include "llvm/Target/Target.td"



include "JRISCRegisterInfo.td"
include "JRISCCallingConv.td"
include "JRISCInstrInfo.td"

def JRISCdevInstrInfo : InstrInfo;
def JRISCdevAsmPrinter : AsmWriter;

def :Processor<"generic",NoItineraries,[]>;


def JRISCdev:Target{
    let InstructionSet = JRISCdevInstrInfo;
    let AssemblyWriters = [JRISCdevAsmPrinter];
}