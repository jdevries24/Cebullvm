
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

JRISCdevILowering::JRISCdevILowering(const TargetMachine &TM,const JRISCdevSubtarget &STI):TargetLowering(TM)
    {
        addRegisterClass(MVT::i32,&JRISC::GPregsRegClass);
        addRegisterClass(MVT::i16,&JRISC::GPregsRegClass);
        addRegisterClass(MVT::i8,&JRISC::GPregsRegClass);
        computeRegisterProperties(STI.getRegisterInfo());
        setOperationAction(ISD::ADD,MVT::i16,Promote);
        setOperationAction(ISD::ADD,MVT::i8,Promote);
        

    }
