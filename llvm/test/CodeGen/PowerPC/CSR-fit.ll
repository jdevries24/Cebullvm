; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mcpu=pwr8 -mtriple=powerpc64le-unknown-unknown \
; RUN:   -ppc-vsr-nums-as-vr -ppc-asm-full-reg-names < %s | FileCheck --check-prefix=CHECK-PWR8 %s
; RUN: llc -mcpu=pwr9 -mtriple=powerpc64le-unknown-unknown \
; RUN:   -ppc-vsr-nums-as-vr -ppc-asm-full-reg-names < %s | FileCheck --check-prefix=CHECK-PWR9 %s


declare signext i32 @callee(i32 signext) local_unnamed_addr

define dso_local signext i32 @caller1(i32 signext %a, i32 signext %b) local_unnamed_addr {
; CHECK-PWR8-LABEL: caller1:
; CHECK-PWR8:       # %bb.0: # %entry
; CHECK-PWR8-NEXT:    mflr r0
; CHECK-PWR8-NEXT:    .cfi_def_cfa_offset 176
; CHECK-PWR8-NEXT:    .cfi_offset lr, 16
; CHECK-PWR8-NEXT:    .cfi_offset r14, -144
; CHECK-PWR8-NEXT:    .cfi_offset r15, -136
; CHECK-PWR8-NEXT:    std r14, -144(r1) # 8-byte Folded Spill
; CHECK-PWR8-NEXT:    std r15, -136(r1) # 8-byte Folded Spill
; CHECK-PWR8-NEXT:    stdu r1, -176(r1)
; CHECK-PWR8-NEXT:    #APP
; CHECK-PWR8-NEXT:    add r3, r3, r4
; CHECK-PWR8-NEXT:    #NO_APP
; CHECK-PWR8-NEXT:    extsw r3, r3
; CHECK-PWR8-NEXT:    std r0, 192(r1)
; CHECK-PWR8-NEXT:    bl callee
; CHECK-PWR8-NEXT:    nop
; CHECK-PWR8-NEXT:    addi r1, r1, 176
; CHECK-PWR8-NEXT:    ld r0, 16(r1)
; CHECK-PWR8-NEXT:    ld r15, -136(r1) # 8-byte Folded Reload
; CHECK-PWR8-NEXT:    ld r14, -144(r1) # 8-byte Folded Reload
; CHECK-PWR8-NEXT:    mtlr r0
; CHECK-PWR8-NEXT:    blr
;
; CHECK-PWR9-LABEL: caller1:
; CHECK-PWR9:       # %bb.0: # %entry
; CHECK-PWR9-NEXT:    mflr r0
; CHECK-PWR9-NEXT:    .cfi_def_cfa_offset 176
; CHECK-PWR9-NEXT:    .cfi_offset lr, 16
; CHECK-PWR9-NEXT:    .cfi_offset r14, -144
; CHECK-PWR9-NEXT:    .cfi_offset r15, -136
; CHECK-PWR9-NEXT:    std r14, -144(r1) # 8-byte Folded Spill
; CHECK-PWR9-NEXT:    std r15, -136(r1) # 8-byte Folded Spill
; CHECK-PWR9-NEXT:    stdu r1, -176(r1)
; CHECK-PWR9-NEXT:    #APP
; CHECK-PWR9-NEXT:    add r3, r3, r4
; CHECK-PWR9-NEXT:    #NO_APP
; CHECK-PWR9-NEXT:    extsw r3, r3
; CHECK-PWR9-NEXT:    std r0, 192(r1)
; CHECK-PWR9-NEXT:    bl callee
; CHECK-PWR9-NEXT:    nop
; CHECK-PWR9-NEXT:    addi r1, r1, 176
; CHECK-PWR9-NEXT:    ld r0, 16(r1)
; CHECK-PWR9-NEXT:    ld r15, -136(r1) # 8-byte Folded Reload
; CHECK-PWR9-NEXT:    ld r14, -144(r1) # 8-byte Folded Reload
; CHECK-PWR9-NEXT:    mtlr r0
; CHECK-PWR9-NEXT:    blr
entry:
  %0 = tail call i32 asm "add $0, $1, $2", "=r,r,r,~{r14},~{r15}"(i32 %a, i32 %b)
  %call = tail call signext i32 @callee(i32 signext %0)
  ret i32 %call
}

