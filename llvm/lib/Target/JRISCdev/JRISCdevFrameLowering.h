#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevFRAMELOWERING_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"
namespace llvm{

class JRISCdevFrameLowering :public TargetFrameLowering{
    public:
        JRISCdevFrameLowering():TargetFrameLowering(TargetFrameLowering::StackGrowsDown,Align(4),0){};
        bool hasFP(const MachineFunction &MF) const override{return false;};
        void emitPrologue(MachineFunction &MF,MachineBasicBlock &MBB) const override;
        void emitEpilogue(MachineFunction &MF,MachineBasicBlock &MBB) const override;
        MachineBasicBlock::iterator eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I)
                                     const override;
        void determineCalleeSaves(MachineFunction &MF,BitVector &SavedRegs,RegScavenger *RS) const override;
};
}

#endif