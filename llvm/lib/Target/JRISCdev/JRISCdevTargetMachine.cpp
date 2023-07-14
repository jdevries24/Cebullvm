#include "JRISCdevTargetMachine.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/JRISCdevTargetInfo.h"

namespace llvm{

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCdevTarget() {
  RegisterTargetMachine<JRISCdevTargetMachine> X(getJRISCdev());
}

static CodeModel::Model getCM(std::optional<CodeModel::Model> CM){
  return CodeModel::Medium;
}

JRISCdevTargetMachine::JRISCdevTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU,StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOpt::Level OL, bool JIT):LLVMTargetMachine(T,"E-p:32:32-i32:32-i16:16-i8:8-i1:8",TT,CPU,FS,Options,Reloc::PIC_,getCM(CM),OL),
                                       subtarget(TT,CPU.str(),FS.str(),*this){
                     }
}