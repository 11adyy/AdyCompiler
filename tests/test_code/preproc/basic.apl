{
    #include "print_h.apl"

    start(i64 argc, ptr u64 argv) {
        print("Hello world!\n");
        exit 0;
    }
}

: OUTPUT
{
#line 0 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/print_h.apl"
#line 0 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/string_h.apl"
 
    function strlen(ptr i8 s) => i64;
 
#line 4 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/print_h.apl"
    
    function print(ptr str msg) => i0;
 
#line 2 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/basic.apl"

    start(i64 argc, ptr u64 argv) {
        print("Hello world!\n");
        exit 0;
    }
}
: