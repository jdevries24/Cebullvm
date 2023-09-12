#include "JRISCdevAsmOutput.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/TinyPtrVector.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Analysis/ConstantFolding.h"
#include "llvm/Analysis/MemoryLocation.h"
#include "llvm/Analysis/OptimizationRemarkEmitter.h"
#include "llvm/BinaryFormat/COFF.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/CodeGen/GCMetadata.h"
#include "llvm/CodeGen/GCMetadataPrinter.h"
#include "llvm/CodeGen/LazyMachineBlockFrequencyInfo.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineDominators.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineInstrBundle.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineLoopInfo.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineModuleInfoImpls.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/CodeGen/MachineOptimizationRemarkEmitter.h"
#include "llvm/CodeGen/StackMaps.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/CodeGen/TargetOpcodes.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/Config/config.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Comdat.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/EHPersonalities.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GCStrategy.h"
#include "llvm/IR/GlobalAlias.h"
#include "llvm/IR/GlobalIFunc.h"
#include "llvm/IR/GlobalObject.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/PseudoProbe.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/ValueHandle.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCSectionCOFF.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCSectionMachO.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCSymbolELF.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/SectionKind.h"

#include "llvm/Object/ELFTypes.h"
#include "llvm/Pass.h"
#include "llvm/Remarks/RemarkStreamer.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Triple.h"
#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cstdint>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using namespace llvm;

char JRISCdevAsmOutput::ID = 0;

JRISCdevAsmOutput::JRISCdevAsmOutput(TargetMachine &tm,std::unique_ptr<formatted_raw_ostream> Owner,MCInstPrinter *Insptr):MachineFunctionPass(ID),
TM(tm),OSOwner(std::move(Owner)),
OS(*OSOwner),InsPtr(Insptr),MCSTI(TM.getMCSubtargetInfo()){}

bool JRISCdevAsmOutput::doInitialization(Module &M){return false;}

bool JRISCdevAsmOutput::runOnMachineFunction(MachineFunction &MF){
    currentCtx = &MF.getContext();
    MCSTI = TM.getMCSubtargetInfo();
    Function &F = MF.getFunction();
    if(!F.hasPrivateLinkage()){
        OS << "@";
    }
    OS << F.getName() << '\n';
    for(auto &MBB : MF){
        if(!MBB.isEntryBlock()){
            OS << MBB.getSymbol()->getName() <<'\n';
        }
        for(auto &MI : MBB){
            MI.dump();
            if(!MI.isMetaInstruction()){
                MCInst temp;
                lowerMI(&MI,temp);
                InsPtr->printInst(&temp,0,"",*MCSTI,OS);
                OS << '\n';
            }
        }
    }
    return false;
}

bool JRISCdevAsmOutput::doFinalization(Module &M){
    OS << "$Data\n";
    for(auto &GV : M.globals()){
        emitGlobalVar(&GV);
    }
    return false;
}

void JRISCdevAsmOutput::emitGlobalVar(GlobalVariable *GV){
    if(!GV->hasPrivateLinkage()){
        OS << "@";
    }
    OS << GV->getName();
    const Type *GVT = GV->getValueType();
    GVT->dump();
    if(GVT->isIntegerTy()){
        emitType(GVT);
        emitInt(GV->getInitializer(),GVT->getIntegerBitWidth());
    }
    if(GVT->isArrayTy()){
        emitArr(GV);
    }
    if(GVT->isPointerTy()){
        OS << " W ";
        emitPtr(GV->getInitializer());
    }
    OS << "\n";
}

void JRISCdevAsmOutput::emitPtr(const Constant *C){
    C->dump();
    if(C->isNullValue()){
        OS << "0";
    }

}

void JRISCdevAsmOutput::emitArr(GlobalVariable *GV){
    const ArrayType *GVT = cast<ArrayType>(GV->getValueType());
    if(GVT->getElementType()->isIntegerTy()){
        emitType(GVT->getElementType());
        for(unsigned i = 0;i < GVT->getArrayNumElements();i += 1){
            emitInt(GV->getInitializer()->getAggregateElement(i));
            if(i != GVT->getArrayNumElements() - 1){
                OS << ",";
            }
        }
    }
}

void JRISCdevAsmOutput::emitInt(const Constant *C,unsigned size){
    APSInt num(size);
    num = C->getUniqueInteger().getSExtValue();
    OS << toString(num,10);
}

void JRISCdevAsmOutput::emitType(const Type *Ty){
    if(Ty->isPointerTy()){
        OS << " W ";
    }
    else if(Ty->getIntegerBitWidth() <= 8){
        OS << " B ";
    }
    else if (Ty->getIntegerBitWidth() <= 16){
        OS << " H ";
    }
    else if (Ty->getIntegerBitWidth() <= 32){
        OS << " W ";
    }
    else{
        OS << " ERROR ";
    }
}


MCOperand JRISCdevAsmOutput::lowerOperand(const MachineOperand &MO) const {
    auto MOT = MO.getType();
    switch(MOT){
        case MachineOperand::MO_Register:
            return MCOperand::createReg(MO.getReg());
        case MachineOperand::MO_Immediate:
            return MCOperand::createImm(MO.getImm());
        case MachineOperand::MO_MachineBasicBlock:
        {
            MCSymbol *sy = MO.getMBB()->getSymbol();
            const MCSymbolRefExpr *MCSym = MCSymbolRefExpr::create(sy,*currentCtx);
            return MCOperand::createExpr(MCSym);
        }
        case MachineOperand::MO_GlobalAddress:
        {
            const GlobalValue *GV = MO.getGlobal();
            SmallString<256> Name;
            if(!GV->hasPrivateLinkage()){
                Name.append("@");
            }
            Name.append(GV->getName());
            MCSymbol *sy = currentCtx->getOrCreateSymbol(Name.str());
            const MCSymbolRefExpr *MCSym = MCSymbolRefExpr::create(sy,*currentCtx);
            return MCOperand::createExpr(MCSym);
        }
        case MachineOperand::MO_RegisterMask:
            return MCOperand();
        default:
            MO.dump();
            llvm_unreachable("unknown MO type");
            
    }
    return MCOperand();
}
void JRISCdevAsmOutput::lowerMI(const MachineInstr *MI, MCInst &OutMI) const {
    OutMI.setOpcode(MI->getOpcode());
    for(auto &MO: MI->operands()){
        OutMI.addOperand(lowerOperand(MO));
    }
}