#include "JRISCdevTargetMachine.h"
#include "JRISCdevAsmOutput.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/LegacyPassManager.h"
#include "TargetInfo/JRISCdevTargetInfo.h"
#include "JRISCdevTargetTransformInfo.h"
#include "llvm/Pass.h"
#include "llvm/CodeGen/AsmPrinter.h"
namespace llvm{

namespace {
class JRISCdevPassConfig : public TargetPassConfig {
public:
  JRISCdevPassConfig(JRISCdevTargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  JRISCdevTargetMachine &getJRISCdevTargetMachine() const {
    return getTM<JRISCdevTargetMachine>();
  }

  bool addInstSelector() override;
  void addPostRegAlloc() override;
};
}

static CodeModel::Model getCM(std::optional<CodeModel::Model> CM){
  return CodeModel::Medium;
}

JRISCdevTargetMachine::JRISCdevTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU,StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT):LLVMTargetMachine(T,"E-p:32:32-i32:32-i16:16-i8:8-i1:8",TT,CPU,FS,Options,Reloc::PIC_,getCM(CM),OL),
                                       subtarget(TT,CPU.str(),FS.str(),*this),TLOF(std::make_unique<TargetLoweringObjectFileELF>()){
                                        initAsmInfo();
                                        TargetTriple.setObjectFormat(Triple::ELF);
                     }

bool JRISCdevTargetMachine::addPassesToEmitFile(
    PassManagerBase &PM, raw_pwrite_stream &Out, raw_pwrite_stream *DwoOut,
    CodeGenFileType FileType, bool DisableVerify,
    MachineModuleInfoWrapperPass *MMIWP){
  // Add common CodeGen passes.
  if (!MMIWP)
    MMIWP = new MachineModuleInfoWrapperPass(this);
  TargetPassConfig *PC = createPassConfig(PM);
  PC->setDisableVerify(DisableVerify);
  PM.add(PC);
  PM.add(MMIWP);
  PC->addISelPasses();
  PC->addMachinePasses();
  PC->setInitialized();
  if (TargetPassConfig::willCompleteCodeGenPipeline()) {
    if(FileType == CodeGenFileType::AssemblyFile){
      if (addCodeFileOut(PM, Out, DwoOut, FileType, MMIWP->getMMI().getContext()))
        return true;
    }
    else{
      if(addAsmPrinter(PM,Out,DwoOut,FileType,MMIWP->getMMI().getContext()))
        return true;
    }
  } else {
    // MIR printing is redundant with -filetype=null.
    if (FileType != CodeGenFileType::Null)
      PM.add(createPrintMIRPass(Out));
  }
 
  PM.add(createFreeMachineFunctionPass());
  return false;
}

bool JRISCdevTargetMachine::addCodeFileOut(PassManagerBase &PM,
                                      raw_pwrite_stream &Out,
                                      raw_pwrite_stream *DwoOut,
                                      CodeGenFileType FileType,
                                      MCContext &Context){
  const MCSubtargetInfo &STI = *getMCSubtargetInfo();
  const MCAsmInfo &MAI = *getMCAsmInfo();
  const MCRegisterInfo &MRI = *getMCRegisterInfo();
  const MCInstrInfo &MII = *getMCInstrInfo();
  if(CodeGenFileType::AssemblyFile == FileType){
    MCInstPrinter *InstPrint = getTarget().createMCInstPrinter(getTargetTriple(),MAI.getAssemblerDialect(),MAI,MII,MRI);
    //std::unique_ptr<MCStreamer> AsmStreamer;
    auto FOut = std::make_unique<formatted_raw_ostream>(Out);
    //MCStreamer *asmPtr = new JRISCdevAsmStreamer(Context,std::move(FOut),InstPrint);
    //AsmStreamer.reset(asmPtr);
    //FunctionPass *PTR = getTarget().createAsmPrinter(*this,std::move(std::move(AsmStreamer)));
    FunctionPass *PTR = new JRISCdevAsmOutput(*this,std::move(FOut),InstPrint);
    if(!PTR){
      return true;
    }
    else{
      PM.add(PTR);
      return false;
    }
    }
  else{
    return true;
  }
}
  


bool JRISCdevPassConfig::addInstSelector(){
  addPass(createJRISCdevISelDag(getJRISCdevTargetMachine(),getOptLevel()));
  return false;
}

void JRISCdevPassConfig::addPostRegAlloc(){
  addPass(createJRISCdevExpandPseudoPass());
}

TargetPassConfig *JRISCdevTargetMachine::createPassConfig(PassManagerBase &PM){
  return new JRISCdevPassConfig(*this,PM);
}

TargetTransformInfo
JRISCdevTargetMachine::getTargetTransformInfo(const Function &F) const {
  return TargetTransformInfo(JRISCdevTTIImpl(this, F));
}


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeJRISCdevTarget() {
  RegisterTargetMachine<JRISCdevTargetMachine> X(getJRISCdev());
}

}
