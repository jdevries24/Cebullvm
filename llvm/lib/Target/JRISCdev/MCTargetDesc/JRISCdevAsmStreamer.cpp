#include "JRISCdevAsmStreamer.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

JRISCdevAsmStreamer::JRISCdevAsmStreamer(MCContext &ctx,std::unique_ptr<formatted_raw_ostream> Owner,MCInstPrinter *Insptr):MCStreamer(ctx),OSOwner(std::move(Owner)),OS(*OSOwner),InsPtr(Insptr){}

void JRISCdevAsmStreamer::emitLabel(MCSymbol *S,SMLoc Loc){
    OS << S->getName() << '\n';
}

void JRISCdevAsmStreamer::emitInstruction(const MCInst &Inst,const MCSubtargetInfo &STI){
    InsPtr->printInst(&Inst,0,StringRef(""),STI,OS);
    OS << "\n";
}

void JRISCdevAsmStreamer::emitZerofill(MCSection *Section, MCSymbol *Symbol, uint64_t Size, Align ByteAlignment, SMLoc Loc){
    APSInt S(16);
    S = Size;
    OS << "ZERO " << toString(S,10) << "\n";
}

