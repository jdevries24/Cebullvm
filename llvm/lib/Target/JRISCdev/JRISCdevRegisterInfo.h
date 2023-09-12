#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevREGINFO_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevREGINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#include "MCTargetDesc/JRISCdevTargetDesc.h"
#define GET_REGINFO_HEADER
#include "JRISCdevGenRegisterInfo.inc"

namespace llvm{

    class JRISCdevRegisterInfo:public JRISCdevGenRegisterInfo{
    public:
        JRISCdevRegisterInfo():JRISCdevGenRegisterInfo(15){}
        const MCPhysReg * getCalleeSavedRegs(const MachineFunction *MF) const override;

    BitVector getReservedRegs(const MachineFunction &MF) const override;

    const uint32_t * getCallPreservedMask(const MachineFunction &MF,CallingConv::ID) const override;
    const TargetRegisterClass*
    getPointerRegClass(const MachineFunction &MF,
                     unsigned Kind = 0) const override;

    bool eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  // Debug information queries.
    Register getFrameRegister(const MachineFunction &MF) const override;
    };
}
#endif