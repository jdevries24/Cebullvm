#include "InputFiles.h"
#include "OutputSections.h"
#include "Symbols.h"
#include "SyntheticSections.h"
#include "Target.h"
#include "llvm/Support/ELFAttributes.h"
#include "llvm/Support/LEB128.h"
#include "llvm/Support/RISCVAttributeParser.h"
#include "llvm/Support/RISCVAttributes.h"
#include "llvm/Support/RISCVISAInfo.h"
#include "llvm/Support/TimeProfiler.h"

using namespace llvm;
using namespace llvm::object;
using namespace llvm::support::endian;
using namespace llvm::ELF;
using namespace lld;
using namespace lld::elf;
namespace{

class JRISC final: public TargetInfo{
    public:
        JRISC();
        RelExpr getRelExpr(RelType type, const Symbol &s,
                            const uint8_t *loc) const override;
        int64_t getImplicitAddend(const uint8_t *buf, RelType type) const override;
        void relocate(uint8_t *loc, const Relocation &rel,
                        uint64_t val) const override;
};
}


static void Reloc_16S(uint8_t *loc,uint64_t val){

}

static void Reloc_20S(uint8_t *loc,uint64_t val){

}

static void Reloc_24S(uint8_t *loc,uint64_t val){
    int64_t v = (int64_t) val;
    if(v < 0){
        v = (v *-1) | 0x800000;
        val = (uint64_t) v;
    }
    loc[1] = (uint8_t)(val >> 16) & 0xff;
    loc[2] = (uint8_t)(val >> 8) & 0xff;
    loc[3] = (uint8_t)(val >> 0) & 0xff;
}

JRISC::JRISC(){}
int64_t JRISC::getImplicitAddend(const uint8_t *buff,RelType type) const {return 0;}
RelExpr JRISC::getRelExpr(RelType type, const Symbol &s,
                            const uint8_t *loc) const{
                                switch(type){
                                    case ELF::EF_JRISC_16S:
                                    case ELF::EF_JRISC_20S:
                                    case ELF::EF_JRISC_24S:
                                        return RelExpr::R_PC;
                                    case ELF::EF_JRISC_32U:
                                        return RelExpr::R_ABS;
                                    default:
                                        llvm_unreachable("Unknown reloc type");
                                }
                            }

void JRISC::relocate(uint8_t *loc, const Relocation &rel,
                        uint64_t val) const{
                            switch(rel.type){
                                case ELF::EF_JRISC_16S:
                                    Reloc_16S(loc,val);
                                    break;
                                case ELF::EF_JRISC_20S:
                                    Reloc_20S(loc,val);
                                    break;
                                case ELF::EF_JRISC_24S:
                                    Reloc_24S(loc,val);
                                    break;
                                default:
                                    llvm_unreachable("Unexpected reloc type");
                            }
                        }

TargetInfo *elf::getJRISCTargetInfo(){
    static JRISC T;
    return &T;
}