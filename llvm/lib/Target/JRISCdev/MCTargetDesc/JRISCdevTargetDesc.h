#ifndef LLVM_LIB_TARGET_JRISCDEV_MCTARGETDESC_JRISCDEVTARGETDESC_H
#define LLVM_LIB_TARGET_JRISCDEV_MCTARGETDESC_JRISCDEVTARGETDESC_H

#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {
class Target;
class MCAsmBackend;
class MCCodeEmitter;
class MCInstrInfo;
class MCSubtargetInfo;
class MCRegisterInfo;
class MCContext;
class MCTargetOptions;
class MCObjectTargetWriter;
class MCStreamer;
class MCTargetStreamer;

/// Creates a machine code emitter for MSP430.
MCCodeEmitter *createJRISCdevCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx);

MCAsmBackend *createJRISCdevAsmBackend(const Target &T,
                                       const MCSubtargetInfo &STI,
                                       const MCRegisterInfo &MRI,
                                       const MCTargetOptions &Options);

MCTargetStreamer *
JRISCdevObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI);
}