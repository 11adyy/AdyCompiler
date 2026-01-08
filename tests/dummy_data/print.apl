{
    #include "print_h.apl"

    function print(ptr str msg) => i0 {
        syscall(0x2000004, 1, msg, strlen(msg));
    }
}