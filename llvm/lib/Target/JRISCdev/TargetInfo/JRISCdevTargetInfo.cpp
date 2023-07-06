#include "TargetInfo/JRISCdevTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getJRISCdev(){
    static Target JRISCtarget;
    return JRISCtarget;
}
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCDEVTargetInfo() {
  RegisterTarget<Triple::JRISCdev, /*HasJIT=*/false> X(getJRISCdev(),
                                                    "JRISCdev", "TychoComp", "JDOS");
}