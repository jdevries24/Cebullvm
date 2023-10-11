#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY JRISCTargetInfo : public TargetInfo{
    public:
        JRISCTargetInfo(const llvm::Triple &Triple, const TargetOptions &);
          void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override{};
        BuiltinVaListKind getBuiltinVaListKind() const override {return TargetInfo::CharPtrBuiltinVaList;};
        bool validateAsmConstraint(const char*&,ConstraintInfo&)const override{return true;};
        ArrayRef<const char*> getGCCRegNames()const override {return ArrayRef<const char*>();};
        std::string_view getClobbers() const override{return std::string_view();};
        ArrayRef<TargetInfo::GCCRegAlias>getGCCRegAliases() const override{return ArrayRef<TargetInfo::GCCRegAlias>();};
        ArrayRef<Builtin::Info> getTargetBuiltins() const override{return ArrayRef<Builtin::Info>();};
};

}
}