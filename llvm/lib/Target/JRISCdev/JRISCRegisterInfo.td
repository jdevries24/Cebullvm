class GPRegister<bits<16> ENC,string n>:Register<n>{
    let HWEncoding = ENC;
    let Namespace = "JRISCdev";
}

def R0:GPRegister<0,"R0">{
    let isConstant = true;
    let AltNames = ["ZERO"];
}

foreach i = 1 - 13 in {
    def R#i: GPRegister<i,"R"#i>;
}

def SP:GPRegister<14,"SP">{
    let AltNames = ["R14"];
}

def RA:GPRegister<15,"RA">{
    let AltNames = ["R15"];
}

def GPregs : RegisterClass<"JRISCdev",[i8,i16,i32],32,(add (sequence "R%i",1,13))>;
def SystemRegs :RegisterClass<"JRISCdev",[i32],32,(add SP,RA)>;

def GPReg : RegisterOperand<GPregs>{
    let GIZeroRegister = R0;
    let EncoderMethod = "encodeRegister";
}