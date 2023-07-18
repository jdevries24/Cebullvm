#include "JRISCdevInstPrinter.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "JRISCdevGenAsmWriter.inc"

void JRISCdevInstPrinter::printRegName(raw_ostream &OS,MCRegister Reg) const{
    OS << getRegisterName(Reg);
}

void JRISCdevInstPrinter::printInst(const MCInst *MI, uint64_t Address, StringRef Annot, const MCSubtargetInfo &STI, raw_ostream &O){
    printInstruction(MI,Address,O);
}

void JRISCdevInstPrinter::printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O){
    const MCOperand op = MI->getOperand(OpNo);
    if(op.isReg()){
        op.print(O,&MRI);
    }
}