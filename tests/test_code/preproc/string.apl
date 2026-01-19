{
    #include "string_h.apl"

    function strlen(ptr i8 s) => i64 {
        i64 l = 0;
        while dref s; {
            s += 1;
            l += 1;
        }

        return l;
    }
}

: OUTPUT
{
#line 0 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/string_h.apl"
     
    function strlen(ptr i8 s) => i64;

#line 2 "/Users/Noah/Documents/Repositories/AdyCompiler/tests/test_code/preproc/string.apl"

    function strlen(ptr i8 s) => i64 {
        i64 l = 0;
        while dref s; {
            s += 1;
            l += 1;
        }

        return l;
    }
}
: