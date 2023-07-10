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

class TWORMath<bits<8> opcode,string asmstr,list<dag> pat>:ShortINS<opcode,(outs GPReg:$dest),(ins GPReg:$s1, GPReg:$s2),asmstr,pat>{
    let Constraints = "$dest = $s1";
}


multiclass MathR <bits<8> opcode,string mem,SDNode opnode>{
    def _i32:TWORMath<opcode,!strconcat(mem, " $s1,$s2"),[(set GPReg:$dest , (opnode i32:$s1 , i32:$s2))]>;
    def _i16:TWORMath<opcode,!strconcat(mem, " $s1,$s2"),[(set i16:$dest , (opnode i16:$s1 , i16:$s2))]>;
    def _i8:TWORMath<opcode,!strconcat(mem, " $s1,$s2"),[(set i8:$dest , (opnode i8:$s1 , i8:$s2))]>;
}

multiclass MathI <bits<8> opcode,string mem,SDNode opnode>{
    def _i32:LongINS<opcode,(outs GPReg:$dest),(ins GPReg:$src,i32imm:$im),!strconcat(mem, " $src,$dest,$im"),[(set i32:$dest , (opnode i32:$src , imm:$im ))]>;
    def _i16:LongINS<opcode,(outs GPReg:$dest),(ins GPReg:$src,i16imm:$im),!strconcat(mem, " $src,$dest,$im"),[(set i16:$dest , (opnode i16:$src , imm:$im ))]>;
    def _i8:LongINS<opcode,(outs GPReg:$dest),(ins GPReg:$src,i8imm:$im),!strconcat(mem, " $src,$dest,$im"),[(set i8:$dest , (opnode i8:$src , imm:$im ))]>;
}





defm ADD:MathR<0x30,"ADD",add>;
defm SUB:MathR<0x31,"SUB",sub>;
defm AND:MathR<0x32,"AND",and>;
defm ORR:MathR<0x33,"ORR",or>;
defm XOR:MathR<0x34,"XOR",xor>;
//def NOT:MathR<0x35,"NOT",NOT>;
//def NEG:MathR<0x36,"NEG",NEG>;
defm LSL:MathR<0x37,"LSL",srl>;
defm LSR:MathR<0x38,"LSR",sra>;
defm MUL:MathR<0x39,"MUL",mul>;
//def SMUL:MathR<0x3A,"SMUL",smul>;
defm MOD:MathR<0x3B,"MOD",urem>;
defm SMOD:MathR<0x3C,"SMOD",srem>;
defm DIV:MathR<0x3D,"DIV",udiv>;
defm SDIV:MathR<0x3F,"SDIV",sdiv>;

defm ADDI:MathI<0x40,"ADDI",add>;
defm SUBI:MathI<0x41,"SUBI",sub>;
defm ANDI:MathI<0x42,"ANDI",and>;
defm ORRI:MathI<0x43,"ORRI",or>;
defm XORI:MathR<0x34,"XORI",xor>;
defm LSLI:MathR<0x37,"LSLI",srl>;
defm LSRI:MathR<0x38,"LSRI",sra>;
defm MULI:MathR<0x39,"MULI",mul>;
//def SMUL:MathR<0x3A,"SMUL",smul>;
defm MODI:MathR<0x3B,"MODI",urem>;
defm SMODI:MathR<0x3C,"SMODI",srem>;
defm DIVI:MathR<0x3D,"DIVI",udiv>;
defm SDIVI:MathR<0x3F,"SDIVI",sdiv>;

class LOADR<bits<8> opcode,string mem,list<dag> pat>:ShortINS<opcode,(outs GPReg:$dest),(ins GPReg:$src),!strconcat(mem , " $src,$dest"),pat>{
    let mayLoad = true;
}

def LDB:LOADR<0x10,"LDB",[(set i8:$dest , (zextloadi8 i32:$src))]>;
def LDBS:LOADR<0x14,"LDBS",[(set i8:$dest , (sextloadi8 i32:$src))]>;
def LDH:LOADR<0x11,"LDH",[(set i16:$dest , (zextloadi16 i32:$src))]>;
def LDHS:LOADR<0x15,"LDHS",[(set i16:$dest , (sextloadi16 i32:$src))]>;
def LDW:LOADR<0x10,"LDW",[(set i32:$dest , (zextloadi32 i32:$src))]>;
def LDWS:LOADR<0x10,"LDWS",[(set i8:$dest , (sextloadi32 i32:$src))]>;


class LOADI<bits<8> opcode,string mem,list<dag> pat>:LongINS<opcode,(outs GPReg:$dest),(ins GPReg:$src , i32imm:$im),!strconcat(mem , " $src,$dest,$im"),pat>{
    let mayLoad = true;
}

def LDBI:LOADI<0x10,"LDBI",[(set i8:$dest , (zextloadi8 (add i32:$src,imm:$im)))]>;
def LDBSI:LOADI<0x10,"LDBSI",[(set i8:$dest , (sextloadi8 (add i32:$src,imm:$im)))]>;
def LDHI:LOADI<0x10,"LDHI",[(set i16:$dest , (zextloadi16 (add i32:$src,imm:$im)))]>;
def LDHSI:LOADI<0x10,"LDHSI",[(set i16:$dest , (sextloadi16 (add i32:$src,imm:$im)))]>;
def LDWI:LOADI<0x10,"LDWI",[(set i32:$dest , (zextloadi32 (add i32:$src,imm:$im)))]>;
def LDWSI:LOADI<0x10,"LDWSI",[(set i32:$dest , (sextloadi32 (add i32:$src,imm:$im)))]>;

class STRR<bits<8> opcode,string mem,list<dag> pat>:ShortINS<opcode,(outs),(ins GPReg:$src , GPReg:$dest),!strconcat(mem , " $src,$dest"),pat>{
    let mayStore = true;
}

def STB:STRR<0x18,"STB",[(st i8:$src , i32:$dest)]>;
def STH:STRR<0x19,"STH",[(st i16:$src , i32:$dest)]>;
def STW:STRR<0x1A,"STW",[(st i32:$src , i32:$dest)]>;

class STRI<bits<8> opcode,string mem,list<dag> pat>:LongINS<opcode,(outs),(ins GPReg:$src , GPReg:$dest , i32imm:$im),!strconcat(mem , " $src,$dest,$im"),pat>{
    let mayStore = true;
}

def STBI:STRI<0x28,"STBI",[(st i8:$src , (add i32:$dest,imm:$im))]>;
def STHI:STRI<0x29,"STHI",[(st i16:$src , (add i32:$dest,imm:$im))]>;
def STWI:STRI<0x2A,"STWI",[(st i32:$src , (add i32:$dest,imm:$im))]>;

def RET:ShortINS<0xB0,(outs),(ins),"ret",[]>{
    let isReturn = true;
}