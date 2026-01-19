{
    #include "print_h.apl"

    function print(ptr str msg) => i0 {
        syscall(0x2000004, 1, msg, strlen(msg));
    }
}

: OUTPUT
{
#line 0 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/print_h.apl"
#line 0 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/string_h.apl"
     
    function strlen(ptr i8 s) => i64;
 
#line 4 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/print_h.apl"
   
    function print(ptr str msg) => i0;

#line 2 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/print.apl"

    function print(ptr str msg) => i0 {
        syscall(0x2000004, 1, msg, strlen(msg));
    }
}
: