// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --version 2
// REQUIRES: riscv-registered-target
// RUN: %clang_cc1 -triple riscv64 -target-feature +v -target-feature +zfh \
// RUN:   -target-feature +zvfh -disable-O0-optnone  \
// RUN:   -emit-llvm %s -o - | opt -S -passes=mem2reg | \
// RUN:   FileCheck --check-prefix=CHECK-RV64 %s

#include <riscv_vector.h>

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i16> @test_vfcvt_rtz_x_f_v_i16mf4
// CHECK-RV64-SAME: (<vscale x 1 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0:[0-9]+]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.nxv1i16.nxv1f16.i64(<vscale x 1 x i16> poison, <vscale x 1 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 1 x i16> [[TMP0]]
//
vint16mf4_t test_vfcvt_rtz_x_f_v_i16mf4(vfloat16mf4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16mf4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i16> @test_vfcvt_rtz_x_f_v_i16mf2
// CHECK-RV64-SAME: (<vscale x 2 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.nxv2i16.nxv2f16.i64(<vscale x 2 x i16> poison, <vscale x 2 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 2 x i16> [[TMP0]]
//
vint16mf2_t test_vfcvt_rtz_x_f_v_i16mf2(vfloat16mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16mf2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i16> @test_vfcvt_rtz_x_f_v_i16m1
// CHECK-RV64-SAME: (<vscale x 4 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.nxv4i16.nxv4f16.i64(<vscale x 4 x i16> poison, <vscale x 4 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 4 x i16> [[TMP0]]
//
vint16m1_t test_vfcvt_rtz_x_f_v_i16m1(vfloat16m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m1(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i16> @test_vfcvt_rtz_x_f_v_i16m2
// CHECK-RV64-SAME: (<vscale x 8 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.nxv8i16.nxv8f16.i64(<vscale x 8 x i16> poison, <vscale x 8 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 8 x i16> [[TMP0]]
//
vint16m2_t test_vfcvt_rtz_x_f_v_i16m2(vfloat16m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i16> @test_vfcvt_rtz_x_f_v_i16m4
// CHECK-RV64-SAME: (<vscale x 16 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.nxv16i16.nxv16f16.i64(<vscale x 16 x i16> poison, <vscale x 16 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 16 x i16> [[TMP0]]
//
vint16m4_t test_vfcvt_rtz_x_f_v_i16m4(vfloat16m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 32 x i16> @test_vfcvt_rtz_x_f_v_i16m8
// CHECK-RV64-SAME: (<vscale x 32 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 32 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.nxv32i16.nxv32f16.i64(<vscale x 32 x i16> poison, <vscale x 32 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 32 x i16> [[TMP0]]
//
vint16m8_t test_vfcvt_rtz_x_f_v_i16m8(vfloat16m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m8(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i16> @test_vfcvt_rtz_xu_f_v_u16mf4
// CHECK-RV64-SAME: (<vscale x 1 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv1i16.nxv1f16.i64(<vscale x 1 x i16> poison, <vscale x 1 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 1 x i16> [[TMP0]]
//
vuint16mf4_t test_vfcvt_rtz_xu_f_v_u16mf4(vfloat16mf4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16mf4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i16> @test_vfcvt_rtz_xu_f_v_u16mf2
// CHECK-RV64-SAME: (<vscale x 2 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv2i16.nxv2f16.i64(<vscale x 2 x i16> poison, <vscale x 2 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 2 x i16> [[TMP0]]
//
vuint16mf2_t test_vfcvt_rtz_xu_f_v_u16mf2(vfloat16mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16mf2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i16> @test_vfcvt_rtz_xu_f_v_u16m1
// CHECK-RV64-SAME: (<vscale x 4 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv4i16.nxv4f16.i64(<vscale x 4 x i16> poison, <vscale x 4 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 4 x i16> [[TMP0]]
//
vuint16m1_t test_vfcvt_rtz_xu_f_v_u16m1(vfloat16m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m1(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i16> @test_vfcvt_rtz_xu_f_v_u16m2
// CHECK-RV64-SAME: (<vscale x 8 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv8i16.nxv8f16.i64(<vscale x 8 x i16> poison, <vscale x 8 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 8 x i16> [[TMP0]]
//
vuint16m2_t test_vfcvt_rtz_xu_f_v_u16m2(vfloat16m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i16> @test_vfcvt_rtz_xu_f_v_u16m4
// CHECK-RV64-SAME: (<vscale x 16 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv16i16.nxv16f16.i64(<vscale x 16 x i16> poison, <vscale x 16 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 16 x i16> [[TMP0]]
//
vuint16m4_t test_vfcvt_rtz_xu_f_v_u16m4(vfloat16m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 32 x i16> @test_vfcvt_rtz_xu_f_v_u16m8
// CHECK-RV64-SAME: (<vscale x 32 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 32 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv32i16.nxv32f16.i64(<vscale x 32 x i16> poison, <vscale x 32 x half> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 32 x i16> [[TMP0]]
//
vuint16m8_t test_vfcvt_rtz_xu_f_v_u16m8(vfloat16m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m8(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i32> @test_vfcvt_rtz_x_f_v_i32mf2
// CHECK-RV64-SAME: (<vscale x 1 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.nxv1i32.nxv1f32.i64(<vscale x 1 x i32> poison, <vscale x 1 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 1 x i32> [[TMP0]]
//
vint32mf2_t test_vfcvt_rtz_x_f_v_i32mf2(vfloat32mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32mf2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i32> @test_vfcvt_rtz_x_f_v_i32m1
// CHECK-RV64-SAME: (<vscale x 2 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.nxv2i32.nxv2f32.i64(<vscale x 2 x i32> poison, <vscale x 2 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 2 x i32> [[TMP0]]
//
vint32m1_t test_vfcvt_rtz_x_f_v_i32m1(vfloat32m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m1(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i32> @test_vfcvt_rtz_x_f_v_i32m2
// CHECK-RV64-SAME: (<vscale x 4 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.nxv4i32.nxv4f32.i64(<vscale x 4 x i32> poison, <vscale x 4 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 4 x i32> [[TMP0]]
//
vint32m2_t test_vfcvt_rtz_x_f_v_i32m2(vfloat32m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i32> @test_vfcvt_rtz_x_f_v_i32m4
// CHECK-RV64-SAME: (<vscale x 8 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.nxv8i32.nxv8f32.i64(<vscale x 8 x i32> poison, <vscale x 8 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 8 x i32> [[TMP0]]
//
vint32m4_t test_vfcvt_rtz_x_f_v_i32m4(vfloat32m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i32> @test_vfcvt_rtz_x_f_v_i32m8
// CHECK-RV64-SAME: (<vscale x 16 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.nxv16i32.nxv16f32.i64(<vscale x 16 x i32> poison, <vscale x 16 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 16 x i32> [[TMP0]]
//
vint32m8_t test_vfcvt_rtz_x_f_v_i32m8(vfloat32m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m8(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i32> @test_vfcvt_rtz_xu_f_v_u32mf2
// CHECK-RV64-SAME: (<vscale x 1 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv1i32.nxv1f32.i64(<vscale x 1 x i32> poison, <vscale x 1 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 1 x i32> [[TMP0]]
//
vuint32mf2_t test_vfcvt_rtz_xu_f_v_u32mf2(vfloat32mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32mf2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i32> @test_vfcvt_rtz_xu_f_v_u32m1
// CHECK-RV64-SAME: (<vscale x 2 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv2i32.nxv2f32.i64(<vscale x 2 x i32> poison, <vscale x 2 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 2 x i32> [[TMP0]]
//
vuint32m1_t test_vfcvt_rtz_xu_f_v_u32m1(vfloat32m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m1(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i32> @test_vfcvt_rtz_xu_f_v_u32m2
// CHECK-RV64-SAME: (<vscale x 4 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv4i32.nxv4f32.i64(<vscale x 4 x i32> poison, <vscale x 4 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 4 x i32> [[TMP0]]
//
vuint32m2_t test_vfcvt_rtz_xu_f_v_u32m2(vfloat32m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i32> @test_vfcvt_rtz_xu_f_v_u32m4
// CHECK-RV64-SAME: (<vscale x 8 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv8i32.nxv8f32.i64(<vscale x 8 x i32> poison, <vscale x 8 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 8 x i32> [[TMP0]]
//
vuint32m4_t test_vfcvt_rtz_xu_f_v_u32m4(vfloat32m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i32> @test_vfcvt_rtz_xu_f_v_u32m8
// CHECK-RV64-SAME: (<vscale x 16 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv16i32.nxv16f32.i64(<vscale x 16 x i32> poison, <vscale x 16 x float> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 16 x i32> [[TMP0]]
//
vuint32m8_t test_vfcvt_rtz_xu_f_v_u32m8(vfloat32m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m8(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i64> @test_vfcvt_rtz_x_f_v_i64m1
// CHECK-RV64-SAME: (<vscale x 1 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.nxv1i64.nxv1f64.i64(<vscale x 1 x i64> poison, <vscale x 1 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 1 x i64> [[TMP0]]
//
vint64m1_t test_vfcvt_rtz_x_f_v_i64m1(vfloat64m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m1(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i64> @test_vfcvt_rtz_x_f_v_i64m2
// CHECK-RV64-SAME: (<vscale x 2 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.nxv2i64.nxv2f64.i64(<vscale x 2 x i64> poison, <vscale x 2 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 2 x i64> [[TMP0]]
//
vint64m2_t test_vfcvt_rtz_x_f_v_i64m2(vfloat64m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i64> @test_vfcvt_rtz_x_f_v_i64m4
// CHECK-RV64-SAME: (<vscale x 4 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.nxv4i64.nxv4f64.i64(<vscale x 4 x i64> poison, <vscale x 4 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 4 x i64> [[TMP0]]
//
vint64m4_t test_vfcvt_rtz_x_f_v_i64m4(vfloat64m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i64> @test_vfcvt_rtz_x_f_v_i64m8
// CHECK-RV64-SAME: (<vscale x 8 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.nxv8i64.nxv8f64.i64(<vscale x 8 x i64> poison, <vscale x 8 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 8 x i64> [[TMP0]]
//
vint64m8_t test_vfcvt_rtz_x_f_v_i64m8(vfloat64m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m8(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i64> @test_vfcvt_rtz_xu_f_v_u64m1
// CHECK-RV64-SAME: (<vscale x 1 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv1i64.nxv1f64.i64(<vscale x 1 x i64> poison, <vscale x 1 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 1 x i64> [[TMP0]]
//
vuint64m1_t test_vfcvt_rtz_xu_f_v_u64m1(vfloat64m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m1(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i64> @test_vfcvt_rtz_xu_f_v_u64m2
// CHECK-RV64-SAME: (<vscale x 2 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv2i64.nxv2f64.i64(<vscale x 2 x i64> poison, <vscale x 2 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 2 x i64> [[TMP0]]
//
vuint64m2_t test_vfcvt_rtz_xu_f_v_u64m2(vfloat64m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m2(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i64> @test_vfcvt_rtz_xu_f_v_u64m4
// CHECK-RV64-SAME: (<vscale x 4 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv4i64.nxv4f64.i64(<vscale x 4 x i64> poison, <vscale x 4 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 4 x i64> [[TMP0]]
//
vuint64m4_t test_vfcvt_rtz_xu_f_v_u64m4(vfloat64m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m4(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i64> @test_vfcvt_rtz_xu_f_v_u64m8
// CHECK-RV64-SAME: (<vscale x 8 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.nxv8i64.nxv8f64.i64(<vscale x 8 x i64> poison, <vscale x 8 x double> [[SRC]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret <vscale x 8 x i64> [[TMP0]]
//
vuint64m8_t test_vfcvt_rtz_xu_f_v_u64m8(vfloat64m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m8(src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i16> @test_vfcvt_rtz_x_f_v_i16mf4_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], <vscale x 1 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv1i16.nxv1f16.i64(<vscale x 1 x i16> poison, <vscale x 1 x half> [[SRC]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 1 x i16> [[TMP0]]
//
vint16mf4_t test_vfcvt_rtz_x_f_v_i16mf4_m(vbool64_t mask, vfloat16mf4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16mf4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i16> @test_vfcvt_rtz_x_f_v_i16mf2_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], <vscale x 2 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv2i16.nxv2f16.i64(<vscale x 2 x i16> poison, <vscale x 2 x half> [[SRC]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 2 x i16> [[TMP0]]
//
vint16mf2_t test_vfcvt_rtz_x_f_v_i16mf2_m(vbool32_t mask, vfloat16mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16mf2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i16> @test_vfcvt_rtz_x_f_v_i16m1_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], <vscale x 4 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv4i16.nxv4f16.i64(<vscale x 4 x i16> poison, <vscale x 4 x half> [[SRC]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 4 x i16> [[TMP0]]
//
vint16m1_t test_vfcvt_rtz_x_f_v_i16m1_m(vbool16_t mask, vfloat16m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m1_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i16> @test_vfcvt_rtz_x_f_v_i16m2_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], <vscale x 8 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv8i16.nxv8f16.i64(<vscale x 8 x i16> poison, <vscale x 8 x half> [[SRC]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 8 x i16> [[TMP0]]
//
vint16m2_t test_vfcvt_rtz_x_f_v_i16m2_m(vbool8_t mask, vfloat16m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i16> @test_vfcvt_rtz_x_f_v_i16m4_m
// CHECK-RV64-SAME: (<vscale x 16 x i1> [[MASK:%.*]], <vscale x 16 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv16i16.nxv16f16.i64(<vscale x 16 x i16> poison, <vscale x 16 x half> [[SRC]], <vscale x 16 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 16 x i16> [[TMP0]]
//
vint16m4_t test_vfcvt_rtz_x_f_v_i16m4_m(vbool4_t mask, vfloat16m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 32 x i16> @test_vfcvt_rtz_x_f_v_i16m8_m
// CHECK-RV64-SAME: (<vscale x 32 x i1> [[MASK:%.*]], <vscale x 32 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 32 x i16> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv32i16.nxv32f16.i64(<vscale x 32 x i16> poison, <vscale x 32 x half> [[SRC]], <vscale x 32 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 32 x i16> [[TMP0]]
//
vint16m8_t test_vfcvt_rtz_x_f_v_i16m8_m(vbool2_t mask, vfloat16m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i16m8_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i16> @test_vfcvt_rtz_xu_f_v_u16mf4_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], <vscale x 1 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv1i16.nxv1f16.i64(<vscale x 1 x i16> poison, <vscale x 1 x half> [[SRC]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 1 x i16> [[TMP0]]
//
vuint16mf4_t test_vfcvt_rtz_xu_f_v_u16mf4_m(vbool64_t mask, vfloat16mf4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16mf4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i16> @test_vfcvt_rtz_xu_f_v_u16mf2_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], <vscale x 2 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv2i16.nxv2f16.i64(<vscale x 2 x i16> poison, <vscale x 2 x half> [[SRC]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 2 x i16> [[TMP0]]
//
vuint16mf2_t test_vfcvt_rtz_xu_f_v_u16mf2_m(vbool32_t mask, vfloat16mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16mf2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i16> @test_vfcvt_rtz_xu_f_v_u16m1_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], <vscale x 4 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv4i16.nxv4f16.i64(<vscale x 4 x i16> poison, <vscale x 4 x half> [[SRC]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 4 x i16> [[TMP0]]
//
vuint16m1_t test_vfcvt_rtz_xu_f_v_u16m1_m(vbool16_t mask, vfloat16m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m1_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i16> @test_vfcvt_rtz_xu_f_v_u16m2_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], <vscale x 8 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv8i16.nxv8f16.i64(<vscale x 8 x i16> poison, <vscale x 8 x half> [[SRC]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 8 x i16> [[TMP0]]
//
vuint16m2_t test_vfcvt_rtz_xu_f_v_u16m2_m(vbool8_t mask, vfloat16m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i16> @test_vfcvt_rtz_xu_f_v_u16m4_m
// CHECK-RV64-SAME: (<vscale x 16 x i1> [[MASK:%.*]], <vscale x 16 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv16i16.nxv16f16.i64(<vscale x 16 x i16> poison, <vscale x 16 x half> [[SRC]], <vscale x 16 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 16 x i16> [[TMP0]]
//
vuint16m4_t test_vfcvt_rtz_xu_f_v_u16m4_m(vbool4_t mask, vfloat16m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 32 x i16> @test_vfcvt_rtz_xu_f_v_u16m8_m
// CHECK-RV64-SAME: (<vscale x 32 x i1> [[MASK:%.*]], <vscale x 32 x half> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 32 x i16> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv32i16.nxv32f16.i64(<vscale x 32 x i16> poison, <vscale x 32 x half> [[SRC]], <vscale x 32 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 32 x i16> [[TMP0]]
//
vuint16m8_t test_vfcvt_rtz_xu_f_v_u16m8_m(vbool2_t mask, vfloat16m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u16m8_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i32> @test_vfcvt_rtz_x_f_v_i32mf2_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], <vscale x 1 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv1i32.nxv1f32.i64(<vscale x 1 x i32> poison, <vscale x 1 x float> [[SRC]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 1 x i32> [[TMP0]]
//
vint32mf2_t test_vfcvt_rtz_x_f_v_i32mf2_m(vbool64_t mask, vfloat32mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32mf2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i32> @test_vfcvt_rtz_x_f_v_i32m1_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], <vscale x 2 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv2i32.nxv2f32.i64(<vscale x 2 x i32> poison, <vscale x 2 x float> [[SRC]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 2 x i32> [[TMP0]]
//
vint32m1_t test_vfcvt_rtz_x_f_v_i32m1_m(vbool32_t mask, vfloat32m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m1_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i32> @test_vfcvt_rtz_x_f_v_i32m2_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], <vscale x 4 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv4i32.nxv4f32.i64(<vscale x 4 x i32> poison, <vscale x 4 x float> [[SRC]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 4 x i32> [[TMP0]]
//
vint32m2_t test_vfcvt_rtz_x_f_v_i32m2_m(vbool16_t mask, vfloat32m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i32> @test_vfcvt_rtz_x_f_v_i32m4_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], <vscale x 8 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv8i32.nxv8f32.i64(<vscale x 8 x i32> poison, <vscale x 8 x float> [[SRC]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 8 x i32> [[TMP0]]
//
vint32m4_t test_vfcvt_rtz_x_f_v_i32m4_m(vbool8_t mask, vfloat32m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i32> @test_vfcvt_rtz_x_f_v_i32m8_m
// CHECK-RV64-SAME: (<vscale x 16 x i1> [[MASK:%.*]], <vscale x 16 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i32> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv16i32.nxv16f32.i64(<vscale x 16 x i32> poison, <vscale x 16 x float> [[SRC]], <vscale x 16 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 16 x i32> [[TMP0]]
//
vint32m8_t test_vfcvt_rtz_x_f_v_i32m8_m(vbool4_t mask, vfloat32m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i32m8_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i32> @test_vfcvt_rtz_xu_f_v_u32mf2_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], <vscale x 1 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv1i32.nxv1f32.i64(<vscale x 1 x i32> poison, <vscale x 1 x float> [[SRC]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 1 x i32> [[TMP0]]
//
vuint32mf2_t test_vfcvt_rtz_xu_f_v_u32mf2_m(vbool64_t mask, vfloat32mf2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32mf2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i32> @test_vfcvt_rtz_xu_f_v_u32m1_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], <vscale x 2 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv2i32.nxv2f32.i64(<vscale x 2 x i32> poison, <vscale x 2 x float> [[SRC]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 2 x i32> [[TMP0]]
//
vuint32m1_t test_vfcvt_rtz_xu_f_v_u32m1_m(vbool32_t mask, vfloat32m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m1_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i32> @test_vfcvt_rtz_xu_f_v_u32m2_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], <vscale x 4 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv4i32.nxv4f32.i64(<vscale x 4 x i32> poison, <vscale x 4 x float> [[SRC]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 4 x i32> [[TMP0]]
//
vuint32m2_t test_vfcvt_rtz_xu_f_v_u32m2_m(vbool16_t mask, vfloat32m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i32> @test_vfcvt_rtz_xu_f_v_u32m4_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], <vscale x 8 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv8i32.nxv8f32.i64(<vscale x 8 x i32> poison, <vscale x 8 x float> [[SRC]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 8 x i32> [[TMP0]]
//
vuint32m4_t test_vfcvt_rtz_xu_f_v_u32m4_m(vbool8_t mask, vfloat32m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 16 x i32> @test_vfcvt_rtz_xu_f_v_u32m8_m
// CHECK-RV64-SAME: (<vscale x 16 x i1> [[MASK:%.*]], <vscale x 16 x float> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i32> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv16i32.nxv16f32.i64(<vscale x 16 x i32> poison, <vscale x 16 x float> [[SRC]], <vscale x 16 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 16 x i32> [[TMP0]]
//
vuint32m8_t test_vfcvt_rtz_xu_f_v_u32m8_m(vbool4_t mask, vfloat32m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u32m8_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i64> @test_vfcvt_rtz_x_f_v_i64m1_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], <vscale x 1 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv1i64.nxv1f64.i64(<vscale x 1 x i64> poison, <vscale x 1 x double> [[SRC]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 1 x i64> [[TMP0]]
//
vint64m1_t test_vfcvt_rtz_x_f_v_i64m1_m(vbool64_t mask, vfloat64m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m1_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i64> @test_vfcvt_rtz_x_f_v_i64m2_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], <vscale x 2 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv2i64.nxv2f64.i64(<vscale x 2 x i64> poison, <vscale x 2 x double> [[SRC]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 2 x i64> [[TMP0]]
//
vint64m2_t test_vfcvt_rtz_x_f_v_i64m2_m(vbool32_t mask, vfloat64m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i64> @test_vfcvt_rtz_x_f_v_i64m4_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], <vscale x 4 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv4i64.nxv4f64.i64(<vscale x 4 x i64> poison, <vscale x 4 x double> [[SRC]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 4 x i64> [[TMP0]]
//
vint64m4_t test_vfcvt_rtz_x_f_v_i64m4_m(vbool16_t mask, vfloat64m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i64> @test_vfcvt_rtz_x_f_v_i64m8_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], <vscale x 8 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i64> @llvm.riscv.vfcvt.rtz.x.f.v.mask.nxv8i64.nxv8f64.i64(<vscale x 8 x i64> poison, <vscale x 8 x double> [[SRC]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 8 x i64> [[TMP0]]
//
vint64m8_t test_vfcvt_rtz_x_f_v_i64m8_m(vbool8_t mask, vfloat64m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_x_f_v_i64m8_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 1 x i64> @test_vfcvt_rtz_xu_f_v_u64m1_m
// CHECK-RV64-SAME: (<vscale x 1 x i1> [[MASK:%.*]], <vscale x 1 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 1 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv1i64.nxv1f64.i64(<vscale x 1 x i64> poison, <vscale x 1 x double> [[SRC]], <vscale x 1 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 1 x i64> [[TMP0]]
//
vuint64m1_t test_vfcvt_rtz_xu_f_v_u64m1_m(vbool64_t mask, vfloat64m1_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m1_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 2 x i64> @test_vfcvt_rtz_xu_f_v_u64m2_m
// CHECK-RV64-SAME: (<vscale x 2 x i1> [[MASK:%.*]], <vscale x 2 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 2 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv2i64.nxv2f64.i64(<vscale x 2 x i64> poison, <vscale x 2 x double> [[SRC]], <vscale x 2 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 2 x i64> [[TMP0]]
//
vuint64m2_t test_vfcvt_rtz_xu_f_v_u64m2_m(vbool32_t mask, vfloat64m2_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m2_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 4 x i64> @test_vfcvt_rtz_xu_f_v_u64m4_m
// CHECK-RV64-SAME: (<vscale x 4 x i1> [[MASK:%.*]], <vscale x 4 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv4i64.nxv4f64.i64(<vscale x 4 x i64> poison, <vscale x 4 x double> [[SRC]], <vscale x 4 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 4 x i64> [[TMP0]]
//
vuint64m4_t test_vfcvt_rtz_xu_f_v_u64m4_m(vbool16_t mask, vfloat64m4_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m4_m(mask, src, vl);
}

// CHECK-RV64-LABEL: define dso_local <vscale x 8 x i64> @test_vfcvt_rtz_xu_f_v_u64m8_m
// CHECK-RV64-SAME: (<vscale x 8 x i1> [[MASK:%.*]], <vscale x 8 x double> [[SRC:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i64> @llvm.riscv.vfcvt.rtz.xu.f.v.mask.nxv8i64.nxv8f64.i64(<vscale x 8 x i64> poison, <vscale x 8 x double> [[SRC]], <vscale x 8 x i1> [[MASK]], i64 [[VL]], i64 3)
// CHECK-RV64-NEXT:    ret <vscale x 8 x i64> [[TMP0]]
//
vuint64m8_t test_vfcvt_rtz_xu_f_v_u64m8_m(vbool8_t mask, vfloat64m8_t src, size_t vl) {
  return __riscv_vfcvt_rtz_xu_f_v_u64m8_m(mask, src, vl);
}

