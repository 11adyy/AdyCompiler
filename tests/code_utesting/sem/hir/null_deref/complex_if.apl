@[entry]
function foo() {
    i32 a = 1;
    if 1; {
        a = 0;
    }
    ptr i32 b = a as ptr i32;
    exit dref b;
}

:/ OUTPUT
[WARNING] 'If' with a constant value 'true'!
    at: {X}.apl:4:8
[WARNING] Possible NULL-dereference error (variable 'b' is NULL)!
    at: {X}.apl:8:10
    trace: Variable 'b' is assigned with 'a' here
      at: {X}.apl:7:14
    trace: Variable 'a' becomes NULL
      at: {X}.apl:5:14
/: