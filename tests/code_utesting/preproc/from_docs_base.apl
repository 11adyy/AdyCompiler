#include "print_h.apl"

start(i64 argc, ptr u64 argv) {
    arr msg[0, i8] = "Hello world!";
    print(ref msg);
    exit 0;
}

:/ OUTPUT
#line 0 "{X}.apl"
#line 0 "code_utesting/preproc/print_h.apl"
#line 1 "code_utesting/preproc/print_h.apl"
#line 2 "code_utesting/preproc/print_h.apl"
#line 0 "code_utesting/preproc/string_h.apl"
#line 1 "code_utesting/preproc/string_h.apl"
#line 2 "code_utesting/preproc/string_h.apl"
function strlen(ptr i8 s) -> i64;
#line 9 "code_utesting/preproc/string_h.apl"
#line 3 "code_utesting/preproc/print_h.apl"
function print(ptr i8 msg) -> i0;
#line 12 "code_utesting/preproc/print_h.apl"
#line 1 "{X}.apl"
start(i64 argc, ptr u64 argv) {
    arr msg[0, i8] = "Hello world!";
    print(ref msg);
    exit 0;
}
/: