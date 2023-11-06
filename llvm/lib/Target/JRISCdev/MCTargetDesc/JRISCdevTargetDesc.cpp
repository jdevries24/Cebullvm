#include "TargetInfo/JRISCdevTargetInfo.h"
#include "JRISCdevTargetDesc.h"
#include "MCTargetDesc/JRISCdevTargetDesc.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/Support/FormattedStream.h"
using namespace llvm;



#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "JRISCdevGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "JRISCdevGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "JRISCdevGenRegisterInfo.inc"

static MCInstrInfo *createJRISCdevMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitJRISCdevMCInstrInfo(X);
  return X;
}


static MCRegisterInfo *createJRISCdevMCRegisterInfo(const Triple &TT) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitJRISCdevMCRegisterInfo(X,0);
    return X;
}

static MCAsmInfo *createJRISCdevMCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TT,
                                        const MCTargetOptions &Options) {
    MCAsmInfo *X = new JRISCdevMCAsmInfo(TT);
    return X;
}

static MCSubtargetInfo *createJRISCdevMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
    MCSubtargetInfo *X = createJRISCdevMCSubtargetInfoImpl(TT,CPU,CPU,FS);
    return X;
}

static MCInstPrinter *createJRISCdevInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
    MCInstPrinter *X = new JRISCdevInstPrinter(MAI,MII,MRI);
    return X;
                                          }

/*
static MCTargetStreamer *createJRISCdevASMTargetStreamer(MCStreamer &S,formatted_raw_ostream &OS,MCInstPrinter *InstPrint,bool isVerbose){
  JRISCdevAsmStreamer NS(S.getContext(),OS,InstPrint);
  S = NS;
  return nullptr;
}
*/

/*
MCCodeEmitter *createJRISCdevMCCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx) {
                                          return createJRISCdevCodeEmitter(MCII,Ctx);
                                         }

*/

MCAsmBackend *createJRISCdevBackend(const Target &T,
                                             const MCSubtargetInfo &STI,
                                             const MCRegisterInfo &MRI,
                                             const MCTargetOptions &Options) {
return createJRISCdevAsmBackend(T,STI,MRI,Options);
}

/*
static MCTargetStreamer *createJRISCdevAsmStreamer(MCStreamer &S,formatted_raw_ostream &OS,MCInstPrinter *InstPrint,bool IsVerboseAsm){
  return new JRISCdevAsmStreamer(S);
}
*/

MCCodeEmitter *CreateE(const MCInstrInfo &MCII,MCContext &Ctx){
  return createJRISCdevCodeEmitter(MCII,Ctx);
}

MCTargetStreamer *
createJRISCdevObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
    return nullptr;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCdevTargetMC() {
  Target &T = getJRISCdev();
  TargetRegistry::RegisterMCAsmInfo(T, createJRISCdevMCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(T, createJRISCdevMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(T, createJRISCdevMCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(T, createJRISCdevMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(T, createJRISCdevInstPrinter);
  TargetRegistry::RegisterMCCodeEmitter(T, CreateE);
  TargetRegistry::RegisterMCAsmBackend(T, createJRISCdevBackend);
  //lsTargetRegistry::RegisterObjectTargetStreamer(T, createJRISCdevObjectTargetStreamer);
}