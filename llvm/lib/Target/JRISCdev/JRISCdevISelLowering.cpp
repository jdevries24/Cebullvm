
#include "JRISCdevISelLowering.h"
#include "JRISCdevRegisterInfo.h"
#include "JRISCdevSubtarget.h"
#include "MCTargetDesc/JRISCdevTargetDesc.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalAlias.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "JRISCdev-lower"

using namespace llvm;

#include "JRISCdevGenCallingConv.inc"


JRISCdevILowering::JRISCdevILowering(const TargetMachine &TM,const JRISCdevSubtarget &STI):TargetLowering(TM)
    {
        addRegisterClass(MVT::i32,&JRISCdev::GPregsRegClass);
        computeRegisterProperties(STI.getRegisterInfo());
    }



SDValue JRISCdevILowering::LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins,
    const SDLoc &dl, SelectionDAG &DAG,
    SmallVectorImpl<SDValue> &InVals) const{
        SmallVector<CCValAssign,16> ArgLocs;
        CCState CCInfo(CallConv,isVarArg,DAG.getMachineFunction(),ArgLocs,*DAG.getContext());
        CCInfo.AnalyzeFormalArguments(Ins,JRISC_CC);
        MachineFunction &MF = DAG.getMachineFunction();
        SDValue ArgValue;
        for(auto VA : ArgLocs){
            if(VA.isRegLoc()){
                EVT RegVT = VA.getLocVT();
                const TargetRegisterClass *RC;
                if(RegVT == MVT::i32){
                    RC = &JRISCdev::GPregsRegClass;
                }
                else{
                    llvm_unreachable("RegVT not supported?");
                }
                unsigned Reg = MF.addLiveIn(VA.getLocReg(),RC);
                ArgValue = DAG.getCopyFromReg(Chain,dl,Reg,RegVT);
                InVals.push_back(ArgValue);
            }
            else{
                assert(VA.isMemLoc() && "Only registers or stack passing");
                unsigned offset = VA.getLocMemOffset();
                MachineFrameInfo &MFI = MF.getFrameInfo();
                offset += MFI.hasCalls() ? 4 : 0;
                const int FI = MFI.CreateFixedObject(4,offset,true);
                EVT PtrTy = getPointerTy(DAG.getDataLayout());
                SDValue FIPtr = DAG.getFrameIndex(FI,PtrTy);
                SDValue Load = DAG.getLoad(VA.getValVT(),dl,Chain,FIPtr,MachinePointerInfo());
                InVals.push_back(Load);
            }
        }
        return Chain;
    }

SDValue JRISCdevILowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                                     SmallVectorImpl<SDValue> &InVals) const {
  SelectionDAG &DAG = CLI.DAG;
  SDLoc &Loc = CLI.DL;
  SmallVectorImpl<ISD::OutputArg> &Outs = CLI.Outs;
  SmallVectorImpl<SDValue> &OutVals = CLI.OutVals;
  SmallVectorImpl<ISD::InputArg> &Ins = CLI.Ins;
  SDValue Chain = CLI.Chain;
  SDValue Callee = CLI.Callee;
  CallingConv::ID CallConv = CLI.CallConv;
  const bool isVarArg = CLI.IsVarArg;

  CLI.IsTailCall = false;

  if (isVarArg) {
    llvm_unreachable("Unimplemented");
  }
  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), ArgLocs,
                 *DAG.getContext());
  CCInfo.AnalyzeCallOperands(Outs, JRISC_CC);
  Chain = DAG.getCALLSEQ_START(Chain,CCInfo.getStackSize(),0,Loc);
  SmallVector<std::pair<unsigned,SDValue>,8> RegsToPass;
  SmallVector<SDValue,16> MemOpChains;
  for(unsigned i = 0,size = ArgLocs.size();i < size;i+=1){
    CCValAssign &VA = ArgLocs[i];
    SDValue Arg = OutVals[i];
    if(VA.isRegLoc()){
        RegsToPass.push_back(std::make_pair(VA.getLocReg(),Arg));
        continue;
    }

    SDValue StackPtr = DAG.getRegister(JRISCdev::SP,MVT::i32);
    SDValue PtrOff = DAG.getIntPtrConstant(VA.getLocMemOffset(),Loc);
    PtrOff = DAG.getNode(ISD::SUB,Loc,MVT::i32,StackPtr,PtrOff);
    MemOpChains.push_back(DAG.getStore(Chain,Loc,Arg,PtrOff,MachinePointerInfo()));  
  }
  if(!MemOpChains.empty()){
    Chain = DAG.getNode(ISD::TokenFactor,Loc,MVT::Other,MemOpChains);
  }
  SDValue Inflag;
  for(auto &Reg : RegsToPass){
    Chain = DAG.getCopyToReg(Chain,Loc,Reg.first,Reg.second,Inflag);
    Inflag = Chain.getValue(1);
  }

  GlobalAddressSDNode *G = dyn_cast<GlobalAddressSDNode>(Callee);
  Callee = DAG.getGlobalAddress(G->getGlobal(),Loc,getPointerTy(DAG.getDataLayout()),0);
  std::vector<SDValue> Ops;
  Ops.push_back(Chain);
  Ops.push_back(Callee);
  for(auto &Reg : RegsToPass){
    Ops.push_back(DAG.getRegister(Reg.first,Reg.second.getValueType()));
  }

  // Add a register mask operand representing the call-preserved registers.
  const uint32_t *Mask;
  const TargetRegisterInfo *TRI = DAG.getSubtarget().getRegisterInfo();
  Mask = TRI->getCallPreservedMask(DAG.getMachineFunction(), CallConv);

  assert(Mask && "Missing call preserved mask for calling convention");
  Ops.push_back(DAG.getRegisterMask(Mask));

  if (Inflag.getNode()) {
    Ops.push_back(Inflag);
  }

  SDVTList NodeTys = DAG.getVTList(MVT::Other, MVT::Glue);

  // Returns a chain and a flag for retval copy to use.
  Chain = DAG.getNode(JRISCdevID::CAL, Loc, NodeTys, Ops);
  Inflag = Chain.getValue(1);

  Chain = DAG.getCALLSEQ_END(Chain,CCInfo.getStackSize(),0,Inflag,Loc);
  if(!Ins.empty()){
    Inflag = Chain.getValue(1);
  }
  return LowerCallResult(Chain,Inflag,CallConv,isVarArg,Ins,Loc,DAG,InVals);
                                     }

