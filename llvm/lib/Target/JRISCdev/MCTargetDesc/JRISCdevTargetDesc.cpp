#include "TargetInfo/JRISCdevTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

static MCInstrInfo *createJRISCdevMCInstrInfo() {
    return nullptr;
}

static MCRegisterInfo *createJRISCdevMCRegisterInfo(const Triple &TT) {
    return nullptr;
}

static MCAsmInfo *createJRISCdevMCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TT,
                                        const MCTargetOptions &Options) {
    return nullptr;
}

static MCSubtargetInfo *createJRISCdevMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
    return nullptr;
}

static MCInstPrinter *createJRISCdevInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
                                                    return nullptr;
                                                }

MCCodeEmitter *createJRISCdevMCCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx) {
                                            return nullptr;
                                         }

MCAsmBackend *createJRISCdevMCAsmBackend(const Target &T,
                                             const MCSubtargetInfo &STI,
                                             const MCRegisterInfo &MRI,
                                             const MCTargetOptions &Options) {
return nullptr;
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
  TargetRegistry::RegisterMCCodeEmitter(T, createJRISCdevMCCodeEmitter);
  TargetRegistry::RegisterMCAsmBackend(T, createJRISCdevMCAsmBackend);
  TargetRegistry::RegisterObjectTargetStreamer(
      T, createJRISCdevObjectTargetStreamer);
}