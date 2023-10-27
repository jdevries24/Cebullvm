#ifndef JRISCdevTargetTransformInfo
#define JRISCdevTargetTransformInfo

#include "JRISCdevSubtarget.h"
#include "JRISCdevTargetMachine.h"
#include "llvm/Analysis/IVDescriptors.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include <optional>

namespace llvm {

class JRISCdevTTIImpl : public BasicTTIImplBase<JRISCdevTTIImpl> {
  using BaseT = BasicTTIImplBase<JRISCdevTTIImpl>;
  using TTI = TargetTransformInfo;

  friend BaseT;

  const JRISCdevSubtarget *ST;
  const JRISCdevILowering *STL;
  const JRISCdevILowering *getTLI() const{return STL;}
  const JRISCdevSubtarget *getST() const{return ST;}
  public:
    explicit JRISCdevTTIImpl(const JRISCdevTargetMachine *TM,const Function &F):BaseT(TM,F.getParent()->getDataLayout()),
    ST(TM->getSubtargetImpl(F)),STL(TM->getSubtargetImpl(F)->getTargetLowering()){}
    InstructionCost getCmpSelInstrCost(unsigned Opcode, Type *ValTy, Type *CondTy,
                                     CmpInst::Predicate VecPred,
                                     TTI::TargetCostKind CostKind,
                                     const Instruction *I = nullptr) { return InstructionCost::getMax();}
    void 	getUnrollingPreferences (Loop *L, ScalarEvolution &SE, TTI::UnrollingPreferences &UP, OptimizationRemarkEmitter *ORE){
      UP.OptSizeThreshold = 0;
      UP.PartialOptSizeThreshold = 0;
    }
      InstructionCost getCallInstrCost(Function *F, Type *RetTy,
                                   ArrayRef<Type *> Tys,
                                   TTI::TargetCostKind CostKind) {
    return InstructionCost::getMin();
  }
	unsigned adjustInliningThreshold(const CallBase *CB){return 0;}
	unsigned getInliningThresholdMultiplier() const { return 0; }

};
} 

#endif
