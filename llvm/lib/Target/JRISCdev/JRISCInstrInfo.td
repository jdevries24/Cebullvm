def jmptarget : Operand<OtherVT>;

class ShortINS<bits<8> opcode,dag outs,dag ins,string asmstr,list<dag> pattern>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Size = 16;
    let Pattern = pattern;
    bits<16> instr;
    let instr{15-8} = opcode;
}

class LongINS<bits<8> opcode,dag outs,dag ins,string asmstr,list<dag> pattern>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Size = 32;
    let Pattern = pattern;
    bits<32> instr;
}

def JRISCimm16U : Operand<i32>,ImmLeaf<i32,[{
    return Imm > = 0 & Imm < 0x10000;
}]>;

def JRISCimm16S : Operand<i32>,ImmLeaf<i32,[{
    return Imm >= -0x7fff && Imm < 0x7fff;
}]>;



class TWORMath<bits<8> opcode,string asmstr,list<dag> pat>:ShortINS<opcode,(outs GPReg:$dest),(ins GPReg:$s1, GPReg:$s2),asmstr,pat>{
    let Constraints = "$dest = $s1";
}

def MOV:ShortINS<0x0F,(outs GPReg:$dest),(ins GPReg:$src),"MOV $src,$dest",[(set i32:$dest,i32:$src)]>;


class MathR <bits<8> opcode,string mem,SDNode opnode>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = (outs GPReg:$dest);
    let InOperandList = (ins GPReg:$s1,GPReg:$s2);
    let AsmString = !strconcat(mem , " $s1,$s2");
    let Constraints = "$dest = $s1";
    let Pattern = [(set i32:$dest , (opnode i32:$s1 , i32:$s2))];
}

class MathI <bits<8> opcode,string mem,SDNode opnode>:LongINS<opcode,(outs GPReg:$dest),(ins GPReg:$src,i32imm:$im),!strconcat(mem, " $src,$dest,$im"),[(set i32:$dest , (opnode i32:$src , JRISCimm16U:$im ))]>;


class JRISC_br<bits<8> opcode,string mem,CondCode cc>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = (outs);
    let InOperandList = (ins GPReg:$s1,GPReg:$s2,jmptarget:$dest);
    let AsmString = !strconcat(mem , " $s1,$s2,$dest");
    let Pattern = [(brcc cc,i32:$s1,i32:$s2,bb:$dest)];
}



def ADD:MathR<0x30,"ADD",add>;
def SUB:MathR<0x31,"SUB",sub>;
def AND:MathR<0x32,"AND",and>;
def ORR:MathR<0x33,"ORR",or>;
def XOR:MathR<0x34,"XOR",xor>;
//def NOT:MathR<0x35,"NOT",NOT>;
//def NEG:MathR<0x36,"NEG",NEG>;
def LSL:MathR<0x37,"LSL",srl>;
def LSR:MathR<0x38,"LSR",sra>;
def MUL:MathR<0x39,"MUL",mul>;
//def SMUL:MathR<0x3A,"SMUL",smul>;
def MOD:MathR<0x3B,"MOD",urem>;
def SMOD:MathR<0x3C,"SMOD",srem>;
def DIV:MathR<0x3D,"DIV",udiv>;
def SDIV:MathR<0x3F,"SDIV",sdiv>;

def ADDI:MathI<0x40,"ADDI",add>;
def SUBI:MathI<0x41,"SUBI",sub>;
def ANDI:MathI<0x42,"ANDI",and>;
def ORRI:MathI<0x43,"ORRI",or>;
def XORI:MathI<0x34,"XORI",xor>;
def LSLI:MathI<0x37,"LSLI",srl>;
def LSRI:MathI<0x38,"LSRI",sra>;
def MULI:MathI<0x39,"MULI",mul>;
//def SMUL:MathR<0x3A,"SMUL",smul>;
def MODI:MathI<0x3B,"MODI",urem>;
def SMODI:MathI<0x3C,"SMODI",srem>;
def DIVI:MathI<0x3D,"DIVI",udiv>;
def SDIVI:MathI<0x3F,"SDIVI",sdiv>;

class LOADR<bits<8> opcode,string mem,list<dag> pat>:ShortINS<opcode,(outs GPReg:$dest),(ins GPReg:$src),!strconcat(mem , " $src,$dest"),pat>{
    let mayLoad = true;
}

def LDB:LOADR<0x10,"LDB",[(set i32:$dest , (zextloadi8 i32:$src))]>;
def LDBS:LOADR<0x14,"LDBS",[(set i32:$dest , (sextloadi8 i32:$src))]>;
def LDH:LOADR<0x11,"LDH",[(set i32:$dest , (zextloadi16 i32:$src))]>;
def LDHS:LOADR<0x15,"LDHS",[(set i32:$dest , (sextloadi16 i32:$src))]>;
def LDW:LOADR<0x10,"LDW",[(set i32:$dest , (zextloadi32 i32:$src))]>;
def LDWS:LOADR<0x10,"LDWS",[(set i32:$dest , (sextloadi32 i32:$src))]>;


class LOADI<bits<8> opcode,string mem,list<dag> pat>:LongINS<opcode,(outs GPReg:$dest),(ins GPReg:$src , i32imm:$im),!strconcat(mem , " $src,$dest,$im"),pat>{
    let mayLoad = true;
}

def LDBI:LOADI<0x10,"LDBI",[(set i32:$dest , (zextloadi8 (add i32:$src,JRISCimm16S:$im)))]>;
def LDBSI:LOADI<0x10,"LDBSI",[(set i32:$dest , (sextloadi8 (add i32:$src,JRISCimm16S:$im)))]>;
def LDHI:LOADI<0x10,"LDHI",[(set i32:$dest , (zextloadi16 (add i32:$src,JRISCimm16S:$im)))]>;
def LDHSI:LOADI<0x10,"LDHSI",[(set i32:$dest , (sextloadi16 (add i32:$src,JRISCimm16S:$im)))]>;
def LDWI:LOADI<0x10,"LDWI",[(set i32:$dest , (zextloadi32 (add i32:$src,JRISCimm16S:$im)))]>;
def LDWSI:LOADI<0x10,"LDWSI",[(set i32:$dest , (sextloadi32 (add i32:$src,JRISCimm16S:$im)))]>;

class STRR<bits<8> opcode,string mem,list<dag> pat>:ShortINS<opcode,(outs),(ins GPReg:$src , GPReg:$dest),!strconcat(mem , " $src,$dest"),pat>{
    let mayStore = true;
}

def STB:STRR<0x18,"STB",[(truncstorevi8 i32:$src , i32:$dest)]>;
def STH:STRR<0x19,"STH",[(truncstorevi16 i32:$src , i32:$dest)]>;
def STW:STRR<0x1A,"STW",[(truncstorevi32 i32:$src , i32:$dest)]>;

class STRI<bits<8> opcode,string mem,list<dag> pat>:LongINS<opcode,(outs),(ins GPReg:$src , GPReg:$dest , i32imm:$im),!strconcat(mem , " $src,$dest,$im"),pat>{
    let mayStore = true;
}

def STBI:STRI<0x28,"STBI",[(truncstorevi8 i32:$src , (add i32:$dest,JRISCimm16S:$im))]>;
def STHI:STRI<0x29,"STHI",[(truncstorevi16 i32:$src , (add i32:$dest,JRISCimm16S:$im))]>;
def STWI:STRI<0x2A,"STWI",[(truncstorevi32 i32:$src , (add i32:$dest,JRISCimm16S:$im))]>;

def JME:JRISC_br<0x51,"JME",SETUEQ>;
def JNE:JRISC_br<0x52,"JNE",SETUNE>;
def JLT:JRISC_br<0x53,"JLT",SETULT>;
def JGT:JRISC_br<0x54,"JGT",SETUGT>;
def JSME:JRISC_br<0x61,"JSME",SETEQ>;
def JSNE:JRISC_br<0x62,"JSNE",SETNE>;
def JSLT:JRISC_br<0x63,"JSLT",SETLT>;
def JSGT:JRISC_br<0x64,"JSGT",SETGT>;

def RET:ShortINS<0xB0,(outs),(ins),"ret",[]>{
    let isReturn = true;
}