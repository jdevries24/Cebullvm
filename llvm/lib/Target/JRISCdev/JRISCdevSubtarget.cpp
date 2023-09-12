#include "JRISCdevSubtarget.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/Compression.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/ADT/ArrayRef.h"




using namespace llvm;

#define DEBUG_TYPE "JRISCdev-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "JRISCdevGenSubtargetInfo.inc"

void JRISCdevSubtarget::anchor(){}

JRISCdevSubtarget::JRISCdevSubtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM):JRISCdevGenSubtargetInfo(TT,CPU,CPU,FS),
                                 RegInfo(),ILower(TM,*this),FlInfo(){
                                 }
