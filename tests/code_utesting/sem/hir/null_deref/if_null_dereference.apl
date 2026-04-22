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
[WARNING] [{X}apl:4:8] 'If' with a constant value 'true'!
[WARNING] [{X}apl:6:16] NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:5:14]     Variable 'a' is assigned with NULL here
/:
