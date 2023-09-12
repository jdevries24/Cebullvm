#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevSubtarget_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevSubtarget_H

#include "JRISCdevISelLowering.h"
#include "JRISCdevRegisterInfo.h"
#include "JRISCdevInstrInfo.h"
#include "JRISCdevFrameLowering.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include <string>


#define GET_SUBTARGETINFO_HEADER
#include "JRISCdevGenSubtargetInfo.inc"

namespace llvm{
class StringRef;
class JRISCdevSubtarget:public JRISCdevGenSubtargetInfo{
    virtual void anchor();
    private:
        JRISCdevILowering ILower;
        JRISCdevRegisterInfo RegInfo;
        JRISCdevInstrInfo IInfo;
        JRISCdevFrameLowering FlInfo;
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
        const JRISCdevInstrInfo *getInstrInfo() const override { return &IInfo; }
        const JRISCdevFrameLowering *getFrameLowering() const override {return &FlInfo;}

};
}

#endif