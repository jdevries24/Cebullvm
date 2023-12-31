# RUN: llvm-mc --triple=loongarch64 --show-encoding %s | \
# RUN:        FileCheck %s --check-prefixes=CHECK-ENCODING,CHECK-INST
# RUN: llvm-mc --triple=loongarch64 --filetype=obj %s | \
# RUN:        llvm-objdump -d - | FileCheck %s --check-prefix=CHECK-INST

gcsrrd $a0, 1
# CHECK-INST: gcsrrd $a0, 1
# CHECK-ENCODING: encoding: [0x04,0x04,0x00,0x05]

gcsrwr $a0, 1
# CHECK-INST: gcsrwr $a0, 1
# CHECK-ENCODING: encoding: [0x24,0x04,0x00,0x05]

gcsrxchg $a0, $a1, 1
# CHECK-INST: gcsrxchg $a0, $a1, 1
# CHECK-ENCODING: encoding: [0xa4,0x04,0x00,0x05]

gtlbflush
# CHECK-INST: gtlbflush
# CHECK-ENCODING: encoding: [0x01,0x24,0x48,0x06]

hvcl 1
# CHECK-INST: hvcl 1
# CHECK-ENCODING: encoding: [0x01,0x80,0x2b,0x00]
