#include "print_h.apl"
#include "string_h.apl"

function foo() -> i0;

function bar() -> i0 {
    foo();
}

function foo() -> i0 {
    print("Hello world!\n");
}

start(i64 argc, ptr u64 argv) {
    bar();
    exit 0;
}
