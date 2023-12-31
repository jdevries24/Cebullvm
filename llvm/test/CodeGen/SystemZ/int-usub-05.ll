; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py UTC_ARGS: --version 3
; Test 64-bit subtraction in which the second operand is constant.
;
; RUN: llc < %s -mtriple=s390x-linux-gnu | FileCheck %s

declare i64 @foo()

; Check addition of 1.
define zeroext i1 @f1(i64 %dummy, i64 %a, ptr %res) {
; CHECK-LABEL: f1:
; CHECK:       # %bb.0:
; CHECK-NEXT:    slgfi %r3, 1
; CHECK-NEXT:    ipm %r0
; CHECK-NEXT:    afi %r0, -536870912
; CHECK-NEXT:    risbg %r2, %r0, 63, 191, 33
; CHECK-NEXT:    stg %r3, 0(%r4)
; CHECK-NEXT:    br %r14
  %t = call {i64, i1} @llvm.usub.with.overflow.i64(i64 %a, i64 1)
  %val = extractvalue {i64, i1} %t, 0
  %obit = extractvalue {i64, i1} %t, 1
  store i64 %val, ptr %res
  ret i1 %obit
}

; Check the high end of the SLGFI range.
define zeroext i1 @f2(i64 %dummy, i64 %a, ptr %res) {
; CHECK-LABEL: f2:
; CHECK:       # %bb.0:
; CHECK-NEXT:    slgfi %r3, 4294967295
; CHECK-NEXT:    ipm %r0
; CHECK-NEXT:    afi %r0, -536870912
; CHECK-NEXT:    risbg %r2, %r0, 63, 191, 33
; CHECK-NEXT:    stg %r3, 0(%r4)
; CHECK-NEXT:    br %r14
  %t = call {i64, i1} @llvm.usub.with.overflow.i64(i64 %a, i64 4294967295)
  %val = extractvalue {i64, i1} %t, 0
  %obit = extractvalue {i64, i1} %t, 1
  store i64 %val, ptr %res
  ret i1 %obit
}

; Check the next value up, which must be loaded into a register first.
define zeroext i1 @f3(i64 %dummy, i64 %a, ptr %res) {
; CHECK-LABEL: f3:
; CHECK:       # %bb.0:
; CHECK-NEXT:    llihl %r0, 1
; CHECK-NEXT:    slgr %r3, %r0
; CHECK-NEXT:    ipm %r0
; CHECK-NEXT:    afi %r0, -536870912
; CHECK-NEXT:    risbg %r2, %r0, 63, 191, 33
; CHECK-NEXT:    stg %r3, 0(%r4)
; CHECK-NEXT:    br %r14
  %t = call {i64, i1} @llvm.usub.with.overflow.i64(i64 %a, i64 4294967296)
  %val = extractvalue {i64, i1} %t, 0
  %obit = extractvalue {i64, i1} %t, 1
  store i64 %val, ptr %res
  ret i1 %obit
}

; Likewise for negative values.
define zeroext i1 @f4(i64 %dummy, i64 %a, ptr %res) {
; CHECK-LABEL: f4:
; CHECK:       # %bb.0:
; CHECK-NEXT:    lghi %r0, -1
; CHECK-NEXT:    slgr %r3, %r0
; CHECK-NEXT:    ipm %r0
; CHECK-NEXT:    afi %r0, -536870912
; CHECK-NEXT:    risbg %r2, %r0, 63, 191, 33
; CHECK-NEXT:    stg %r3, 0(%r4)
; CHECK-NEXT:    br %r14
  %t = call {i64, i1} @llvm.usub.with.overflow.i64(i64 %a, i64 -1)
  %val = extractvalue {i64, i1} %t, 0
  %obit = extractvalue {i64, i1} %t, 1
  store i64 %val, ptr %res
  ret i1 %obit
}

; Check using the overflow result for a branch.
define void @f5(i64 %dummy, i64 %a, ptr %res) {
; CHECK-LABEL: f5:
; CHECK:       # %bb.0:
; CHECK-NEXT:    slgfi %r3, 1
; CHECK-NEXT:    stg %r3, 0(%r4)
; CHECK-NEXT:    jgle foo@PLT
; CHECK-NEXT:  .LBB4_1: # %exit
; CHECK-NEXT:    br %r14
  %t = call {i64, i1} @llvm.usub.with.overflow.i64(i64 %a, i64 1)
  %val = extractvalue {i64, i1} %t, 0
  %obit = extractvalue {i64, i1} %t, 1
  store i64 %val, ptr %res
  br i1 %obit, label %call, label %exit

call:
  tail call i64 @foo()
  br label %exit

exit:
  ret void
}

; ... and the same with the inverted direction.
define void @f6(i64 %dummy, i64 %a, ptr %res) {
; CHECK-LABEL: f6:
; CHECK:       # %bb.0:
; CHECK-NEXT:    slgfi %r3, 1
; CHECK-NEXT:    stg %r3, 0(%r4)
; CHECK-NEXT:    jgnle foo@PLT
; CHECK-NEXT:  .LBB5_1: # %exit
; CHECK-NEXT:    br %r14
  %t = call {i64, i1} @llvm.usub.with.overflow.i64(i64 %a, i64 1)
  %val = extractvalue {i64, i1} %t, 0
  %obit = extractvalue {i64, i1} %t, 1
  store i64 %val, ptr %res
  br i1 %obit, label %exit, label %call

call:
  tail call i64 @foo()
  br label %exit

exit:
  ret void
}

declare {i64, i1} @llvm.usub.with.overflow.i64(i64, i64) nounwind readnone

