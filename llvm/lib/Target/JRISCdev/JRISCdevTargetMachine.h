#ifndef LLVM_LIB_TARGET_JRISCDEV_JRISCDEVTARGETMACHINE_H
#define LLVM_LIB_TARGET_JRISCDEV_JRISCDEVTARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"
namespace llvm{
class JRISCdevTargetMachine : public LLVMTargetMachine{


    public:
        JRISCdevTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOpt::Level OL, bool JIT);
};
}

#endif