.section __FOO,__bitcode
.asciz "Wrong Section"

.section __LLVM,__bitcode
.incbin "llvm.lto.section.bc"
