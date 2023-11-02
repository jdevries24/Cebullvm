include "JRISCdevOperators.td"


class ShortINS<bits<8> opcode,dag outs,dag ins,string asmstr,list<dag> pattern>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Size = 2;
    let Pattern = pattern;
    bits<16>Inst;
    let Inst{15-8} = opcode;
}

class LongINS<bits<8> opcode,dag outs,dag ins,string asmstr,list<dag> pattern>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Size = 4;
    let Pattern = pattern;
    bits<32>Inst;
    let Inst{31-24} = opcode;
}

class MathR <bits<8> opcode,string mem,SDNode opnode>:Instruction{
    let Namespace = "JRISCdev";
    let Size = 2;
    let OutOperandList = (outs GPReg:$dest);
    let InOperandList = (ins GPReg:$src1,GPReg:$src2);
    bits<4> src1;bits<4> src2;
    let AsmString = !strconcat(mem , " $src1,$src2");
    let Pattern = [(set i32:$dest , (opnode i32:$src1 , i32:$src2))];
    let Constraints = "$dest = $src1";
    let Size = 2;
    bits<16> Inst;
    let Inst{15-8} = opcode;
    let Inst{7-4} = src1;
    let Inst{3-0} = src2;
}

class LDR<bits<8> opcode,string mem,list<dag> pat>:Instruction{
    let Namespace = "JRISCdev";
    let Size = 2;
    let OutOperandList = (outs GPReg:$dest);
    let InOperandList = (ins GPReg:$src);
    let Pattern = pat;
    let AsmString = !strconcat(mem , " $dest,$src");
    bits<16> Inst;
    bits<4> dest;bits<4> src;
    let Inst{15-8} = opcode;
    let Inst{7-4} = dest;
    let Inst{3-0} = src;
    let mayLoad = true;
}

class LOADI<bits<8> opcode,string mem,list<dag> pat>:Instruction{
    let Namespace = "JRISCdev";
    let Size = 4;
    let OutOperandList = (outs GPReg:$dest);
    let InOperandList = (ins memsrc:$src);
    let Pattern = pat;
    let AsmString = !strconcat(mem , " $dest,$src");
    bits<32> Inst;
    bits<4> dest;bits<20> src;
    let Inst{31-24} = opcode;
    let Inst{23-20} = dest;
    let Inst{19-0} = src;
    let mayLoad = true;
}

class STRR<bits<8> opcode,string mem,list<dag> pat>:Instruction{
    let Namespace = "JRISCdev";
    let Size = 2;
    let OutOperandList = (outs);
    let InOperandList = (ins GPReg:$src,GPReg:$dest);
    let Pattern = pat;
    let AsmString = !strconcat(mem , " $src,$dest");
    bits<16> Inst;
    bits<4> dest;bits<4> src;
    let Inst{15-8} = opcode;
    let Inst{7-4} = src;
    let Inst{3-0} = dest;
    let mayStore = true;
}

class STRI<bits<8> opcode,string mem,list<dag> pat>:Instruction{
    let Namespace = "JRISCdev";
    let Size = 2;
    let OutOperandList = (outs);
    let InOperandList = (ins GPReg:$src,memsrc:$dest);
    let Pattern = pat;
    let AsmString = !strconcat(mem , " $src,$dest");
    bits<32> Inst;
    bits<20> dest;bits<4> src;
    let Inst{31-24} = opcode;
    let Inst{23-20} = src;
    let Inst{19-0} = dest;
    let mayStore = true;
}

class MathI <bits<8> opcode,string mem,SDNode opnode,Operand Optype = JRISCimm16U>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = (outs GPReg:$dest);
    let InOperandList = (ins GPReg:$src,MathIM:$im);
    let AsmString = !strconcat(mem, " $dest,$src,$im");
    let Pattern = [(set i32:$dest , (opnode i32:$src , Optype:$im ))];
    let Size = 4;
    bits<32> Inst;
    bits<4> src;bits<4> dest;bits<16>im;
    let Inst{31-24} = opcode;
    let Inst{23-20} = dest;
    let Inst{19-16} = src;
    let Inst{15-0} = im;
}

class JRISC_br<bits<8> opcode,string mem,CondCode cc>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = (outs);
    let InOperandList = (ins GPReg:$s1,GPReg:$s2,branchtarget:$dest);
    let AsmString = !strconcat(mem , " $s1,$s2,$dest");
    let Pattern = [(brcc cc,i32:$s1,i32:$s2,bb:$dest)];
    let Size = 4;
    bits<32> Inst;
    bits<4> s1;bits<4> s2;bits<16>dest;
    let Inst{31-24} = opcode;
    let Inst{23-20} = s1;
    let Inst{19-16} = s2;
    let Inst{15-0} = dest;
    
}


def ADDI:MathI<0x40,"ADDI",add>;
def SUBI:MathI<0x42,"SUBI",add,JRISCimm16N>;
def ANDI:MathI<0x42,"ANDI",and>;
def ORRI:MathI<0x43,"ORRI",or>;
def XORI:MathI<0x44,"XORI",xor>;
def ASLI:MathI<0x45,"ASRI",sra>;
def LSLI:MathI<0x47,"LSLI",shl>;
def LSRI:MathI<0x48,"LSRI",srl>;
def MULI:MathI<0x49,"MULI",mul>;
//def SMUL:MathR<0x3A,"SMUL",smul>;
def MODI:MathI<0x4B,"MODI",urem>;
def SMODI:MathI<0x4C,"SMODI",srem>;
def DIVI:MathI<0x4D,"DIVI",udiv>;
def SDIVI:MathI<0x4F,"SDIVI",sdiv>;

def ADD:MathR<0x30,"ADD",add>;
def SUB:MathR<0x31,"SUB",sub>;
def AND:MathR<0x32,"AND",and>;
def ORR:MathR<0x33,"ORR",or>;
def XOR:MathR<0x34,"XOR",xor>;
//def NOT:MathR<0x35,"NOT",NOT>;
//def NEG:MathR<0x36,"NEG",NEG>;
def LSL:MathR<0x37,"LSL",shl>;
def LSR:MathR<0x38,"LSR",srl>;
def MUL:MathR<0x39,"MUL",mul>;
//def SMUL:MathR<0x3A,"SMUL",smul>;
def MOD:MathR<0x3B,"MOD",urem>;
def SMOD:MathR<0x3C,"SMOD",srem>;
def DIV:MathR<0x3D,"DIV",udiv>;
def SDIV:MathR<0x3F,"SDIV",sdiv>;

def LDB:LDR<0x10,"LDB",[(set i32:$dest , (zextloadi8 i32:$src))]>;
def LDBS:LDR<0x14,"LDBS",[(set i32:$dest , (sextloadi8 i32:$src))]>;
def LDH:LDR<0x11,"LDH",[(set i32:$dest , (zextloadi16 i32:$src))]>;
def LDHS:LDR<0x15,"LDHS",[(set i32:$dest , (sextloadi16 i32:$src))]>;
def LDW:LDR<0x10,"LDW",[(set i32:$dest , (load i32:$src))]>;
def LDWS:LDR<0x10,"LDWS",[(set i32:$dest , (extload i32:$src))]>;

def LDBI:LOADI<0x10,"LDBI",[(set i32:$dest , (zextloadi8 addr:$src))]>;
def LDBSI:LOADI<0x10,"LDBSI",[(set i32:$dest , (sextloadi8 addr:$src))]>;
def LDHI:LOADI<0x10,"LDHI",[(set i32:$dest , (zextloadi16 addr:$src))]>;
def LDHSI:LOADI<0x10,"LDHSI",[(set i32:$dest , (sextloadi16 addr:$src))]>;
def LDWI:LOADI<0x10,"LDWI",[(set i32:$dest , (load addr:$src))]>;
def LDWSI:LOADI<0x10,"LDWSI",[(set i32:$dest , (extload addr:$src))]>;


def STB:STRR<0x18,"STB",[(truncstorevi8 i32:$src , i32:$dest)]>;
def STH:STRR<0x19,"STH",[(truncstorevi16 i32:$src , i32:$dest)]>;
def STW:STRR<0x1A,"STW",[(store i32:$src , i32:$dest)]>;

def STBI:STRI<0x28,"STBI",[(truncstorevi8 i32:$src , addr:$dest)]>;
def STHI:STRI<0x29,"STHI",[(truncstorevi16 i32:$src , addr:$dest)]>;
def STWI:STRI<0x2A,"STWI",[(store i32:$src , addr:$dest)]>;


let isTerminator = 1,isBranch = 1 in {
def JNE:JRISC_br<0x52,"JNE",SETUNE>;
def JME:JRISC_br<0x51,"JME",SETUEQ>;
def JLT:JRISC_br<0x53,"JLT",SETULT>;
def JGT:JRISC_br<0x54,"JGT",SETUGT>;
def JSNE:JRISC_br<0x62,"JSNE",SETNE>;
def JSME:JRISC_br<0x61,"JSME",SETEQ>;
def JSLT:JRISC_br<0x63,"JSLT",SETLT>;
def JSGT:JRISC_br<0x64,"JSGT",SETGT>;
}



def JMP:Instruction{
    let Namespace = "JRISCdev";
    let Size = 4;
    let InOperandList = (ins jmptarget:$loc);
    let OutOperandList = (outs);
    let AsmString = "JMP $loc";
    let Pattern = [(br bb:$loc)];
    bits<32> Inst;
    let Inst{31-24} = 0x50;
    bits<24> loc;
    let Inst{23-0} = loc;
    let isBranch = true;
    let isTerminator = true;
    let isBarrier = true;
}


def RET:Instruction{
    let Namespace = "JRISCdev";
    let Size = 2;
    let InOperandList = (ins);
    let OutOperandList = (outs);
    let AsmString = "RET";
    let Pattern = [(JRISCdevRetFlag)];
    bits<16> Inst = 0xB000;
    let isReturn = true;
    let isTerminator = true;
    let isBarrier = true;
}

def MOV:Instruction{
    let Namespace = "JRISCdev";
    let Size = 2;
    let InOperandList = (ins GPReg:$src);
    let OutOperandList = (outs GPReg:$dest);
    let AsmString = "MOV $dest,$src";
    let Pattern = [];
    bits<16> Inst;
    bits<4> dest;bits<4> src;
    let Inst{15-8} = 0x4f;
    let Inst{7-4} = dest;
    let Inst{3-0} = src;
}

//def LEA:LongINS<0x74,(outs GPReg:$dest),(ins i32imm:$loc),"LEA $dest,$loc",[(set i32:$dest ,(load_sym tglobaladdr:$loc))]>;
def LEA:Instruction{
    let Namespace = "JRISCdev";
    let Size = 4;
    let InOperandList = (ins JRISCimm24S:$loc);
    let OutOperandList = (outs GPReg:$dest);
    let AsmString = "LEA $dest,$loc";
    let Pattern = [(set i32:$dest ,(load_sym tglobaladdr:$loc))];
    bits<32> Inst;
    bits<20> loc;
    bits<4> dest;
    let Inst{31-24} = 0x74;
    let Inst{23-20} = dest;
    let Inst{19-0} = loc;
    let isCall = 1;
}

//def CAL:LongINS<0x0A,(outs),(ins JRISCimm24S:$loc),"CAL $loc",[(JRISC_call (load_sym tglobaladdr:$loc))]>{let isCall=1;}
def CAL:Instruction{
    let Namespace = "JRISCdev";
    let Size = 4;
    let InOperandList = (ins JRISCimm24S:$loc);
    let OutOperandList = (outs);
    let AsmString = "CAL $loc";
    let Pattern = [(JRISC_call (load_sym tglobaladdr:$loc))];
    bits<32> Inst;
    bits<24> loc;
    let Inst{31-24} = 0xA0;
    let Inst{23-0} = loc;
    let isCall = 1;
}

//def CAR:LongINS<0x0A,(outs),(ins GPReg:$loc),"CAR $loc",[(JRISC_call i32:$loc)]>{let isCall=1;}

def CAR:Instruction{
    let Namespace = "JRISCdev";
    let Size = 4;
    let InOperandList = (ins GPReg:$loc);
    let OutOperandList = (outs);
    let AsmString = "CAR $loc";
    let Pattern = [(JRISC_call i32:$loc)];
    bits<16> Inst;
    bits<4> loc;
    let Inst{15-8} = 0xA0;
    let Inst{8-4} = 0;
    let Inst{3-0} = loc;
    let isCall = 1;
}




class SEL_PAT<CondCode cc,string CondStr>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = (outs GPReg:$res);
    let InOperandList = (ins GPReg:$cond1,GPReg:$cond2,GPReg:$true,GPReg:$false);
    let AsmString = !strconcat("$res = ($cond1 ",CondStr, " $cond2) ? $true : $false");
    let Pattern = [(set i32:$res , (selectcc i32:$cond1, i32:$cond2 , i32:$true, i32:$false,cc))];
}




let isPseudo = 1 in {
def SELECT_LT:SEL_PAT<SETULT,"LT">;
def SELECT_SLT:SEL_PAT<SETLT,"SLT">;
def SELECT_EQ:SEL_PAT<SETEQ,"EQ">;
def SELECT_NE:SEL_PAT<SETNE,"NE">;
def SELECT_GT:SEL_PAT<SETUGT,"GT">;
def SELECT_SGT:SEL_PAT<SETGT,"SGT">;
def CALLSTACKDOWN : LongINS<0x00,(outs),(ins i32imm:$amt,i32imm:$amt2),"ERROR!",[(callseq_start timm:$amt,timm:$amt2)]>;
def CALLSTACKUP:LongINS<0x00,(outs),(ins i32imm:$amt,i32imm:$amt2),"ERROR!",[(callseq_end timm:$amt,timm:$amt2)]>;
}