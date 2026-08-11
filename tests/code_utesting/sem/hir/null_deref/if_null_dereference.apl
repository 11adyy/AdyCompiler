start() {
    ptr i32 a = 1;
    ptr i32 b = 1;
    if 1; {
        a = 0;
        return dref a;
    }

    return 0;
}

:/ OUTPUT
[WARNING] 'If' with a constant value 'true'!
    at: {X}.apl:4:8
[WARNING] NULL-dereference error (variable 'a' is NULL)!
    at: {X}.apl:6:16
    trace: Variable 'a' is assigned with NULL here
      at: {X}.apl:5:14
/: