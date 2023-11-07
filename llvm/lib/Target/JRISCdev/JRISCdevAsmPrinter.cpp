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


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCdevAsmPrinter(){
    RegisterAsmPrinter<JRISCdevAsmPrinter> X(getJRISCdev());
}