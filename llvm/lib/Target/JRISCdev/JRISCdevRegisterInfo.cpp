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
                        return &JRISCdev::GPregsRegClass;
                     }

BitVector JRISCdevRegisterInfo::getReservedRegs(const MachineFunction &MF) const{
    BitVector Reserved(getNumRegs());
    Reserved.set(JRISCdev::RA);
    Reserved.set(JRISCdev::SP);
    Reserved.set(JRISCdev::R0);
    return Reserved;
}

const MCPhysReg *JRISCdevRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const MCPhysReg Saved[] = {JRISCdev::RA,JRISCdev::R8,JRISCdev::R9,JRISCdev::R10,JRISCdev::R11,JRISCdev::R12,JRISCdev::R13,0};
  return Saved;
}

const uint32_t * JRISCdevRegisterInfo::getCallPreservedMask(const MachineFunction &MF,CallingConv::ID) const{
  static uint32_t Preserved = 0;
  const MCPhysReg *saved = getCalleeSavedRegs(&MF);
  for(int i = 0;saved[i];i += 1){
    Preserved |= 1 << ((uint32_t) saved[i]);
  }
  return &Preserved;
}


bool JRISCdevRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                        int SPAdj, unsigned FIOperandNum,
                                        RegScavenger *RS) const
                                        {
                                          MachineInstr &MI = *II;
                                          const MachineFunction &MF = *MI.getParent()->getParent();
                                          const MachineFrameInfo *MFI = &MF.getFrameInfo();
                                          MachineOperand &FIOp = MI.getOperand(FIOperandNum);
                                          unsigned FI = FIOp.getIndex();
                                          MachineOperand &ImmOp = MI.getOperand(FIOperandNum + 1);
                                          int offset = MFI->getObjectOffset(FI) + MFI->getStackSize() + ImmOp.getImm();
                                          FIOp.ChangeToRegister(JRISCdev::SP,false);
                                          ImmOp.setImm(offset);
                                          return true;
                                        }

Register JRISCdevRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return JRISCdev::SP;
}