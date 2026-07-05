#define ASD i32
#define ASD1 ASD
#define ASD2 ASD1
#define ASD3 ASD2
#define ASD4 ASD3
#define ASD5 ASD4
#define ASD6 ASD5
#define ASD7 ASD6
function foo(ASD7 a);

:/ OUTPUT
#line 0 "{X}.apl"
#line 1 "{X}.apl"
#line 2 "{X}.apl"
#line 3 "{X}.apl"
#line 4 "{X}.apl"
#line 5 "{X}.apl"
#line 6 "{X}.apl"
#line 7 "{X}.apl"
#line 8 "{X}.apl"
function foo(i32 a);
/: