def memsrc : Operand<i32>{
    let MIOperandInfo = (ops GPReg,i32imm);
    let PrintMethod = "printAddr";
    let MCOperandPredicate = "{if((MCOp.isImm()) && (MCOp.getImm() == 0)){return false;}return true;}";
}

def jmptarget : Operand<OtherVT>;
def branchtarget: Operand<OtherVT>;

def addr : ComplexPattern<i32,2,"SelectAddr",[],[]>;

def JRISCimm16U : Operand<i32>,ImmLeaf<i32,[{
    return (Imm >= 0) & (Imm < 65536);
}]>;

def MathIM : Operand<i32>{
    let MIOperandInfo = (ops i32imm);
    let PrintMethod = "printMathIM";
}

def JRISCimm16N : Operand<i32>,ImmLeaf<i32,[{
    return (Imm > -65536) & (Imm < 0);
}]>{
    let PrintMethod = "printNeg";
}

def JRISCimm16S : Operand<i32>,ImmLeaf<i32,[{
    return (Imm > -32767) & (Imm < 32767);
}]>;

def JRISCimm24U : Operand<i32>,ImmLeaf<i32,[{
    return (Imm >= 0) & (Imm < 1048576);
}]>;

def JRISCimm24S : Operand<i32>,ImmLeaf<i32,[{
    return (Imm > -524228 ) & (Imm < 524228);
}]>;

def load_sym : SDNode<"JRISCdevID::LOAD_SYM",SDTIntUnaryOp>;

def SDT_JRISCdevCallSeqStart : SDCallSeqStart<[SDTCisVT<0,i32>,SDTCisVT<1,i32>]>;
def SDT_JRISCdevCallSeqEnd   : SDCallSeqEnd<[
  SDTCisVT<0, i32>, SDTCisVT<1, i32>
]>;



def JRISC_Global_Ptr : SDTypeProfile<0,1,[SDTCisPtrTy<0>]>;

def JRISCdevRetFlag : SDNode<"JRISCdevID::RET_FLAG",SDTNone,[SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_JRISCdevCallSeqStart,
                           [SDNPHasChain, SDNPOutGlue]>;
def callseq_end   : SDNode<"ISD::CALLSEQ_END",   SDT_JRISCdevCallSeqEnd,
                           [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

def JRISC_call : SDNode<"JRISCdevID::CAL",JRISC_Global_Ptr,[ SDNPHasChain, SDNPOptInGlue, SDNPOutGlue, SDNPVariadic ]>;