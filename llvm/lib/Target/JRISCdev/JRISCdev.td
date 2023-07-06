include "llvm/Target/Target.td"
include "JRISCRegisterInfo.td"
include "JRISCCallingConv.td"
include "JRISCInstrInfo.td"

def JRISCInstrInfo : InstrInfo;

def JRISCdev:Target{
    let InstructionSet = JRISCInstrInfo;
}