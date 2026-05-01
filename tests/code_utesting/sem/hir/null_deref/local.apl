start() {
    function foo(ptr i32 p) -> i32 {
        return dref p;
    }
    ptr i32 a = 0;
    foo(a);
}

:/ OUTPUT
[WARNING] [{X}apl:6:9] Function 'foo' has the 'i32' return type but the call doesn't store it anywhere else.
[WARNING] [{X}apl:3:16] NULL-dereference error (variable 'p' is NULL)!
          [{X}apl:2:14]     Variable 'p' is assigned with NULL here
/:
