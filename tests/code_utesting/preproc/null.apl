#define NULL 0 as ptr u64
start() {
    ptr i8 a = NULL;
    exit 0;
}

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
start() {
    ptr i8 a = 0 as ptr u64;
    exit 0;
}
/: