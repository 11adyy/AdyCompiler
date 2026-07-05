#ifndef PRINT_H_
#define PRINT_H_ 0
#include "string_h.apl"

: Basic print function that is based on
    a syscall invoke.
    Params
    - `msg` - Input message to print.
    
    Returns i0 aka nothing. :
function print(ptr i8 msg) -> i0;
#endif

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
#line 2 "{X}.apl"
#line 0 "code_utesting/preproc/string_h.apl"
#line 1 "code_utesting/preproc/string_h.apl"
#line 2 "code_utesting/preproc/string_h.apl"
function strlen(ptr i8 s) -> i64;
#line 9 "code_utesting/preproc/string_h.apl"
#line 3 "{X}.apl"
function print(ptr i8 msg) -> i0;
#line 12 "{X}.apl"
/: