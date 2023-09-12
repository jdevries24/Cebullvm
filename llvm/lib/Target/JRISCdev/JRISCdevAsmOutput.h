#ifndef JRISCdevASMOutput_h
#define JRISCdevASMOutput_h

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/CodeGen/AsmPrinterHandler.h"
#include "llvm/CodeGen/DwarfStringPoolEntry.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/StackMaps.h"
#include "llvm/DebugInfo/CodeView/CodeView.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/Support/FormattedStream.h"
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace llvm {
 
class AddrLabelMap;
class BasicBlock;
class BlockAddress;
class Constant;
class ConstantArray;
class DataLayout;
class DIE;
class DIEAbbrev;
class DwarfDebug;
class GCMetadataPrinter;
class GCStrategy;
class GlobalAlias;
class GlobalObject;
class GlobalValue;
class GlobalVariable;
class MachineBasicBlock;
class MachineConstantPoolValue;
class MachineDominatorTree;
class MachineFunction;
class MachineInstr;
class MachineJumpTableInfo;
class MachineLoopInfo;
class MachineModuleInfo;
class MachineOptimizationRemarkEmitter;
class MCAsmInfo;
class MCCFIInstruction;
class MCContext;
class MCExpr;
class MCInst;
class MCSection;
class MCStreamer;
class MCSubtargetInfo;
class MCOperand;
class MachineOperand;
class MCSymbol;
class MCTargetOptions;
class MDNode;
class Module;
class PseudoProbeHandler;
class raw_ostream;
class StringRef;
class TargetLoweringObjectFile;
class TargetMachine;
class Twine;

class JRISCdevAsmOutput :public MachineFunctionPass{
    private:
        TargetMachine &TM;
        std::unique_ptr<formatted_raw_ostream> OSOwner;
        formatted_raw_ostream &OS;
        MCInstPrinter *InsPtr;
        MCContext *currentCtx = nullptr;
        const MCSubtargetInfo *MCSTI;
    public:
        JRISCdevAsmOutput(TargetMachine &tm,std::unique_ptr<formatted_raw_ostream> Owner,MCInstPrinter *Insptr);
        MCOperand lowerOperand(const MachineOperand &MO) const;
        void emitGlobalVar(GlobalVariable *GV);
        void emitIntVar(GlobalVariable *GV);
        void emitType(const Type *Ty);
        void emitInt(const Constant *C,unsigned size = 32);
        void emitArr(GlobalVariable *GV);
        void emitPtr(const Constant *C);
        void lowerMI(const MachineInstr *MI, MCInst &OutMI) const;
        bool doInitialization(Module &M) override;
        bool runOnMachineFunction(MachineFunction &MF) override;
        bool doFinalization(Module &MF) override;
    private:
    static char ID;
};
}
#endif