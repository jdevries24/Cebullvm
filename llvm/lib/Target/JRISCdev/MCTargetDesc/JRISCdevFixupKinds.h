#ifndef JRISCdev_FIXUPKINDS_H
#define JRISCdev_FIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm{
    namespace JRISCdev{
        enum Fixups{
            FK_PC_REL_24S = FirstTargetFixupKind,
            FK_PC_REL_20S,
            FK_PC_REL_16S,
            FK_PC_REL_32U,
            LastTargetFixupKind,
            NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
        };
    }
}

#endif