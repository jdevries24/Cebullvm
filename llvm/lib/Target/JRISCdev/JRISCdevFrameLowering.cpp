#include "JRISCdevFrameLowering.h"
#include "JRISCdevInstrInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Function.h"
#include "llvm/Target/TargetOptions.h"
using namespace llvm;

void JRISCdevFrameLowering::emitPrologue(MachineFunction &MF,MachineBasicBlock &MBB) const{
    uint64_t stacksize = MF.getFrameInfo().getStackSize();
    if(stacksize == 0){
        return;
    }
    const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();
    auto MBBI = MBB.begin();
    DebugLoc dl = MBBI != MBB.end() ? MBBI->getDebugLoc(): DebugLoc();
    BuildMI(MBB,MBBI,dl,TII.get(JRISCdev::SUBI),JRISCdev::SP).addReg(JRISCdev::SP).addImm(stacksize).setMIFlag(MachineInstr::FrameSetup);
}

void JRISCdevFrameLowering::emitEpilogue(MachineFunction &MF,MachineBasicBlock &MBB) const{
    uint64_t stacksize = MF.getFrameInfo().getStackSize();
    if(stacksize == 0){
        return;
    }
    const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();
    auto MBBI = MBB.getLastNonDebugInstr();
    DebugLoc dl = MBBI->getDebugLoc();
    BuildMI(MBB,MBBI,dl,TII.get(JRISCdev::ADDI),JRISCdev::SP).addReg(JRISCdev::SP).addImm(stacksize).setMIFlag(MachineInstr::FrameSetup);
}

MachineBasicBlock::iterator JRISCdevFrameLowering::eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I)
                                     const{
                                        if((I->getOpcode() == JRISCdev::CALLSTACKDOWN) || (I->getOpcode() == JRISCdev::CALLSTACKUP)){
                                            MBB.erase(I);
                                        }
                                        return I;
                                     }

void JRISCdevFrameLowering::determineCalleeSaves(MachineFunction &MF,BitVector &SavedRegs,RegScavenger *RS) const{
    const TargetRegisterInfo &TRI = *MF.getSubtarget().getRegisterInfo();
    SavedRegs.resize(TRI.getNumRegs());
    const MCPhysReg *CSRegs = MF.getRegInfo().getCalleeSavedRegs();
    const MachineRegisterInfo &MRI = MF.getRegInfo();
    for(int i = 0;CSRegs[i];i+=1){
        if(MRI.isPhysRegModified(CSRegs[i])){
            SavedRegs.set(CSRegs[i]);
        }
    }
    if(MF.getFrameInfo().hasCalls()){
        SavedRegs.set(JRISCdev::RA);
    }
}