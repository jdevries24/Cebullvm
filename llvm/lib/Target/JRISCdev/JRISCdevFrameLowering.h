#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevFRAMELOWERING_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"
namespace llvm{
class JRISCdevSubtarget;
class JRISCdevInstrInfo;
class JRISCdevRegisterInfo;

class JRISCdevFrameLowering :public TargetFrameLowering{
    public:
        JRISCdevFrameLowering(JRISCdevSubtarget &STI);
};
}

#endif