#ifndef JRISCdev_JRISCdevASMStreamer_H
#define JRISCdev_JRISCdevASMStreamer_H

#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/MC/MCInstPrinter.h"

namespace llvm{
    class JRISCdevAsmStreamer:public MCStreamer{
        std::unique_ptr<formatted_raw_ostream> OSOwner;
        formatted_raw_ostream &OS;
        MCInstPrinter *InsPtr;
        public:
            JRISCdevAsmStreamer(MCContext &ctx,std::unique_ptr<formatted_raw_ostream> Owner,MCInstPrinter *Insptr);
            void emitLabel(MCSymbol *symbol,SMLoc Loc=SMLoc()) override;
            void emitInstruction(const MCInst &Inst,const MCSubtargetInfo &STI) override;
            bool emitSymbolAttribute(MCSymbol *Symbol,MCSymbolAttr attr) override{return false;};
            void emitCommonSymbol(MCSymbol *Symbol, uint64_t Size, Align ByteAlignment) override{};
            void emitZerofill(MCSection *Section, MCSymbol *Symbol=nullptr, uint64_t Size=0, Align ByteAlignment=Align(1), SMLoc Loc=SMLoc()) override;
            raw_ostream &getCommentOS() override{return OS;};
            bool isVerboseAsm()const override{return true;};

    };
}

#endif