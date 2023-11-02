#include "JRISCdevTargetDesc.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
    class JRISCdevMCCodeEmitter: public MCCodeEmitter{
        const MCInstrInfo &II;
        MCContext &Ctx;
        public:
            JRISCdevMCCodeEmitter(const MCInstrInfo &l,MCContext &c):MCCodeEmitter(),II(l),Ctx(c){}
            void encodeInstruction (const MCInst &Inst, SmallVectorImpl< char > &CB, SmallVectorImpl< MCFixup > &Fixups, const MCSubtargetInfo &STI)const override;
            uint64_t getBinaryCodeForInstr(const MCInst &MI,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo &STI)const;
            uint64_t encodeMemSrc(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const;
            uint64_t encodeImm16S(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const;
            uint64_t encodeImm20S(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const;
            uint64_t encodeImm24S(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const;
            uint64_t encodeRegister(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const;
            uint64_t encodeMathIM(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const;
    };
}
MCCodeEmitter *llvm::createJRISCdevCodeEmitter(const MCInstrInfo &l,MCContext &c){
    return new JRISCdevMCCodeEmitter(l,c);
}

uint64_t JRISCdevMCCodeEmitter::encodeMemSrc(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const{
    return 0;
}


uint64_t JRISCdevMCCodeEmitter::encodeImm16S(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const{
    return 0;
}

uint64_t JRISCdevMCCodeEmitter::encodeImm20S(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const{
    return 0;
}

uint64_t JRISCdevMCCodeEmitter::encodeImm24S(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const{
    return 0;
}

uint64_t JRISCdevMCCodeEmitter::encodeRegister(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const{return 0;}

uint64_t JRISCdevMCCodeEmitter::encodeMathIM(const MCInst &MI,uint64_t index,SmallVectorImpl<MCFixup> &Fixups,const MCSubtargetInfo)const{return 0;}

void JRISCdevMCCodeEmitter::encodeInstruction (const MCInst &Inst, SmallVectorImpl< char > &CB, SmallVectorImpl< MCFixup > &Fixups, const MCSubtargetInfo &STI)const{
    const MCInstrDesc &Disc = II.get(Inst.getOpcode());
    if(Disc.getSize() == 2){
        uint16_t bin = getBinaryCodeForInstr(Inst,Fixups,STI);
        support::endian::write<uint16_t>(CB,bin,support::big);
    }
    else if(Disc.getSize() == 4){
        uint32_t bin = getBinaryCodeForInstr(Inst,Fixups,STI);
        support::endian::write<uint32_t>(CB,bin,support::big);
    }
}

#include "JRISCdevGenEmitter.inc"




