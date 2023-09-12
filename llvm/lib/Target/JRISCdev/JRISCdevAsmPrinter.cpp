#include "JRISCdevAsmPrinter.h"

using namespace llvm;

void JRISCdevAsmPrinter::emitFunctionBodyStart(){
    MClow.init(&MF->getContext());
}

void JRISCdevAsmPrinter::emitInstruction(const MachineInstr *MI){
    MCInst temp;
    MClow.lower(MI,temp);
    EmitToStreamer(*OutStreamer,temp);
}

void JRISCdevAsmPrinter::emitFunctionEntryLabel(){
    OutStreamer->emitLabel(CurrentFnSym);
}

void JRISCdevAsmPrinter::emitGlobalVariable(const GlobalVariable *GV){
    MCSymbol *GVsym = getSymbol(GV);
    OutStreamer->emitLabel(GVsym);
    const DataLayout &DL = GV->getParent()->getDataLayout();
    uint64_t size = DL.getTypeAllocSize(GV->getValueType());
    emitGlobalConstant(DL,GV->getInitializer());
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCdevAsmPrinter(){
    RegisterAsmPrinter<JRISCdevAsmPrinter> X(getJRISCdev());
}