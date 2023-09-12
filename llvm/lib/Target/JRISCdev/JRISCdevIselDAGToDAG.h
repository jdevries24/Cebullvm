#ifndef LLVM_LIB_TARGET_JRISCV_JRISCVISELDAGTODAG_H
#define LLVM_LIB_TARGET_JRISCV_JRISCVISELDAGTODAG_H

#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Support/KnownBits.h"

namespace llvm{
  class JRISCdevTargetMachine;
FunctionPass *createJRISCdevISelDag(JRISCdevTargetMachine &TM,CodeGenOpt::Level lev);
}
#endif