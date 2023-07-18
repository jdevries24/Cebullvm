#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevSubtarget_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevSubtarget_H

#include "JRISCdevISelLowering.h"
#include "JRISCdevRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "JRISCdevGenSubtargetInfo.inc"

namespace llvm{
class StringRef;
class JRISCdevSubtarget:public JRISCdevGenSubtargetInfo{
    private:
        JRISCdevILowering ILower;
        JRISCdevRegisterInfo RegInfo;
        virtual void anchor();
    public:
        JRISCdevSubtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM);
        void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
        const JRISCdevRegisterInfo *getRegisterInfo() const override{
            return &RegInfo;
        }
        const JRISCdevILowering *getTargetLowering() const override{
            return &ILower;
        }
};
}

#endif