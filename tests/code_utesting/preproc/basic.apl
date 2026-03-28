#include "print_h.apl"

start(i64 argc, ptr u64 argv) {
    print("Hello world!\n");
    exit 0;
}

:/ OUTPUT
#line 0 "{X}.apl"
#line 0 "{X}.apl"
 
function strlen(ptr i8 s) -> i64;
 
#line 3 "{X}.apl"
    
function print(ptr str msg) -> i0;
 
#line 1 "{X}.apl"

start(i64 argc, ptr u64 argv) {
    print("Hello world!\n");
    exit 0;
}
/:
