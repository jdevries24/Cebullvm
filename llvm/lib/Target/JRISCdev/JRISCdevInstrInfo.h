#ifndef JRISCdev_InstrInfo_H
#define JRISCdev_InstrInfo_H

#include "JRISCdevRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#define GET_INSTRINFO_HEADER
#include "JRISCdevGenInstrInfo.inc"

namespace llvm{
    class JRISCdevInstrInfo : public JRISCdevGenInstrInfo{
        const JRISCdevRegisterInfo RI;
        virtual void anchor();
    public:
        JRISCdevInstrInfo();
        const JRISCdevRegisterInfo &getRegisterInfo() const {return RI;};

        virtual void copyPhysReg(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, const DebugLoc &DL,
                           MCRegister DestReg, MCRegister SrcReg,
                           bool KillSrc) const override;

        virtual void storeRegToStackSlot(MachineBasicBlock &MBB,
                                   MachineBasicBlock::iterator MI,
                                   Register SrcReg, bool isKill, int FrameIndex,
                                   const TargetRegisterClass *RC,
                                   const TargetRegisterInfo *TRI,
                                   Register VReg) const override;

        virtual void loadRegFromStackSlot(MachineBasicBlock &MBB,
                                    MachineBasicBlock::iterator MI,
                                    Register DestReg, int FrameIndex,
                                    const TargetRegisterClass *RC,
                                    const TargetRegisterInfo *TRI,
                                    Register VReg) const override;
    };
}
#endif