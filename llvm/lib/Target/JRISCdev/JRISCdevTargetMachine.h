#ifndef LLVM_LIB_TARGET_JRISCDEV_JRISCDEVTARGETMACHINE_H
#define LLVM_LIB_TARGET_JRISCDEV_JRISCDEVTARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "MCTargetDesc/JRISCdevAsmStreamer.h"
#include "JRISCdevSubtarget.h"
namespace llvm{



class JRISCdevTargetMachine : public LLVMTargetMachine{
    private:
        JRISCdevSubtarget subtarget;
        std::unique_ptr<TargetLoweringObjectFile> TLOF;
    public:
        JRISCdevTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT);
          const JRISCdevSubtarget *getSubtargetImpl(const Function &F) const override {
            const JRISCdevSubtarget *sbinfo = &subtarget;
            assert(sbinfo && "NO subtarget?");
    return sbinfo;
  }
        TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
    TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
  TargetTransformInfo getTargetTransformInfo(const Function &F) const override;
  bool addPassesToEmitFile(
    PassManagerBase &PM, raw_pwrite_stream &Out, raw_pwrite_stream *DwoOut,
    CodeGenFileType FileType, bool DisableVerify,
    MachineModuleInfoWrapperPass *MMIWP) override;
  bool addCodeFileOut(PassManagerBase &PM,
                                      raw_pwrite_stream &Out,
                                      raw_pwrite_stream *DwoOut,
                                      CodeGenFileType FileType,
                                      MCContext &Context);
};

FunctionPass *createJRISCdevISelDag(JRISCdevTargetMachine &TM,CodeGenOptLevel lev);
}

#endif
