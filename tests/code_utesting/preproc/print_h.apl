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
function strlen(ptr i8 s) -> i64;
#line 3 "{X}.apl"
function print(ptr i8 msg) -> i0;
/:
