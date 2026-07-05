#define ASD 1
function foo(i32 a = ASD);
#undef ASD
function bar(i32 a = ASD);
: #undef ASD
#undef ASD :
function baz(u32 a = ASD);
function main(u32 a = ASD);

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
function foo(i32 a = 1);
#line 3 "{X}.apl"
function bar(i32 a = ASD);
function baz(u32 a = ASD);
function main(u32 a = ASD);
/: