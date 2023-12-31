; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=aarch64 | FileCheck %s

define i64 @test(i64 %aa) {
; CHECK-LABEL: test:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    movi v0.8b, #137
; CHECK-NEXT:    fmov x0, d0
; CHECK-NEXT:    ret
entry:
  %a = bitcast i64 %aa to  <1 x i64>
  %k = icmp sgt <1 x i64> %a, zeroinitializer
  %l = zext <1 x i1> %k to <1 x i64>
  %o = and <1 x i64> %l, %a
  %p = xor <1 x i64> %l, <i64 -1>
  %q = and <1 x i64> %p, <i64 81985529216486895>
  %r = or <1 x i64> %q, %o
  %s = bitcast <1 x i64> %r to <8 x i8>
  %t = shufflevector <8 x i8> %s, <8 x i8> %s, <8 x i32> <i32 3, i32 3, i32 3, i32 3, i32 3, i32 3, i32 3, i32 3>
  %u = bitcast <8 x i8> %t to i64
  ret i64 %u
}