define dso_local signext i32 @caller2(i32 signext %a, i32 signext %b) local_unnamed_addr {
; CHECK-PWR8-LABEL: caller2:
; CHECK-PWR8:       # %bb.0: # %entry
; CHECK-PWR8-NEXT:    mflr r0
; CHECK-PWR8-NEXT:    .cfi_def_cfa_offset 176
; CHECK-PWR8-NEXT:    .cfi_offset lr, 16
; CHECK-PWR8-NEXT:    .cfi_offset f14, -144
; CHECK-PWR8-NEXT:    .cfi_offset f15, -136
; CHECK-PWR8-NEXT:    stfd f14, -144(r1) # 8-byte Folded Spill
; CHECK-PWR8-NEXT:    stfd f15, -136(r1) # 8-byte Folded Spill
; CHECK-PWR8-NEXT:    stdu r1, -176(r1)
; CHECK-PWR8-NEXT:    #APP
; CHECK-PWR8-NEXT:    add r3, r3, r4
; CHECK-PWR8-NEXT:    #NO_APP
; CHECK-PWR8-NEXT:    extsw r3, r3
; CHECK-PWR8-NEXT:    std r0, 192(r1)
; CHECK-PWR8-NEXT:    bl callee
; CHECK-PWR8-NEXT:    nop
; CHECK-PWR8-NEXT:    addi r1, r1, 176
; CHECK-PWR8-NEXT:    ld r0, 16(r1)
; CHECK-PWR8-NEXT:    lfd f15, -136(r1) # 8-byte Folded Reload
; CHECK-PWR8-NEXT:    lfd f14, -144(r1) # 8-byte Folded Reload
; CHECK-PWR8-NEXT:    mtlr r0
; CHECK-PWR8-NEXT:    blr
;
; CHECK-PWR9-LABEL: caller2:
; CHECK-PWR9:       # %bb.0: # %entry
; CHECK-PWR9-NEXT:    mflr r0
; CHECK-PWR9-NEXT:    .cfi_def_cfa_offset 176
; CHECK-PWR9-NEXT:    .cfi_offset lr, 16
; CHECK-PWR9-NEXT:    .cfi_offset f14, -144
; CHECK-PWR9-NEXT:    .cfi_offset f15, -136
; CHECK-PWR9-NEXT:    stfd f14, -144(r1) # 8-byte Folded Spill
; CHECK-PWR9-NEXT:    stfd f15, -136(r1) # 8-byte Folded Spill
; CHECK-PWR9-NEXT:    stdu r1, -176(r1)
; CHECK-PWR9-NEXT:    #APP
; CHECK-PWR9-NEXT:    add r3, r3, r4
; CHECK-PWR9-NEXT:    #NO_APP
; CHECK-PWR9-NEXT:    extsw r3, r3
; CHECK-PWR9-NEXT:    std r0, 192(r1)
; CHECK-PWR9-NEXT:    bl callee
; CHECK-PWR9-NEXT:    nop
; CHECK-PWR9-NEXT:    addi r1, r1, 176
; CHECK-PWR9-NEXT:    ld r0, 16(r1)
; CHECK-PWR9-NEXT:    lfd f15, -136(r1) # 8-byte Folded Reload
; CHECK-PWR9-NEXT:    lfd f14, -144(r1) # 8-byte Folded Reload
; CHECK-PWR9-NEXT:    mtlr r0
; CHECK-PWR9-NEXT:    blr
entry:
  %0 = tail call i32 asm "add $0, $1, $2", "=r,r,r,~{f14},~{f15}"(i32 %a, i32 %b)
  %call = tail call signext i32 @callee(i32 signext %0)
  ret i32 %call
}

define dso_local signext i32 @caller3(i32 signext %a, i32 signext %b) local_unnamed_addr {
; CHECK-PWR8-LABEL: caller3:
; CHECK-PWR8:       # %bb.0: # %entry
; CHECK-PWR8-NEXT:    mflr r0
; CHECK-PWR8-NEXT:    stdu r1, -240(r1)
; CHECK-PWR8-NEXT:    std r0, 256(r1)
; CHECK-PWR8-NEXT:    .cfi_def_cfa_offset 240
; CHECK-PWR8-NEXT:    .cfi_offset lr, 16
; CHECK-PWR8-NEXT:    .cfi_offset v20, -192
; CHECK-PWR8-NEXT:    .cfi_offset v21, -176
; CHECK-PWR8-NEXT:    li r5, 48
; CHECK-PWR8-NEXT:    stvx v20, r1, r5 # 16-byte Folded Spill
; CHECK-PWR8-NEXT:    li r5, 64
; CHECK-PWR8-NEXT:    stvx v21, r1, r5 # 16-byte Folded Spill
; CHECK-PWR8-NEXT:    #APP
; CHECK-PWR8-NEXT:    add r3, r3, r4
; CHECK-PWR8-NEXT:    #NO_APP
; CHECK-PWR8-NEXT:    extsw r3, r3
; CHECK-PWR8-NEXT:    bl callee
; CHECK-PWR8-NEXT:    nop
; CHECK-PWR8-NEXT:    li r4, 64
; CHECK-PWR8-NEXT:    lvx v21, r1, r4 # 16-byte Folded Reload
; CHECK-PWR8-NEXT:    li r4, 48
; CHECK-PWR8-NEXT:    lvx v20, r1, r4 # 16-byte Folded Reload
; CHECK-PWR8-NEXT:    addi r1, r1, 240
; CHECK-PWR8-NEXT:    ld r0, 16(r1)
; CHECK-PWR8-NEXT:    mtlr r0
; CHECK-PWR8-NEXT:    blr
;
; CHECK-PWR9-LABEL: caller3:
; CHECK-PWR9:       # %bb.0: # %entry
; CHECK-PWR9-NEXT:    mflr r0
; CHECK-PWR9-NEXT:    stdu r1, -224(r1)
; CHECK-PWR9-NEXT:    std r0, 240(r1)
; CHECK-PWR9-NEXT:    .cfi_def_cfa_offset 224
; CHECK-PWR9-NEXT:    .cfi_offset lr, 16
; CHECK-PWR9-NEXT:    .cfi_offset v20, -192
; CHECK-PWR9-NEXT:    .cfi_offset v21, -176
; CHECK-PWR9-NEXT:    stxv v20, 32(r1) # 16-byte Folded Spill
; CHECK-PWR9-NEXT:    stxv v21, 48(r1) # 16-byte Folded Spill
; CHECK-PWR9-NEXT:    #APP
; CHECK-PWR9-NEXT:    add r3, r3, r4
; CHECK-PWR9-NEXT:    #NO_APP
; CHECK-PWR9-NEXT:    extsw r3, r3
; CHECK-PWR9-NEXT:    bl callee
; CHECK-PWR9-NEXT:    nop
; CHECK-PWR9-NEXT:    lxv v21, 48(r1) # 16-byte Folded Reload
; CHECK-PWR9-NEXT:    lxv v20, 32(r1) # 16-byte Folded Reload
; CHECK-PWR9-NEXT:    addi r1, r1, 224
; CHECK-PWR9-NEXT:    ld r0, 16(r1)
; CHECK-PWR9-NEXT:    mtlr r0
; CHECK-PWR9-NEXT:    blr
entry:
  %0 = tail call i32 asm "add $0, $1, $2", "=r,r,r,~{v20},~{v21}"(i32 %a, i32 %b)
  %call = tail call signext i32 @callee(i32 signext %0)
  ret i32 %call
}

