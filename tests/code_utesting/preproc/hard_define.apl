#define int  i32
#define pint ptr i32
#define BASE int a = 1, pint b = 2
#define FUNC (BASE) -> int
function foo FUNC;

function fang(pint a, pint b) {
    return dref a;
}

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
#line 2 "{X}.apl"
#line 3 "{X}.apl"
#line 4 "{X}.apl"
function foo (i32 a = 1, ptr i32 b = 2) -> i32;
function fang(ptr i32 a, ptr i32 b) {
    return dref a;
}
/: