#include "JRISCdevInstrInfo.h"
#include "MCTargetDesc/JRISCdevTargetDesc.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "JRISCdevGenInstrInfo.inc"

using namespace llvm;

void JRISCdevInstrInfo::anchor(){}

JRISCdevInstrInfo::JRISCdevInstrInfo():JRISCdevGenInstrInfo(),RI(){}

void JRISCdevInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, const DebugLoc &DL,
                           MCRegister DestReg, MCRegister SrcReg,
                           bool KillSrc) const{
                            BuildMI(MBB,MI,MI->getDebugLoc(),get(JRISCdev::MOV),DestReg).addReg(SrcReg,getKillRegState(KillSrc));
                           }


void JRISCdevInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                   MachineBasicBlock::iterator MI,
                                   Register SrcReg, bool isKill, int FrameIndex,
                                   const TargetRegisterClass *RC,
                                   const TargetRegisterInfo *TRI,
                                   Register VReg) const{ 
                                        BuildMI(MBB,MI,MI->getDebugLoc(),get(JRISCdev::STWI))
                                        .addReg(SrcReg,getKillRegState(isKill))
                                        .addFrameIndex(FrameIndex).addImm(0);
                                   }

void JRISCdevInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                    MachineBasicBlock::iterator MI,
                                    Register DestReg, int FrameIndex,
                                    const TargetRegisterClass *RC,
                                    const TargetRegisterInfo *TRI,
                                    Register VReg) const{
                                        BuildMI(MBB,MI,MI->getDebugLoc(),get(JRISCdev::LDWI),DestReg)
                                        .addFrameIndex(FrameIndex).addImm(0);
                                    

                                    }