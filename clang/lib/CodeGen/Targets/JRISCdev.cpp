#include "ABIInfoImpl.h"
#include "TargetInfo.h"

using namespace clang;
using namespace clang::CodeGen;

namespace{
    class JRISCdevABIInfo: public DefaultABIInfo{
        public:
            JRISCdevABIInfo(CodeGen::CodeGenTypes &CGT):DefaultABIInfo(CGT){}
    };
}

namespace{
    class JRISCdevCodeGenInfo: public TargetCodeGenInfo{
        public:
            JRISCdevCodeGenInfo(CodeGen::CodeGenTypes &CGT):TargetCodeGenInfo(std::make_unique<JRISCdevABIInfo>(CGT)){}
    };
}

std::unique_ptr<TargetCodeGenInfo> CodeGen::createJRISCdevTargetCodeGenInfo(CodeGenModule &CGM){
    return std::make_unique<JRISCdevCodeGenInfo>(CGM.getTypes());
}