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
        if(GV.hasInitializer()){
            emitGlobalVar(&GV);
        }
    }
    return false;
}

void JRISCdevAsmOutput::emitGlobalVar(GlobalVariable *GV){
    if(!GV->hasPrivateLinkage()){
        OS << "@";
    }
    OS << GV->getName() << " ";
    emitGlobalConstant(GV->getParent()->getDataLayout(),GV->getInitializer(),nullptr);
    OS << '\n';
}

void JRISCdevAsmOutput::PrintInt(int64_t value){
    APSInt s(32);
    if(value < 0){
        OS << "-";
        value *= -1;
    }
    s = value;
    OS << toString(s,10);
}

void JRISCdevAsmOutput::PrintSize(uint64_t size){
    switch(size){
        case 1:
            OS << "BYTE";
            break;
        case 2:
            OS << "HALF";
            break;
        case 4:
            OS << "WORD";
            break;
        default:
            OS << "UKNOWN SIZE ";
            PrintInt((int64_t) size);
    }
}

void JRISCdevAsmOutput::emitGlobalAgg(const DataLayout &DL,const ConstantAggregate *CS,const Constant *BaseCV){
    unsigned numops = CS->getNumOperands();
    for(unsigned i = 0;i < numops;i+=1){
        const Constant *OP = CS->getOperand(i);
        if((OP->getType()->isIntOrPtrTy())||(OP->isZeroValue())) {
            OS << "_";
        }
        emitGlobalConstant(DL,OP,CS);
        if(i != (numops - 1)){
            OS << "\n";
        }
    }
}

void JRISCdevAsmOutput::emitGlobalSeq(const DataLayout &DL,const ConstantDataSequential *CV,const Constant *BaseCV){
    if(CV->isString()){
        OS << "BYTES \"" << CV->getAsString() << "\"";
        for(unsigned i = 0;i < CV->getNumElements();i += 1){
            if(CV->getElementAsInteger(i) == 0){
                OS << ",0";
            }
        }
    }
    else if(CV->getElementType()->isIntegerTy()){
        PrintSize(CV->getElementByteSize());
        OS << " ";
        unsigned numelms = CV->getNumElements();
        for(unsigned i = 0;i < numelms;i += 1){
            PrintInt(CV->getElementAsInteger(i));
            if(i != numelms - 1){
                OS << ",";
            }
        } 
    }
    else if(CV->getElementType()->isPointerTy()){
        PrintSize(4);
        unsigned numelms = CV->getNumElements();
        for(unsigned i = 0;i < numelms;i += 1){
            OS << "PTR";
            if(i != numelms - 1){
                OS << ",";
            }
        }
    }
}

void JRISCdevAsmOutput::emitGlobalInt(const DataLayout &DL,const ConstantInt *CV,const Constant *BaseCV){
    PrintSize(DL.getTypeAllocSize(CV->getType()));
    OS << " ";
    PrintInt(CV->getSExtValue());
}

void JRISCdevAsmOutput::emitGlobalConstant(const DataLayout &DL,const Constant *CV,const Constant *BaseCV){
    uint64_t size = DL.getTypeAllocSize(CV->getType());
    if(isa<ConstantAggregateZero>(CV)){
        OS << "ZERO ";
        PrintInt((int64_t) size);
    }
    else if(const ConstantInt *CVI = dyn_cast<ConstantInt>(CV)){
        emitGlobalInt(DL,CVI,BaseCV);
    }
    else if(const ConstantDataSequential *CDS = dyn_cast<ConstantDataSequential>(CV)){
        emitGlobalSeq(DL,CDS,BaseCV);
    }
    else if(const ConstantAggregate *CS = dyn_cast<ConstantAggregate>(CV)){
        if(BaseCV == nullptr){
            OS << "\n";
        }
        emitGlobalAgg(DL,CS,BaseCV);
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