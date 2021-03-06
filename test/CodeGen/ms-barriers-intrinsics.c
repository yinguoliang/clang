// RUN: %clang_cc1 -ffreestanding -fms-extensions -fms-compatibility -fms-compatibility-version=17.00 \
// RUN:         -triple i686--windows -emit-llvm %s -o - \
// RUN:         | FileCheck %s -check-prefix=CHECK -check-prefix=CHECK-I386
// RUN: %clang_cc1 -ffreestanding -fms-extensions -fms-compatibility -fms-compatibility-version=17.00 \
// RUN:         -triple x86_64--windows -emit-llvm %s -o - \
// RUN:         | FileCheck %s --check-prefix=CHECK --check-prefix=CHECK-X64

// intrin.h needs size_t, but -ffreestanding prevents us from getting it from
// stddef.h.  Work around it with this typedef.
typedef __SIZE_TYPE__ size_t;

#include <intrin.h>

void test_ReadWriteBarrier() { _ReadWriteBarrier(); }
// CHECK-LABEL: define void @test_ReadWriteBarrier
// CHECK:   fence singlethread seq_cst
// CHECK:   ret void
// CHECK: }

void test_ReadBarrier() { _ReadBarrier(); }
// CHECK-LABEL: define void @test_ReadBarrier
// CHECK:   fence singlethread seq_cst
// CHECK:   ret void
// CHECK: }

void test_WriteBarrier() { _WriteBarrier(); }
// CHECK-LABEL: define void @test_WriteBarrier
// CHECK:   fence singlethread seq_cst
// CHECK:   ret void
// CHECK: }

#if defined(__x86_64__)
void test__faststorefence() { __faststorefence(); }
// CHECK-X64-LABEL: define void @test__faststorefence
// CHECK-X64:   fence seq_cst
// CHECK-X64:   ret void
// CHECK-X64: }
#endif

