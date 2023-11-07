
#ifndef JRISCdev_JRISCdevASMPrinter_H
#define JRISCdev_JRISCdevASMPrinter_H

#include "llvm/CodeGen/AsmPrinter.h"
#include "TargetInfo/JRISCdevTargetInfo.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
#include "MCTargetDesc/JRISCdevInstPrinter.h"
#include "JRISCdevMClower.h"

namespace llvm{
    class JRISCdevAsmPrinter: public AsmPrinter{
        JRISCdevMCInstLower MClow;
        
        public:
            explicit JRISCdevAsmPrinter(TargetMachine &TM,std::unique_ptr<MCStreamer> Streamer):AsmPrinter(TM,std::move(Streamer)),MClow(*this){}
            StringRef getPassName() const override {return "JRISCdev Assembly printer";}
            void emitInstruction(const MachineInstr *MI) override;
            void emitFunctionBodyStart() override;
            void emitFunctionEntryLabel() override;
    };
}

#endif