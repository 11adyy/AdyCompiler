#define A 1
#define B A + 1
#define C B + 1
#define int i32
start() {
    int a = C + A - B;
}

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
#line 2 "{X}.apl"
#line 3 "{X}.apl"
#line 4 "{X}.apl"
start() {
    i32 a = 1 + 1 + 1 + 1 - 1 + 1;
}
/: