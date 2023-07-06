add_llvm_component_group(JRISCdev)
set(LLVM_TARGET_DEFINITIONS JRISCdev.td)
tablegen(LLVM JRISCdevGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(JRISCdevCommonTableGen)


add_llvm_target(JRISCdevCODEGEN
    JRISCdevTargetMachine.cpp

    LINK_COMPONENTS
    Analysis
    AsmPrinter
    CodeGen
    CodeGenTypes
    Core
    GlobalISel
    MC
    SelectionDAG
    Support
    Target
    TargetParser
    JRISCdevInfo

    ADD_TO_COMPONENT
    JRISCdev
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)