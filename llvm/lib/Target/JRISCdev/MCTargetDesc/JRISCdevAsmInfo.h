#ifndef JRISCdev_JRISCdevASMinfo_H
#define JRISCdev_JRISCdevASMinfo_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class JRISCdevMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit JRISCdevMCAsmInfo(const Triple &TT);
};

} // namespace llvm

#endif