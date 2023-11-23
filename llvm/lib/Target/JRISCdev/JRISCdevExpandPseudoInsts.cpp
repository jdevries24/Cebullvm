#include "llvm/CodeGen/LivePhysRegs.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/MC/MCContext.h"
#include "JRISCdevInstrInfo.h"
#include "JRISCdevTargetMachine.h"

using namespace llvm;

#define JRISCdevPostExpandRA_Name "JRISC-V PreRA PhudoLowering"

namespace{

    class JRISCdevExpandPseudo : public MachineFunctionPass{
        const JRISCdevInstrInfo *TII;
        const JRISCdevSubtarget *STI;
        static char ID;
        public:
            JRISCdevExpandPseudo():MachineFunctionPass(ID){};
            bool runOnMachineFunction(MachineFunction &MF) override;
            
        private:
            bool expandMBB(MachineBasicBlock &MBB);
            bool expandMI(MachineBasicBlock &MBB,MachineBasicBlock::iterator MBBI,MachineBasicBlock::iterator &NextMBBI);
            bool expandSelect(MachineBasicBlock &MBB,MachineBasicBlock::iterator MBBI,MachineBasicBlock::iterator &NextMBBI);
            bool expandLargeMOV(MachineBasicBlock &MBB,MachineBasicBlock::iterator MBBI);
            unsigned getSelectCMPIns(unsigned OP);
    };


    char JRISCdevExpandPseudo::ID;

    bool JRISCdevExpandPseudo::runOnMachineFunction(MachineFunction &MF){
        STI = &MF.getSubtarget<JRISCdevSubtarget>();
        TII = STI->getInstrInfo();
        bool modified = false;
        for(auto &MBB:MF){
            modified |= expandMBB(MBB);
        }
        return modified;
    }

    bool JRISCdevExpandPseudo::expandMBB(MachineBasicBlock &MBB){
        bool modified = false;
        MachineBasicBlock::iterator MBBI = MBB.begin(), E = MBB.end();
        while(MBBI != E){
            MachineBasicBlock::iterator nextMBBI = std::next(MBBI);
            modified |= expandMI(MBB,MBBI,nextMBBI);
            MBBI = nextMBBI;
        }
        return modified;
    }

    bool JRISCdevExpandPseudo::expandMI(MachineBasicBlock &MBB,MachineBasicBlock::iterator MBBI,MachineBasicBlock::iterator &NextMBBI){
        switch(MBBI->getOpcode()){
            case JRISCdev::SELECT_EQ:
            case JRISCdev::SELECT_GT:
            case JRISCdev::SELECT_LT:
            case JRISCdev::SELECT_NE:
            case JRISCdev::SELECT_SGT:
            case JRISCdev::SELECT_SLT:
            case JRISCdev::SELECT_GE:
            case JRISCdev::SELECT_SGE:
            case JRISCdev::SELECT_LE:
            case JRISCdev::SELECT_SLE:
                return expandSelect(MBB,MBBI,NextMBBI);
            case JRISCdev::LARGEMOVE:
                return expandLargeMOV(MBB,MBBI);
            default:
                return false;
        }
    }

    bool JRISCdevExpandPseudo::expandLargeMOV(MachineBasicBlock &MBB,MachineBasicBlock::iterator MBBI){
        MachineInstr &MI = *MBBI;
        Register Reg = MI.getOperand(0).getReg();
        int64_t imm = MI.getOperand(1).getImm();
        DebugLoc DL = MI.getDebugLoc();
        int64_t high = (imm >> 16) & 0xffff;
        BuildMI(MBB,MBBI,DL,TII->get(JRISCdev::ADDI)).addReg(Reg)
        .addReg(JRISCdev::R0)
        .addImm(high);
        BuildMI(MBB,MBBI,DL,TII->get(JRISCdev::LSLI),Reg).addReg(Reg).addImm(16);
        BuildMI(MBB,MBBI,DL,TII->get(JRISCdev::ORRI),Reg).addReg(Reg).addImm(imm & 0xffff);
        MI.eraseFromParent();
        return true;
    }
    unsigned JRISCdevExpandPseudo::getSelectCMPIns(unsigned Op){
        switch(Op){
            case JRISCdev::SELECT_EQ:return JRISCdev::JME;
            case JRISCdev::SELECT_NE:return JRISCdev::JNE;
            case JRISCdev::SELECT_GT:return JRISCdev::JGT;
            case JRISCdev::SELECT_LT:return JRISCdev::JLT;
            case JRISCdev::SELECT_SGT:return JRISCdev::JSGT;
            case JRISCdev::SELECT_SLT:return JRISCdev::JSLT;
            case JRISCdev::SELECT_GE:return JRISCdev::JGE;
            case JRISCdev::SELECT_SGE:return JRISCdev::JSGE;
            case JRISCdev::SELECT_LE:return JRISCdev::JLE;
            case JRISCdev::SELECT_SLE:return JRISCdev::JSLE;
            default:
                llvm_unreachable("Non Select Intstruction");
        }
    }


    bool JRISCdevExpandPseudo::expandSelect(MachineBasicBlock &MBB,MachineBasicBlock::iterator MBBI,MachineBasicBlock::iterator &NextMBBI){
        MachineFunction *MF = MBB.getParent();
        MachineInstr &MI = *MBBI;
        DebugLoc DL = MI.getDebugLoc();
        MachineBasicBlock *FalseBB = MF->CreateMachineBasicBlock(MBB.getBasicBlock());
        MachineBasicBlock *MergeBB = MF->CreateMachineBasicBlock(MBB.getBasicBlock());

        MF->insert(++MBB.getIterator(),FalseBB);
        MF->insert(++FalseBB->getIterator(),MergeBB);

        if(MI.getOperand(0).getReg().id() != MI.getOperand(3).getReg().id()){
            llvm_unreachable("Phudo select doesnt match");
        }

        BuildMI(MBB,MBBI,DL,TII->get(getSelectCMPIns(MI.getOpcode())))
        .addReg(MI.getOperand(1).getReg())
        .addReg(MI.getOperand(2).getReg())
        .addMBB(MergeBB);

        BuildMI(FalseBB,DL,TII->get(JRISCdev::MOV)).addReg(MI.getOperand(0).getReg()).addReg(MI.getOperand(4).getReg());
        
        FalseBB->addSuccessor(MergeBB);
        MergeBB->splice(MergeBB->end(),&MBB,MI,MBB.end());
        MergeBB->transferSuccessors(&MBB);
        MBB.addSuccessor(MergeBB);
        MBB.addSuccessor(FalseBB);

        NextMBBI = MBB.end();
        LivePhysRegs LiveRegs;
        MI.eraseFromParent();
        computeAndAddLiveIns(LiveRegs,*FalseBB);
        computeAndAddLiveIns(LiveRegs,*MergeBB);
        return true;
    }

}
namespace llvm{
    FunctionPass *createJRISCdevExpandPseudoPass(){return new JRISCdevExpandPseudo();}
}