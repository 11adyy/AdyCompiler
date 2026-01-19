{
#ifndef PRINT_H_
#define PRINT_H_ 0
    #include "string_h.apl"

    : Basic print function that is based on
      a syscall invoke.
      Params
      - `msg` - Input message to print.
      
      Returns i0 aka nothing. :
    function print(ptr str msg) => i0;
#endif
}

: OUTPUT
{
#line 0 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/string_h.apl"
  
    function strlen(ptr i8 s) => i64;

#line 4 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/print_h.apl"
    
    function print(ptr str msg) => i0;
}
: