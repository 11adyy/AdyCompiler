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
[WARNING] [{X}apl:4:11] 'If' with a constant value 'true'!
[WARNING] [{X}apl:6:25] NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:5:11]     Variable 'a' is assigned with NULL here
/:
