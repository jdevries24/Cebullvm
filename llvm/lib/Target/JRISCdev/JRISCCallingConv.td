def JRISC_CC:CallingConv<[
    CCIfType<[i8,i16,i32],CCAssignToReg<[R2,R3]>>,
    CCIfType<[i32],CCAssignToStack<4,0>>,
    CCIfType<[i16],CCAssignToStack<2,0>>,
    CCIfType<[i8],CCAssignToStack<1,0>>
]>;

def JRISC_RCC:CallingConv<[
    CCIfType<[i8,i16,i32],CCAssignToReg<[R1]>>,
    CCIfType<[i32],CCAssignToStack<4,0>>,
    CCIfType<[i16],CCAssignToStack<2,0>>,
    CCIfType<[i8],CCAssignToStack<1,0>>
]>;