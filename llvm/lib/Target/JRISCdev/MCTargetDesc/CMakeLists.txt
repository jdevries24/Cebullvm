add_llvm_component_library(LLVMJRISCdevDesc

JRISCdevTargetDesc.cpp
  LINK_COMPONENTS
  MC
  JRISCdevInfo
  Support

  ADD_TO_COMPONENT
  JRISCdev
  )