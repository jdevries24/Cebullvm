#include "TargetInfo/JRISCdevTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
using namespace llvm;

Target &llvm::getJRISCdev(){
    static Target JRISCtarget;
    return JRISCtarget;
}

void DUMP(){
  dbgs() << "HEAR!!!!";
}
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCdevTargetInfo() {
  RegisterTarget<Triple::JRISCdev, /*HasJIT=*/false> X(getJRISCdev(),
                                                    "JRISCdev", "A simple risc arch", "JDOS");
  DUMP();
}