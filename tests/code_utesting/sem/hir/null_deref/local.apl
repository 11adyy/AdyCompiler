start() {
    function foo(ptr i32 p) -> i32 {
        return dref p;
    }
    ptr i32 a = 0;
    foo(a);
}

:/ OUTPUT
[WARNING] Function 'foo' has the 'i32' return type but the call doesn't store it anywhere else.
    at: {X}.apl:6:13
[WARNING] NULL-dereference error (variable 'p' is NULL)!
    at: {X}.apl:3:16
    trace: Variable 'p' is assigned with NULL here
      at: {X}.apl:2:14
/: