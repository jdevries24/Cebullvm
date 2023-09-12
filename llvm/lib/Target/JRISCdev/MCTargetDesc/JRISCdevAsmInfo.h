#ifndef JRISCdev_JRISCdevASMinfo_H
#define JRISCdev_JRISCdevASMinfo_H

#include "llvm/MC/MCAsmInfoELF.h"
#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
class Triple;

class JRISCdevMCAsmInfo : public MCAsmInfo {
  //void anchor() override;

public:
  explicit JRISCdevMCAsmInfo(const Triple &TT);
};

} // namespace llvm

#endif