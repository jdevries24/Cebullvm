add_llvm_component_library(LLVMJRISCdevInfo
  JRISCdevTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  JRISCdev
  )