SDValue JRISCdevILowering::LowerCallResult(
    SDValue Chain, SDValue InGlue, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc dl, SelectionDAG &DAG,
    SmallVectorImpl<SDValue> &InVals) const{
        SmallVector<CCValAssign,16> RVLocs;
        CCState CCInfo(CallConv,isVarArg,DAG.getMachineFunction(),RVLocs,*DAG.getContext());
        CCInfo.AnalyzeCallResult(Ins,JRISC_RCC);
        for (auto &Loc : RVLocs){
            if(Loc.isRegLoc()){
                Chain = DAG.getCopyFromReg(Chain,dl,Loc.getLocReg(),Loc.getValVT(),InGlue).getValue(1);
                InGlue = Chain.getValue(2);
                InVals.push_back(Chain.getValue(0));
            }
            else{
                llvm_unreachable("Stack return not implemented");
            }
        }
        return Chain;
    }

bool JRISCdevILowering::CanLowerReturn(CallingConv::ID CallConv,
                              MachineFunction &MF, bool isVarArg,
               const SmallVectorImpl<ISD::OutputArg> &Outs,
               LLVMContext &Context) const{
                SmallVector<CCValAssign,16> RVLocs;
                CCState CCInfo(CallConv,isVarArg,MF,RVLocs,Context);
                if (!CCInfo.CheckReturn(Outs,JRISC_RCC)){
                  return false;
                }
                if(CCInfo.getStackSize() != 0 && isVarArg){
                  return false;
                }
                return true;
               }
SDValue JRISCdevILowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                              bool isVarArg,
                              const SmallVectorImpl<ISD::OutputArg> & Outs,
                              const SmallVectorImpl<SDValue> & OutVals,
                              const SDLoc & dl,
                              SelectionDAG & DAG) const {
    if (isVarArg){
        report_fatal_error("NOT suported?!");
    }

    SmallVector<CCValAssign,16> RVLocs;

    CCState CCInfo(CallConv,isVarArg,DAG.getMachineFunction(),RVLocs,*DAG.getContext());
    CCInfo.AnalyzeReturn(Outs,JRISC_RCC);
    SDValue Flag;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  // Copy the result values into the output registers.
  for (unsigned i = 0, e = RVLocs.size(); i < e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");

    Chain = DAG.getCopyToReg(Chain, dl, VA.getLocReg(), OutVals[i], Flag);

    Flag = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

  RetOps[0] = Chain; // Update chain.

  // Add the flag if we have it.
  if (Flag.getNode()) {
    RetOps.push_back(Flag);
  }

  return DAG.getNode(JRISCdevID::RET_FLAG, dl, MVT::Other, RetOps);
}