#define TEST 0
function foo(i32 a = TEST) {
}

#ifndef TEST2
#define TEST2 1
function foo2(i32 a = TEST2) {
}
#endif
#undef TEST2

#ifdef TEST2
function foo3(i32 a) {}
#endif

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
function foo(i32 a = 0) {
}
#line 5 "{X}.apl"
#line 6 "{X}.apl"
function foo2(i32 a = 1) {
}
#line 9 "{X}.apl"
#line 10 "{X}.apl"
#line 12 "{X}.apl"
#line 14 "{X}.apl"
/: