include "JRISCdevOperators.td"


class ShortINS<bits<8> opcode,dag outs,dag ins,string asmstr,list<dag> pattern>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Size = 2;
    let Pattern = pattern;
    bits<16> Inst;
    let Inst{15-8} = opcode;
}

class LongINS<bits<8> opcode,dag outs,dag ins,string asmstr,list<dag> pattern>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Size = 4;
    let Pattern = pattern;
    bits<32> Inst;
    let Inst{31-24} = opcode;
}

class MathR <bits<8> opcode,string mem,SDNode opnode>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = (outs GPReg:$dest);
    let InOperandList = (ins GPReg:$src1,GPReg:$src2);
    let AsmString = !strconcat(mem , " $src1,$src2");
    let Pattern = [(set i32:$dest , (opnode i32:$src1 , i32:$src2))];
    let Constraints = "$dest = $src1";
    let Size = 2;
    bits<16> Inst;
    let Inst{15-8} = opcode;
}

class MathI <bits<8> opcode,string mem,SDNode opnode>:LongINS<opcode,(outs GPReg:$dest),(ins GPReg:$src,MathIM:$im),!strconcat(mem, " $dest,$src,$im"),[(set i32:$dest , (opnode i32:$src , JRISCimm16U:$im ))]>;


class JRISC_br<bits<8> opcode,string mem,CondCode cc>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = (outs);
    let InOperandList = (ins GPReg:$s1,GPReg:$s2,jmptarget:$dest);
    let AsmString = !strconcat(mem , " $s1,$s2,$dest");
    let Pattern = [(brcc cc,i32:$s1,i32:$s2,bb:$dest)];
    let Size = 2;
    bits<32> Inst;
    let Inst{31-24} = opcode;
    
}


def ADDI:MathI<0x40,"ADDI",add>;
def SUBI:LongINS<0x41,(outs GPReg:$dest),(ins GPReg:$src,MathIM:$im),"SUBI $dest,$src,$im",[(set i32:$dest , (add i32:$src , JRISCimm16N:$im))]>;
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




class LOADR<bits<8> opcode,string mem,list<dag> pat>:ShortINS<opcode,(outs GPReg:$dest),(ins GPReg:$src),!strconcat(mem , " $dest,$src"),pat>{
    let mayLoad = true;
}

def LDB:LOADR<0x10,"LDB",[(set i32:$dest , (zextloadi8 i32:$src))]>;
def LDBS:LOADR<0x14,"LDBS",[(set i32:$dest , (sextloadi8 i32:$src))]>;
def LDH:LOADR<0x11,"LDH",[(set i32:$dest , (zextloadi16 i32:$src))]>;
def LDHS:LOADR<0x15,"LDHS",[(set i32:$dest , (sextloadi16 i32:$src))]>;
def LDW:LOADR<0x10,"LDW",[(set i32:$dest , (load i32:$src))]>;
def LDWS:LOADR<0x10,"LDWS",[(set i32:$dest , (extload i32:$src))]>;



class LOADI<bits<8> opcode,string mem,list<dag> pat>:LongINS<opcode,(outs GPReg:$dest),(ins memsrc:$src),!strconcat(mem , " $dest,$src"),pat>{
    let mayLoad = true;
}

def LDBI:LOADI<0x10,"LDBI",[(set i32:$dest , (zextloadi8 addr:$src))]>;
def LDBSI:LOADI<0x10,"LDBSI",[(set i32:$dest , (sextloadi8 addr:$src))]>;
def LDHI:LOADI<0x10,"LDHI",[(set i32:$dest , (zextloadi16 addr:$src))]>;
def LDHSI:LOADI<0x10,"LDHSI",[(set i32:$dest , (sextloadi16 addr:$src))]>;
def LDWI:LOADI<0x10,"LDWI",[(set i32:$dest , (load addr:$src))]>;
def LDWSI:LOADI<0x10,"LDWSI",[(set i32:$dest , (extload addr:$src))]>;

class STRR<bits<8> opcode,string mem,list<dag> pat>:ShortINS<opcode,(outs),(ins GPReg:$src , GPReg:$dest),!strconcat(mem , " $src,$dest"),pat>{
    let mayStore = true;
}

def STB:STRR<0x18,"STB",[(truncstorevi8 i32:$src , i32:$dest)]>;
def STH:STRR<0x19,"STH",[(truncstorevi16 i32:$src , i32:$dest)]>;
def STW:STRR<0x1A,"STW",[(store i32:$src , i32:$dest)]>;

class STRI<bits<8> opcode,string mem,list<dag> pat>:LongINS<opcode,(outs),(ins GPReg:$src , memsrc:$dest),!strconcat(mem , " $src,$dest"),pat>{
    let mayStore = true;
}

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

def JMP:LongINS<0x50,(outs),(ins jmptarget:$loc),"JMP $loc",[(br bb:$loc)]>{
    let isBarrier = 1;
    let isTerminator = 1;
    let isBranch = 1;
    }


def RET:ShortINS<0xB0,(outs),(ins),"RET",[(JRISCdevRetFlag)]>{
    let isReturn = true;
    let isTerminator = true;
    let isBarrier = true;
}

def MOV:ShortINS<0x70,(outs GPReg:$dest),(ins GPReg:$src),"MOV $dest,$src",[]>{let isMoveReg = 1;}
def MOVI:LongINS<0x71,(outs GPReg:$dest),(ins i32imm:$im),"MOVI $dest,$im",[]>;
def MOVSI:LongINS<0x73,(outs GPReg:$dest),(ins i32imm:$im),"MOVSI $dest,$im",[]>;
def MOVUI:LongINS<0x72,(outs GPReg:$dest),(ins i32imm:$im),"MOVUI $dest,$im",[]>;
def LEA:LongINS<0x74,(outs GPReg:$dest),(ins i32imm:$loc),"LEA $dest,$loc",[(set i32:$dest ,(load_sym tglobaladdr:$loc))]>;
def CAL:LongINS<0x0A,(outs),(ins i32imm:$loc),"CAL $loc",[(JRISC_call (load_sym tglobaladdr:$loc))]>{let isCall=1;}
def CAR:LongINS<0x0A,(outs),(ins GPReg:$loc),"CAR $loc",[(JRISC_call i32:$loc)]>{let isCall=1;}

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