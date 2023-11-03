add_llvm_component_group(JRISCdev)
set(LLVM_TARGET_DEFINITIONS JRISCdev.td)
tablegen(LLVM JRISCdevGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM JRISCdevGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM JRISCGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM JRISCdevGenCallingConv.inc -gen-callingconv)
tablegen(LLVM JRISCdevGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM JRISCdevGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM JRISCdevGenEmitter.inc -gen-emitter)

add_public_tablegen_target(JRISCdevCommonTableGen)


add_llvm_target(JRISCdevCodeGen
    JRISCdevFrameLowering.cpp
    JRISCdevRegisterInfo.cpp
    JRISCdevISelLowering.cpp
    JRISCdevIselDAGToDAG.cpp
    JRISCdevInstrInfo.cpp
    JRISCdevSubtarget.cpp
    JRISCdevTargetMachine.cpp
    JRISCdevAsmPrinter.cpp
    JRISCdevMClower.cpp
    JRISCdevTargetTransformInfo.cpp
    JRISCdevAsmOutput.cpp
    JRISCdevExpandPseudoInsts.cpp
    
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