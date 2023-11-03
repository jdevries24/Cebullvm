add_llvm_component_library(LLVMJRISCdevDesc

JRISCdevMCCodeEmitter.cpp
JRISCdevTargetDesc.cpp
JRISCdevAsmInfo.cpp
JRISCdevInstPrinter.cpp
JRISCdevAsmStreamer.cpp
JRISCdevMCAsmBackend.cpp

  LINK_COMPONENTS
  MC
  JRISCdevInfo
  Support

  ADD_TO_COMPONENT
  JRISCdev
  )