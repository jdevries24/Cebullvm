def JRISC_CC:CallingConv<[
    CCIfType<[i8,i16],CCPromoteToType<i32>>,
    CCIfType<[i32],CCAssignToReg<[R2,R3,R4]>>,
    CCIfType<[i32],CCAssignToStack<4,0>>
]>;

def JRISC_RCC:CallingConv<[
    CCIfType<[i32,i16,i32],CCPromoteToType<i32>>,
    CCIfType<[i32,i16,i32],CCAssignToReg<[R1]>>,
]>;