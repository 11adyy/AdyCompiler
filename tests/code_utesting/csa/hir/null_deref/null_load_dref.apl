function foo() {
    dref 0 = 0;
    i32 a = 0;
    dref a = 0;
}

:/ OUTPUT
[WARNING] NULL-dereference error
    at: {X}.apl:2:10
[WARNING] NULL-dereference error (variable 'a' is NULL)!
    at: {X}.apl:4:16
    trace: Variable 'a' is assigned with NULL here
      at: {X}.apl:4:16
/: