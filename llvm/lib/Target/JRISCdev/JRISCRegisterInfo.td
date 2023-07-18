class GPRegister<bits<16> ENC,string n>:Register<n>{
    let HWEncoding = ENC;
    let Namespace = "JRISC";
}

def R0:GPRegister<0,"R0">{
    let isConstant = true;
}

foreach i = 1 - 13 in {
    def R#i: GPRegister<i,"R"#i>;
}
def SP:GPRegister<14,"SP">;
def RA:GPRegister<15,"RA">;

def GPregs : RegisterClass<"JRISC",[i32,i16,i8],32,(add (sequence "R%i",0,13),SP,RA)>;

def GPReg : RegisterOperand<GPregs>{
    let GIZeroRegister = R0;
}