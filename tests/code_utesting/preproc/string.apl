#include "string_h.apl"

function strlen(ptr i8 s) -> i64 {
    i64 l = 0;
    while dref s; {
        s += 1;
        l += 1;
    }

    return l;
}

:/ OUTPUT
#line 0 "{X}.apl"
#line 0 "code_utesting/preproc/string_h.apl"
#line 1 "code_utesting/preproc/string_h.apl"
#line 2 "code_utesting/preproc/string_h.apl"
function strlen(ptr i8 s) -> i64;
#line 9 "code_utesting/preproc/string_h.apl"
#line 1 "{X}.apl"
function strlen(ptr i8 s) -> i64 {
    i64 l = 0;
    while dref s; {
        s += 1;
        l += 1;
    }
    return l;
}
/: