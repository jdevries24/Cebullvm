#ifndef LLVM_LIB_TARGET_JRISCdev_JRISCdevISELLOWERING_H
#define LLVM_LIB_TARGET_JRISCdev_JRISCdevISELLOWERING_H

#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm{
    namespace JRISCdevID{
        enum NodeType{
            FIRST_NUMBER = ISD::BUILTIN_OP_END,
            CAL,
            LOAD_SYM,
            RET_FLAG,
        };
    }
    class JRISCdevSubtarget;
    class JRISCdevILowering:public TargetLowering{
        public:
            explicit JRISCdevILowering(const TargetMachine &TM,const JRISCdevSubtarget &STI);
            virtual const char *getTargetNodeName(unsigned Op) const override{
                switch(Op){
                    case JRISCdevID::CAL:
                        return "CAL";
                    case JRISCdevID::LOAD_SYM:
                        return "LOAD_SYM";
                    case JRISCdevID::RET_FLAG:
                        return "RET_FLAG";
                    default:
                        return "Unknown Target Node";
                }
            }
            //bool convertSetCCLogicToBitwiseLogic(EVT VT) const override{return true;};
            bool isSelectSupported(SelectSupportKind SSK) const override {return false;};
            ISD::CondCode getCondCode(ISD::CondCode CC) const;
            bool needsSwap(ISD::CondCode CC) const;
	    SDValue getBRCond(SDValue Op,SelectionDAG &DAG,SDLoc dl) const;
            SDValue getSET_CC(SDValue Op,SelectionDAG &DAG,SDLoc dl) const;
            SDValue getCMP(SDValue Op,SelectionDAG &DAG,SDLoc dl,ISD::CondCode code,bool reversed) const;
            SDValue LowerCMP(SDValue Op,SelectionDAG &DAG, SDLoc dl) const;
            SDValue LowerConst(SDValue Op,SelectionDAG &DAG) const;
            SDValue LowerGlobalAddr(SDValue Op,SelectionDAG &DAG,SDLoc dl) const;
            MachineBasicBlock *InsertSelect(MachineInstr &MI,MachineBasicBlock *BB) const;
            SDValue LowerOperation(SDValue Op,SelectionDAG &DAG) const override;
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
            bool isIntDivCheap(EVT,AttributeList) const override{return true;};
            bool preferZeroCompareBranch() const override{return true;};
            MachineBasicBlock *EmitInstrWithCustomInserter(MachineInstr &MI,MachineBasicBlock *BB) const override;
            
    };
}

#endif
