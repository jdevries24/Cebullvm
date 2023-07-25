#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevISELLOWERING_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevISELLOWERING_H

#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm{
    namespace JRISCdevID{
        enum NodeType{
            FIRST_NUMBER = ISD::BUILTIN_OP_END,
            CAL,
            RET_FLAG,
        };
    }
    class JRISCdevSubtarget;
    class JRISCdevILowering:public TargetLowering{
        public:
            explicit JRISCdevILowering(const TargetMachine &TM,const JRISCdevSubtarget &STI);
        private:
            SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                         const SmallVectorImpl<ISD::InputArg> &Ins,
                         const SDLoc &dl, SelectionDAG &DAG,
                         SmallVectorImpl<SDValue> &InVals) const override;
            SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,SmallVectorImpl<SDValue> &InVals) const override;
            bool CanLowerReturn(CallingConv::ID /*CallConv*/,
                              MachineFunction &/*MF*/, bool /*isVarArg*/,
               const SmallVectorImpl<ISD::OutputArg> &/*Outs*/,
               LLVMContext &/*Context*/) const override;
            SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                              bool isVarArg,
                              const SmallVectorImpl<ISD::OutputArg> & Outs,
                              const SmallVectorImpl<SDValue> & OutVals,
                              const SDLoc & dl,
                              SelectionDAG & DAG) const override;
            SDValue LowerCallResult(
                        SDValue Chain, SDValue InGlue, CallingConv::ID CallConv, bool isVarArg,
                        const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc dl, SelectionDAG &DAG,
                        SmallVectorImpl<SDValue> &InVals) const;
    };
}

#endif