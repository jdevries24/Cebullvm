// RUN: %clang_cc1 -Wno-objc-root-class -Wno-int-conversion -fblocks -o /dev/null -triple x86_64-- -emit-llvm %s
// REQUIRES: asserts
// Verify there is no assertion.

typedef unsigned long long uint64_t;
typedef enum AnEnum : uint64_t AnEnum;
enum AnEnum: uint64_t {
    AnEnumA
};

typedef void (^BlockType)(void);
@interface MyClass
@end
@implementation MyClass
- (void)_doStuff {
  struct {
    int identifier;
    AnEnum type;
    BlockType handler;
  } var = {
    "hello",
    AnEnumA,
    ((void *)0)
  };
}
@end
