include "llvm/Target/Target.td"

def :Processor<"generic",NoItineraries,[]>;

include "JRISCRegisterInfo.td"
include "JRISCCallingConv.td"
include "JRISCInstrInfo.td"

def JRISCInstrInfo : InstrInfo;

def JRISCdev:Target{
    let InstructionSet = JRISCInstrInfo;
}