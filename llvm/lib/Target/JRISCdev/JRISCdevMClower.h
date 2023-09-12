#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevMCINSTLOWER_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevMCINSTLOWER_H

#include "llvm/Support/Compiler.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/IR/GlobalValue.h"

namespace llvm{
  class AsmPrinter;
  class MCContext;
  class MCInst;
  class MCOperand;
  class MCSymbol;
  class MachineInstr;
  class MachineOperand;
    class LLVM_LIBRARY_VISIBILITY JRISCdevMCInstLower{
      public:
        AsmPrinter &ASMprinter;
        MCContext *ctx;
        JRISCdevMCInstLower(AsmPrinter &ptr):ASMprinter(ptr){}
        MCOperand lowerOperand(const MachineOperand &MO) const;
        void lower(const MachineInstr *MI, MCInst &OutMI) const;
        void init(MCContext *ct);
        };
}

#endif