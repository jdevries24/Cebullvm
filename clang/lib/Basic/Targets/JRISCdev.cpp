#include "JRISCdev.h"

using namespace clang;
using namespace clang::targets;

JRISCTargetInfo::JRISCTargetInfo(const llvm::Triple &Triple, const TargetOptions &):TargetInfo(Triple){
    resetDataLayout("E-p:32:32-i32:32-i16:16-i8:8-i1:8");
            }