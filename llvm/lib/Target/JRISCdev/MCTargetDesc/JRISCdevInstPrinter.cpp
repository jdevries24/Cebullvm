#include "JRISCdevInstPrinter.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/ADT/StringExtras.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "JRISCdevGenAsmWriter.inc"

void JRISCdevInstPrinter::printInt(int64_t value,bool hex,raw_ostream &O,int size){
    if(hex){
        APSInt hexval(size);
        hexval = value;
        O << "0x" << toString(hexval,16);
    }
    else{
        if(value < 0){
            value = value * -1;
            O << "-";
        }
        APSInt val(16);
        val = value;
        O << toString(val,10);
    }
}

void JRISCdevInstPrinter::printMathIM(const MCInst *MI,unsigned OpNo,raw_ostream &O){
    const MCOperand &OP = MI->getOperand(OpNo);
    int64_t val = OP.getImm();
    if(val < 0){
        val = OP.getImm() * - 1;
    }
    printInt(val,true,O);
}

void JRISCdevInstPrinter::printAddr(const MCInst *MI,unsigned OpNo,raw_ostream &O){
    const MCOperand &Op1 = MI->getOperand(OpNo);
    const MCOperand &Op2 = MI->getOperand(OpNo + 1);
    O << getRegisterName(Op1.getReg()) << ",";
    printInt(Op2.getImm(),false,O);
}
void JRISCdevInstPrinter::printRegName(raw_ostream &OS,MCRegister Reg) const{
    OS << getRegisterName(Reg);
}

void JRISCdevInstPrinter::printInst(const MCInst *MI, uint64_t Address, StringRef Annot, const MCSubtargetInfo &STI, raw_ostream &O){
    printInstruction(MI,Address,O);
}

void JRISCdevInstPrinter::printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &OS){
    const MCOperand op = MI->getOperand(OpNo);
    if(op.isReg()){
        printRegName(OS,op.getReg());
    }
    if(op.isImm()){
        if(op.getImm() >= 0x10000){
            printInt(op.getImm(),true,OS,16);
        }
        else{
            printInt(op.getImm(),true,OS);
        }
    }
    if(op.isExpr()){
        auto exp = op.getExpr();
        if(exp->getKind() == MCExpr::SymbolRef){
            const MCSymbolRefExpr &SRE = cast<MCSymbolRefExpr>(*exp);
            const MCSymbol &sym = SRE.getSymbol();
            OS << sym.getName();
        }
    }
}