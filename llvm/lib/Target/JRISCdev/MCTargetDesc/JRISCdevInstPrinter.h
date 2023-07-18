#ifndef LLVM_LIB_TARGET_JRISCdev_MCTARGETDESC_JRISCdevINSTPRINTER_H
#define LLVM_LIB_TARGET_JRISCdev_MCTARGETDESC_JRISCdevINSTPRINTER_H
#include "llvm/MC/MCInstPrinter.h"

namespace llvm {
    class JRISCdevInstPrinter: public MCInstPrinter{
        public:
            JRISCdevInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                      const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {
        setPrintImmHex(true);
      }
            std::pair<const char *,uint64_t> getMnemonic(const MCInst *MI) override;
            void printInst(const MCInst *MI, uint64_t Address, StringRef Annot, const MCSubtargetInfo &STI, raw_ostream &O) override;
            void printInstruction(const MCInst *MI,uint64_t Address,raw_ostream &O);
            void printRegName(raw_ostream &OS,MCRegister Reg) const override;
            static const char *getRegisterName(MCRegister Reg);
            void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
            bool printAliasInstr(const MCInst *MI,uint64_t Address,raw_ostream &OS);


    };
}

#endif