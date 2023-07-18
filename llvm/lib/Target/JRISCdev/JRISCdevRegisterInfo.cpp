#include "JRISCdevRegisterInfo.h"
#include "JRISCdevFrameLowering.h"
#include "JRISCdevSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "JRISCdev-reg-info"
#define GET_REGINFO_TARGET_DESC
#include "JRISCdevGenRegisterInfo.inc"



const TargetRegisterClass * JRISCdevRegisterInfo::getPointerRegClass(const MachineFunction &MF,
                     unsigned Kindm) const{
                        return &JRISC::GPregsRegClass;
                     }

BitVector JRISCdevRegisterInfo::getReservedRegs(const MachineFunction &MF) const{
    BitVector Reserved(getNumRegs());
    Reserved.set(JRISC::RA);
    Reserved.set(JRISC::SP);
    return Reserved;
}

const MCPhysReg*
JRISCdevRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
    return nullptr;
}

bool JRISCdevRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                        int SPAdj, unsigned FIOperandNum,
                                        RegScavenger *RS) const {return false;}

Register JRISCdevRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return JRISC::SP;
}