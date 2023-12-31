// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --version 2
// REQUIRES: riscv-registered-target
// RUN: %clang_cc1 -triple riscv64 -target-feature +v -disable-O0-optnone \
// RUN:   -emit-llvm %s -o - | opt -S -passes=mem2reg | \
// RUN:   FileCheck --check-prefix=CHECK-RV64 %s

#include <riscv_vector.h>

// CHECK-RV64-LABEL: define dso_local { <vscale x 1 x i8>, <vscale x 1 x i8> } @test_vlseg2e8_v_i8mf8x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0:[0-9]+]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 1 x i8>, <vscale x 1 x i8> } @llvm.riscv.vlseg2.nxv1i8.i64(<vscale x 1 x i8> poison, <vscale x 1 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 1 x i8>, <vscale x 1 x i8> } [[TMP0]]
//
vint8mf8x2_t test_vlseg2e8_v_i8mf8x2(const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8mf8x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 2 x i8>, <vscale x 2 x i8> } @test_vlseg2e8_v_i8mf4x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 2 x i8>, <vscale x 2 x i8> } @llvm.riscv.vlseg2.nxv2i8.i64(<vscale x 2 x i8> poison, <vscale x 2 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 2 x i8>, <vscale x 2 x i8> } [[TMP0]]
//
vint8mf4x2_t test_vlseg2e8_v_i8mf4x2(const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8mf4x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 4 x i8>, <vscale x 4 x i8> } @test_vlseg2e8_v_i8mf2x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 4 x i8>, <vscale x 4 x i8> } @llvm.riscv.vlseg2.nxv4i8.i64(<vscale x 4 x i8> poison, <vscale x 4 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 4 x i8>, <vscale x 4 x i8> } [[TMP0]]
//
vint8mf2x2_t test_vlseg2e8_v_i8mf2x2(const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8mf2x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 8 x i8>, <vscale x 8 x i8> } @test_vlseg2e8_v_i8m1x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 8 x i8>, <vscale x 8 x i8> } @llvm.riscv.vlseg2.nxv8i8.i64(<vscale x 8 x i8> poison, <vscale x 8 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 8 x i8>, <vscale x 8 x i8> } [[TMP0]]
//
vint8m1x2_t test_vlseg2e8_v_i8m1x2(const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8m1x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 16 x i8>, <vscale x 16 x i8> } @test_vlseg2e8_v_i8m2x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 16 x i8>, <vscale x 16 x i8> } @llvm.riscv.vlseg2.nxv16i8.i64(<vscale x 16 x i8> poison, <vscale x 16 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 16 x i8>, <vscale x 16 x i8> } [[TMP0]]
//
vint8m2x2_t test_vlseg2e8_v_i8m2x2(const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8m2x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 32 x i8>, <vscale x 32 x i8> } @test_vlseg2e8_v_i8m4x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 32 x i8>, <vscale x 32 x i8> } @llvm.riscv.vlseg2.nxv32i8.i64(<vscale x 32 x i8> poison, <vscale x 32 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 32 x i8>, <vscale x 32 x i8> } [[TMP0]]
//
vint8m4x2_t test_vlseg2e8_v_i8m4x2(const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8m4x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 1 x i8>, <vscale x 1 x i8> } @test_vlseg2e8_v_u8mf8x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 1 x i8>, <vscale x 1 x i8> } @llvm.riscv.vlseg2.nxv1i8.i64(<vscale x 1 x i8> poison, <vscale x 1 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 1 x i8>, <vscale x 1 x i8> } [[TMP0]]
//
vuint8mf8x2_t test_vlseg2e8_v_u8mf8x2(const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8mf8x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 2 x i8>, <vscale x 2 x i8> } @test_vlseg2e8_v_u8mf4x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 2 x i8>, <vscale x 2 x i8> } @llvm.riscv.vlseg2.nxv2i8.i64(<vscale x 2 x i8> poison, <vscale x 2 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 2 x i8>, <vscale x 2 x i8> } [[TMP0]]
//
vuint8mf4x2_t test_vlseg2e8_v_u8mf4x2(const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8mf4x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 4 x i8>, <vscale x 4 x i8> } @test_vlseg2e8_v_u8mf2x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 4 x i8>, <vscale x 4 x i8> } @llvm.riscv.vlseg2.nxv4i8.i64(<vscale x 4 x i8> poison, <vscale x 4 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 4 x i8>, <vscale x 4 x i8> } [[TMP0]]
//
vuint8mf2x2_t test_vlseg2e8_v_u8mf2x2(const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8mf2x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 8 x i8>, <vscale x 8 x i8> } @test_vlseg2e8_v_u8m1x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 8 x i8>, <vscale x 8 x i8> } @llvm.riscv.vlseg2.nxv8i8.i64(<vscale x 8 x i8> poison, <vscale x 8 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 8 x i8>, <vscale x 8 x i8> } [[TMP0]]
//
vuint8m1x2_t test_vlseg2e8_v_u8m1x2(const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8m1x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 16 x i8>, <vscale x 16 x i8> } @test_vlseg2e8_v_u8m2x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 16 x i8>, <vscale x 16 x i8> } @llvm.riscv.vlseg2.nxv16i8.i64(<vscale x 16 x i8> poison, <vscale x 16 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 16 x i8>, <vscale x 16 x i8> } [[TMP0]]
//
vuint8m2x2_t test_vlseg2e8_v_u8m2x2(const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8m2x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 32 x i8>, <vscale x 32 x i8> } @test_vlseg2e8_v_u8m4x2
// CHECK-RV64-SAME: (ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 32 x i8>, <vscale x 32 x i8> } @llvm.riscv.vlseg2.nxv32i8.i64(<vscale x 32 x i8> poison, <vscale x 32 x i8> poison, ptr [[BASE]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret { <vscale x 32 x i8>, <vscale x 32 x i8> } [[TMP0]]
//
vuint8m4x2_t test_vlseg2e8_v_u8m4x2(const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8m4x2(base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 1 x i8>, <vscale x 1 x i8> } @test_vlseg2e8_v_i8mf8x2_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 1 x i8>, <vscale x 1 x i8> } @llvm.riscv.vlseg2.mask.nxv1i8.i64(<vscale x 1 x i8> poison, <vscale x 1 x i8> poison, ptr [[BASE]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 1 x i8>, <vscale x 1 x i8> } [[TMP0]]
//
vint8mf8x2_t test_vlseg2e8_v_i8mf8x2_m(vbool64_t mask, const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8mf8x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 2 x i8>, <vscale x 2 x i8> } @test_vlseg2e8_v_i8mf4x2_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 2 x i8>, <vscale x 2 x i8> } @llvm.riscv.vlseg2.mask.nxv2i8.i64(<vscale x 2 x i8> poison, <vscale x 2 x i8> poison, ptr [[BASE]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 2 x i8>, <vscale x 2 x i8> } [[TMP0]]
//
vint8mf4x2_t test_vlseg2e8_v_i8mf4x2_m(vbool32_t mask, const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8mf4x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 4 x i8>, <vscale x 4 x i8> } @test_vlseg2e8_v_i8mf2x2_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 4 x i8>, <vscale x 4 x i8> } @llvm.riscv.vlseg2.mask.nxv4i8.i64(<vscale x 4 x i8> poison, <vscale x 4 x i8> poison, ptr [[BASE]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 4 x i8>, <vscale x 4 x i8> } [[TMP0]]
//
vint8mf2x2_t test_vlseg2e8_v_i8mf2x2_m(vbool16_t mask, const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8mf2x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 8 x i8>, <vscale x 8 x i8> } @test_vlseg2e8_v_i8m1x2_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 8 x i8>, <vscale x 8 x i8> } @llvm.riscv.vlseg2.mask.nxv8i8.i64(<vscale x 8 x i8> poison, <vscale x 8 x i8> poison, ptr [[BASE]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 8 x i8>, <vscale x 8 x i8> } [[TMP0]]
//
vint8m1x2_t test_vlseg2e8_v_i8m1x2_m(vbool8_t mask, const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8m1x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 16 x i8>, <vscale x 16 x i8> } @test_vlseg2e8_v_i8m2x2_m
// CHECK-RV64-SAME: (<vscale x 16 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 16 x i8>, <vscale x 16 x i8> } @llvm.riscv.vlseg2.mask.nxv16i8.i64(<vscale x 16 x i8> poison, <vscale x 16 x i8> poison, ptr [[BASE]], <vscale x 16 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 16 x i8>, <vscale x 16 x i8> } [[TMP0]]
//
vint8m2x2_t test_vlseg2e8_v_i8m2x2_m(vbool4_t mask, const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8m2x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 32 x i8>, <vscale x 32 x i8> } @test_vlseg2e8_v_i8m4x2_m
// CHECK-RV64-SAME: (<vscale x 32 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 32 x i8>, <vscale x 32 x i8> } @llvm.riscv.vlseg2.mask.nxv32i8.i64(<vscale x 32 x i8> poison, <vscale x 32 x i8> poison, ptr [[BASE]], <vscale x 32 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 32 x i8>, <vscale x 32 x i8> } [[TMP0]]
//
vint8m4x2_t test_vlseg2e8_v_i8m4x2_m(vbool2_t mask, const int8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_i8m4x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 1 x i8>, <vscale x 1 x i8> } @test_vlseg2e8_v_u8mf8x2_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 1 x i8>, <vscale x 1 x i8> } @llvm.riscv.vlseg2.mask.nxv1i8.i64(<vscale x 1 x i8> poison, <vscale x 1 x i8> poison, ptr [[BASE]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 1 x i8>, <vscale x 1 x i8> } [[TMP0]]
//
vuint8mf8x2_t test_vlseg2e8_v_u8mf8x2_m(vbool64_t mask, const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8mf8x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 2 x i8>, <vscale x 2 x i8> } @test_vlseg2e8_v_u8mf4x2_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 2 x i8>, <vscale x 2 x i8> } @llvm.riscv.vlseg2.mask.nxv2i8.i64(<vscale x 2 x i8> poison, <vscale x 2 x i8> poison, ptr [[BASE]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 2 x i8>, <vscale x 2 x i8> } [[TMP0]]
//
vuint8mf4x2_t test_vlseg2e8_v_u8mf4x2_m(vbool32_t mask, const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8mf4x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 4 x i8>, <vscale x 4 x i8> } @test_vlseg2e8_v_u8mf2x2_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 4 x i8>, <vscale x 4 x i8> } @llvm.riscv.vlseg2.mask.nxv4i8.i64(<vscale x 4 x i8> poison, <vscale x 4 x i8> poison, ptr [[BASE]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 4 x i8>, <vscale x 4 x i8> } [[TMP0]]
//
vuint8mf2x2_t test_vlseg2e8_v_u8mf2x2_m(vbool16_t mask, const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8mf2x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 8 x i8>, <vscale x 8 x i8> } @test_vlseg2e8_v_u8m1x2_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 8 x i8>, <vscale x 8 x i8> } @llvm.riscv.vlseg2.mask.nxv8i8.i64(<vscale x 8 x i8> poison, <vscale x 8 x i8> poison, ptr [[BASE]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 8 x i8>, <vscale x 8 x i8> } [[TMP0]]
//
vuint8m1x2_t test_vlseg2e8_v_u8m1x2_m(vbool8_t mask, const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8m1x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 16 x i8>, <vscale x 16 x i8> } @test_vlseg2e8_v_u8m2x2_m
// CHECK-RV64-SAME: (<vscale x 16 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 16 x i8>, <vscale x 16 x i8> } @llvm.riscv.vlseg2.mask.nxv16i8.i64(<vscale x 16 x i8> poison, <vscale x 16 x i8> poison, ptr [[BASE]], <vscale x 16 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 16 x i8>, <vscale x 16 x i8> } [[TMP0]]
//
vuint8m2x2_t test_vlseg2e8_v_u8m2x2_m(vbool4_t mask, const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8m2x2_m(mask, base, vl);
}

// CHECK-RV64-LABEL: define dso_local { <vscale x 32 x i8>, <vscale x 32 x i8> } @test_vlseg2e8_v_u8m4x2_m
// CHECK-RV64-SAME: (<vscale x 32 x i1> [[MASK:%.*]], ptr noundef [[BASE:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call { <vscale x 32 x i8>, <vscale x 32 x i8> } @llvm.riscv.vlseg2.mask.nxv32i8.i64(<vscale x 32 x i8> poison, <vscale x 32 x i8> poison, ptr [[BASE]], <vscale x 32 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret { <vscale x 32 x i8>, <vscale x 32 x i8> } [[TMP0]]
//
vuint8m4x2_t test_vlseg2e8_v_u8m4x2_m(vbool2_t mask, const uint8_t *base, size_t vl) {
  return __riscv_vlseg2e8_v_u8m4x2_m(mask, base, vl);
}

