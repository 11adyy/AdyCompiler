{
    #include "string_h.apl"

    function strlen(ptr i8 s) -> i64 {
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
#line 0 "{X}.apl"
     
    function strlen(ptr i8 s) -> i64;

#line 2 "{X}.apl"

    function strlen(ptr i8 s) -> i64 {
        i64 l = 0;
        while dref s; {
            s += 1;
            l += 1;
        }

        return l;
    }
}
: