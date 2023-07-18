#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevISELLOWERING_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevISELLOWERING_H

#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm{
    class JRISCdevSubtarget;
    class JRISCdevILowering:public TargetLowering{
        public:
            explicit JRISCdevILowering(const TargetMachine &TM,const JRISCdevSubtarget &STI);

    };
}

#endif