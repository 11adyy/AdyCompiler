{
    #include "print_h.apl"

    function print(ptr str msg) -> i0 {
        syscall(0x2000004, 1, msg, strlen(msg));
    }
}

: OUTPUT
{
#line 0 "{X}.apl"
#line 0 "{X}.apl"
     
    function strlen(ptr i8 s) -> i64;
 
#line 4 "{X}.apl"
   
    function print(ptr str msg) -> i0;

#line 2 "{X}.apl"

    function print(ptr str msg) -> i0 {
        syscall(0x2000004, 1, msg, strlen(msg));
    }
}
: