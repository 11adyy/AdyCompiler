function foo() {
    ptr i32 a = 0;
    i32 b = dref a;
}

:/ OUTPUT
[WARNING] NULL-dereference error (variable 'a' is NULL)!
    at: {X}.apl:3:9
    trace: Variable 'a' is assigned with NULL here
      at: {X}.apl:2:14
/: