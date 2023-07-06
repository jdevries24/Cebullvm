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

class LongINS<dag outs,dag ins,string asmstr,list<dag> pattern>:Instruction{
    let Namespace = "JRISCdev";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Size = 32;
    let Pattern = pattern;
    bits<32> instr;
}

class TWOREGINS<bits <8> opcode,string asmstr,list<dag> pattern>:ShortINS<opcode,(outs GPReg:$dest),(ins GPReg:$src),asmstr,pattern>;

class MathR<bits<8> opcode,string asmstr,list<dag> pattern>:ShortINS<opcode,(outs GPReg:$dest),(ins GPReg:$s1, GPReg:$s2),asmstr,pattern>{
    let Constraints = "$dest = $s2";
}

class MathI<bits<8> opcode,string asmstr,list<dag> pattern>:LongINS<(outs GPReg:$dest),(ins GPReg:$src, i32imm:$im),asmstr,pattern>{
    let instr{31-24} = opcode;
}

def ADD:MathR<0x30,"ADD $s1,$s2",[(set i32:$dest, (add i32:$s1,i32:$s2))]>;
def SUB:MathR<0x31,"SUB $s1,$s2",[(set i32:$dest, (sub i32:$s1,i32:$s2))]>;
def AND:MathR<0x32,"AND $s1,$s2",[(set i32:$dest, (and i32:$s1,i32:$s2))]>;
def ORR:MathR<0x33,"ORR $s1,$s2",[(set i32:$dest, (or i32:$s1,i32:$s2))]>;
def XOR:MathR<0x34,"XOR $s1,$s2",[(set i32:$dest, (xor i32:$s1,i32:$s2))]>;
def NOT:TWOREGINS<0x35,"NOT $dest,$src",[(set i32:$dest, (not i32:$src))]>;
//def NEG:MathR<0x36,"NEG $src,$dest",[(set i32:$dest, (Negative i32:$src))]>;
def LSL:MathR<0x37,"LSL $s1,$s2",[(set i32:$dest, (srl i32:$s1,i32:$s2))]>;
def LSR:MathR<0x38,"LSR $s1,$s2",[(set i32:$dest, (sra i32:$s1,i32:$s2))]>;
def MUL:MathR<0x39,"MUL $s1,$s2",[(set i32:$dest, (mul i32:$s1,i32:$s2))]>;
//def SMUL:MathR<0x3A,"SMUL $src,$dest",[(set i32:$dest,i32:$dest)];
def MOD:MathR<0x3B,"MOD $s1,$s2",[(set i32:$dest,(udivrem i32:$s1,i32:$s2))]>;
def SMOD:MathR<0x3C,"SMOD $s1,$s2",[(set i32:$dest,(sdivrem i32:$s1,i32:$s2))]>;
def DIV:MathR<0x3D,"DIV $s1,$s2",[(set i32:$dest,(udiv i32:$s1,i32:$s2))]>;
def SDIV:MathR<0x3F,"SDIV $s1,$s2",[(set i32:$dest,(sdiv i32:$s1,i32:$s2))]>;

//def ADDI:MathI<0x41,"ADDI $src,$dest,$im",[(set i32:$dest, (add i32:$src, i32imm:$im))]>;
