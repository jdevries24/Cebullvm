#include "MCTargetDesc/JRISCdevTargetDesc.h"
#include "MCTargetDesc/JRISCdevFixupKinds.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/ADT/APInt.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCAsmLayout.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/LEB128.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

namespace{
    class JRISCdevObjectWriter:public MCELFObjectTargetWriter{
        public:
            JRISCdevObjectWriter(uint8_t OSABI)
            :MCELFObjectTargetWriter(/*is64Bit*/false,OSABI,/*ELF::EM_ARM*/ELF::EM_ARM,/*hasRelocationAddend*/false){}
            ~JRISCdevObjectWriter() override;
        protected:
            unsigned getRelocType(MCContext &Ctx,const MCValue &Target,const MCFixup &Fixup,bool IsPCRel) const override{
                switch(Fixup.getKind()){
                    case JRISCdev::FK_PC_REL_24S:
                        return ELF::EF_JRISC_24S;
                    case JRISCdev::FK_PC_REL_20S:
                        return ELF::EF_JRISC_20S;
                    case JRISCdev::FK_PC_REL_16S:
                        return ELF::EF_JRISC_16S;
                    default:
                        llvm_unreachable("Unexpected Fixup type for JRISC");
                }
            }


    };

    class JRISCdevAsmBackend: public MCAsmBackend{
        public:
        JRISCdevAsmBackend(const Target &T):MCAsmBackend(endianness::big,JRISCdev::NumTargetFixupKinds){}
        const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override{
            const static MCFixupKindInfo Infos[JRISCdev::NumTargetFixupKinds] = {
                {"FK_PC_REL_24S",0,24,MCFixupKindInfo::FKF_IsPCRel},
                {"FK_PC_REL_20S",0,20,MCFixupKindInfo::FKF_IsPCRel},
                {"FK_PC_REL_16S",0,16,MCFixupKindInfo::FKF_IsPCRel},
                {"FK_PC_REL_32U",0,32,MCFixupKindInfo::FKF_Constant},
            };
            if(Kind < FirstTargetFixupKind){
                return MCAsmBackend::getFixupKindInfo(Kind);
            }
            assert(unsigned(Kind - FirstTargetFixupKind) < JRISCdev::NumTargetFixupKinds && "Kind out of range");
            return Infos[Kind - FirstTargetFixupKind];
        }

        unsigned getNumFixupKinds() const override{return JRISCdev::NumTargetFixupKinds;}
        bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                                            const MCRelaxableFragment *DF,
                                            const MCAsmLayout &Layout) const override {return false;}

        uint64_t get_value_offset(const MCValue &Value)const{

        }

        void Fix_PC_REL_24S(const MCAssembler &Asm, const MCFixup &Fixup,
                                const MCValue &Target, MutableArrayRef<char> Data,
                                uint64_t V, bool IsResolved,
                                const MCSubtargetInfo *STI)const{
                                int64_t Value = (int64_t) V;
                                if(Value < 0){
                                    Value *= -1;
                                    Value |= 0x800000;
                                }
                                uint64_t off = Fixup.getOffset() + 1;
                                    Data[off + 0] = (uint8_t) (Value >> 16) & 0xff;
                                    Data[off + 1] = (uint8_t) (Value >> 8) & 0xff;
                                    Data[off + 2] = (uint8_t) Value & 0xff;
                                }

        uint64_t Fix_PC_REL_20S(const MCAssembler &Asm, const MCFixup &Fixup,
                                const MCValue &Target, MutableArrayRef<char> Data,
                                uint64_t Value, bool IsResolved,
                                const MCSubtargetInfo *STI)const;

        uint64_t Fix_PC_REL_16S(const MCAssembler &Asm, const MCFixup &Fixup,
                                const MCValue &Target, MutableArrayRef<char> Data,
                                uint64_t V, bool IsResolved,
                                const MCSubtargetInfo *STI)const{
                                    int64_t Value = (int64_t) V;
                                    if(Value > 0){
                                        Value *= -1;
                                        Value |= 0x8000;
                                    }
                                    uint64_t off = Fixup.getOffset() + 2;
                                    Data[off + 0] = (uint8_t) (V >> 8) & 0xff;
                                    Data[off + 1] = (uint8_t) V & 0xff;
                                }

        uint64_t Fix_PC_REL_32U(const MCAssembler &Asm, const MCFixup &Fixup,
                                const MCValue &Target, MutableArrayRef<char> Data,
                                uint64_t Value, bool IsResolved,
                                const MCSubtargetInfo *STI) const;

        void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                                const MCValue &Target, MutableArrayRef<char> Data,
                                uint64_t Value, bool IsResolved,
                                const MCSubtargetInfo *STI) const override{
                                    switch(Fixup.getKind()){
                                        case JRISCdev::FK_PC_REL_24S:
                                            Fix_PC_REL_24S(Asm,Fixup,Target,Data,Value,IsResolved,STI);
                                            break;
                                        case JRISCdev::FK_PC_REL_16S:
                                            Fix_PC_REL_16S(Asm,Fixup,Target,Data,Value,IsResolved,STI);
                                            break;
                                        default:
                                            llvm_unreachable("Unknown fixup type");
                                    }
                                };

        std::unique_ptr<MCObjectTargetWriter> createObjectTargetWriter() const override{
            return std::make_unique<JRISCdevObjectWriter>(ELF::ELFOSABI_NONE);
        }
        bool writeNopData(raw_ostream &OS, uint64_t Count,
                            const MCSubtargetInfo *STI) const override{
                                for(uint64_t i = 0;i < Count;i+=1){
                                    OS << 0;
                                }
                                return true;
                            }
    };
}

JRISCdevObjectWriter::~JRISCdevObjectWriter() = default;


MCAsmBackend *llvm::createJRISCdevAsmBackend(const Target &T,
                                       const MCSubtargetInfo &STI,
                                       const MCRegisterInfo &MRI,
                                       const MCTargetOptions &Options){
                                        return new JRISCdevAsmBackend(T);
                                       }