define dso_local signext i32 @caller4(i32 signext %a, i32 signext %b) local_unnamed_addr {
; CHECK-PWR8-LABEL: caller4:
; CHECK-PWR8:       # %bb.0: # %entry
; CHECK-PWR8-NEXT:    mflr r0
; CHECK-PWR8-NEXT:    stdu r1, -240(r1)
; CHECK-PWR8-NEXT:    std r0, 256(r1)
; CHECK-PWR8-NEXT:    .cfi_def_cfa_offset 240
; CHECK-PWR8-NEXT:    .cfi_offset lr, 16
; CHECK-PWR8-NEXT:    .cfi_offset v20, -192
; CHECK-PWR8-NEXT:    .cfi_offset v21, -176
; CHECK-PWR8-NEXT:    li r5, 48
; CHECK-PWR8-NEXT:    stvx v20, r1, r5 # 16-byte Folded Spill
; CHECK-PWR8-NEXT:    li r5, 64
; CHECK-PWR8-NEXT:    stvx v21, r1, r5 # 16-byte Folded Spill
; CHECK-PWR8-NEXT:    #APP
; CHECK-PWR8-NEXT:    add r3, r3, r4
; CHECK-PWR8-NEXT:    #NO_APP
; CHECK-PWR8-NEXT:    extsw r3, r3
; CHECK-PWR8-NEXT:    bl callee
; CHECK-PWR8-NEXT:    nop
; CHECK-PWR8-NEXT:    li r4, 64
; CHECK-PWR8-NEXT:    lvx v21, r1, r4 # 16-byte Folded Reload
; CHECK-PWR8-NEXT:    li r4, 48
; CHECK-PWR8-NEXT:    lvx v20, r1, r4 # 16-byte Folded Reload
; CHECK-PWR8-NEXT:    addi r1, r1, 240
; CHECK-PWR8-NEXT:    ld r0, 16(r1)
; CHECK-PWR8-NEXT:    mtlr r0
; CHECK-PWR8-NEXT:    blr
;
; CHECK-PWR9-LABEL: caller4:
; CHECK-PWR9:       # %bb.0: # %entry
; CHECK-PWR9-NEXT:    mflr r0
; CHECK-PWR9-NEXT:    stdu r1, -224(r1)
; CHECK-PWR9-NEXT:    std r0, 240(r1)
; CHECK-PWR9-NEXT:    .cfi_def_cfa_offset 224
; CHECK-PWR9-NEXT:    .cfi_offset lr, 16
; CHECK-PWR9-NEXT:    .cfi_offset v20, -192
; CHECK-PWR9-NEXT:    .cfi_offset v21, -176
; CHECK-PWR9-NEXT:    stxv v20, 32(r1) # 16-byte Folded Spill
; CHECK-PWR9-NEXT:    stxv v21, 48(r1) # 16-byte Folded Spill
; CHECK-PWR9-NEXT:    #APP
; CHECK-PWR9-NEXT:    add r3, r3, r4
; CHECK-PWR9-NEXT:    #NO_APP
; CHECK-PWR9-NEXT:    extsw r3, r3
; CHECK-PWR9-NEXT:    bl callee
; CHECK-PWR9-NEXT:    nop
; CHECK-PWR9-NEXT:    lxv v21, 48(r1) # 16-byte Folded Reload
; CHECK-PWR9-NEXT:    lxv v20, 32(r1) # 16-byte Folded Reload
; CHECK-PWR9-NEXT:    addi r1, r1, 224
; CHECK-PWR9-NEXT:    ld r0, 16(r1)
; CHECK-PWR9-NEXT:    mtlr r0
; CHECK-PWR9-NEXT:    blr
entry:
  %0 = tail call i32 asm "add $0, $1, $2", "=r,r,r,~{vs52},~{vs53}"(i32 %a, i32 %b)
  %call = tail call signext i32 @callee(i32 signext %0)
  ret i32 %call
}

define dso_local signext i32 @caller_mixed(i32 signext %a, i32 signext %b) local_unnamed_addr {
; CHECK-PWR8-LABEL: caller_mixed:
; CHECK-PWR8:       # %bb.0: # %entry
; CHECK-PWR8-NEXT:    mflr r0
; CHECK-PWR8-NEXT:    stdu r1, -528(r1)
; CHECK-PWR8-NEXT:    std r0, 544(r1)
; CHECK-PWR8-NEXT:    .cfi_def_cfa_offset 528
; CHECK-PWR8-NEXT:    .cfi_offset lr, 16
; CHECK-PWR8-NEXT:    .cfi_offset r14, -288
; CHECK-PWR8-NEXT:    .cfi_offset f14, -144
; CHECK-PWR8-NEXT:    .cfi_offset v20, -480
; CHECK-PWR8-NEXT:    .cfi_offset v21, -464
; CHECK-PWR8-NEXT:    li r5, 48
; CHECK-PWR8-NEXT:    std r14, 240(r1) # 8-byte Folded Spill
; CHECK-PWR8-NEXT:    stfd f14, 384(r1) # 8-byte Folded Spill
; CHECK-PWR8-NEXT:    stvx v20, r1, r5 # 16-byte Folded Spill
; CHECK-PWR8-NEXT:    li r5, 64
; CHECK-PWR8-NEXT:    stvx v21, r1, r5 # 16-byte Folded Spill
; CHECK-PWR8-NEXT:    #APP
; CHECK-PWR8-NEXT:    add r3, r3, r4
; CHECK-PWR8-NEXT:    #NO_APP
; CHECK-PWR8-NEXT:    extsw r3, r3
; CHECK-PWR8-NEXT:    bl callee
; CHECK-PWR8-NEXT:    nop
; CHECK-PWR8-NEXT:    li r4, 64
; CHECK-PWR8-NEXT:    lfd f14, 384(r1) # 8-byte Folded Reload
; CHECK-PWR8-NEXT:    ld r14, 240(r1) # 8-byte Folded Reload
; CHECK-PWR8-NEXT:    lvx v21, r1, r4 # 16-byte Folded Reload
; CHECK-PWR8-NEXT:    li r4, 48
; CHECK-PWR8-NEXT:    lvx v20, r1, r4 # 16-byte Folded Reload
; CHECK-PWR8-NEXT:    addi r1, r1, 528
; CHECK-PWR8-NEXT:    ld r0, 16(r1)
; CHECK-PWR8-NEXT:    mtlr r0
; CHECK-PWR8-NEXT:    blr
;
; CHECK-PWR9-LABEL: caller_mixed:
; CHECK-PWR9:       # %bb.0: # %entry
; CHECK-PWR9-NEXT:    mflr r0
; CHECK-PWR9-NEXT:    stdu r1, -512(r1)
; CHECK-PWR9-NEXT:    std r0, 528(r1)
; CHECK-PWR9-NEXT:    .cfi_def_cfa_offset 512
; CHECK-PWR9-NEXT:    .cfi_offset lr, 16
; CHECK-PWR9-NEXT:    .cfi_offset r14, -288
; CHECK-PWR9-NEXT:    .cfi_offset f14, -144
; CHECK-PWR9-NEXT:    .cfi_offset v20, -480
; CHECK-PWR9-NEXT:    .cfi_offset v21, -464
; CHECK-PWR9-NEXT:    std r14, 224(r1) # 8-byte Folded Spill
; CHECK-PWR9-NEXT:    stfd f14, 368(r1) # 8-byte Folded Spill
; CHECK-PWR9-NEXT:    stxv v20, 32(r1) # 16-byte Folded Spill
; CHECK-PWR9-NEXT:    stxv v21, 48(r1) # 16-byte Folded Spill
; CHECK-PWR9-NEXT:    #APP
; CHECK-PWR9-NEXT:    add r3, r3, r4
; CHECK-PWR9-NEXT:    #NO_APP
; CHECK-PWR9-NEXT:    extsw r3, r3
; CHECK-PWR9-NEXT:    bl callee
; CHECK-PWR9-NEXT:    nop
; CHECK-PWR9-NEXT:    lxv v21, 48(r1) # 16-byte Folded Reload
; CHECK-PWR9-NEXT:    lxv v20, 32(r1) # 16-byte Folded Reload
; CHECK-PWR9-NEXT:    lfd f14, 368(r1) # 8-byte Folded Reload
; CHECK-PWR9-NEXT:    ld r14, 224(r1) # 8-byte Folded Reload
; CHECK-PWR9-NEXT:    addi r1, r1, 512
; CHECK-PWR9-NEXT:    ld r0, 16(r1)
; CHECK-PWR9-NEXT:    mtlr r0
; CHECK-PWR9-NEXT:    blr
entry:
  %0 = tail call i32 asm "add $0, $1, $2", "=r,r,r,~{r14},~{f14},~{v20},~{vs53}"(i32 %a, i32 %b)
  %call = tail call signext i32 @callee(i32 signext %0)
  ret i32 %call
}


