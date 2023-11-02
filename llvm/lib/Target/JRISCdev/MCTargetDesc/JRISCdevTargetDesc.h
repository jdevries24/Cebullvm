#ifndef LLVM_LIB_TARGET_JRISCDEV_MCTARGETDESC_JRISCDEVTARGETDESC_H
#define LLVM_LIB_TARGET_JRISCDEV_MCTARGETDESC_JRISCDEVTARGETDESC_H

#include "llvm/Support/DataTypes.h"
#include "MCTargetDesc/JRISCdevInstPrinter.h"
#include "MCTargetDesc/JRISCdevAsmInfo.h"

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
class MCInstPrinter;
class formatted_raw_ostream;

MCCodeEmitter *createJRISCdevCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx);

MCAsmBackend *createJRISCdevAsmBackend(const Target &T,
                                       const MCSubtargetInfo &STI,
                                       const MCRegisterInfo &MRI,
                                       const MCTargetOptions &Options);

MCTargetStreamer *
JRISCdevObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI);

//MCCodeEmitter *createJRISCdevCodeEmitter(MCInstrInfo &l,MCContext &c);

}



#define GET_REGINFO_ENUM
#include "JRISCdevGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "JRISCdevGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "JRISCdevGenSubtargetInfo.inc"

#endif