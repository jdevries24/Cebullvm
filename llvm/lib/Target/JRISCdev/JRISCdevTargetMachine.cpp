#include "JRISCdevTargetMachine.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/JRISCdevTargetInfo.h"

namespace llvm{

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCdevTargetMachine() {
  RegisterTargetMachine<JRISCdevTargetMachine> X(getJRISCdev());
}

static CodeModel::Model getCM(std::optional<CodeModel::Model> CM){
  return CodeModel::Medium;
}

JRISCdevTargetMachine::JRISCdevTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOpt::Level OL, bool JIT):LLVMTargetMachine(T,"E-p:32:1-i:32:1",TT,CPU,FS,Options,Reloc::PIC_,getCM(CM),OL){
                     }
}