#define A 1
#ifdef A
function a();
#define B 1
#ifdef B
function b();
#undef B
#endif
#ifdef B
function c();
#endif
function d();
#undef A
#endif

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
#line 2 "{X}.apl"
function a();
#line 4 "{X}.apl"
#line 5 "{X}.apl"
function b();
#line 7 "{X}.apl"
#line 8 "{X}.apl"
#line 9 "{X}.apl"
#line 11 "{X}.apl"
function d();
#line 13 "{X}.apl"
#line 14 "{X}.apl"
/: