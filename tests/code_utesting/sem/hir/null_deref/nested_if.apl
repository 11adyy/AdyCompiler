start() {
    ptr i32 a = 1;
    if 1; {
        if 2; {
            a = 0;
        }
        else a = 2;
    }
    dref a = 0;
}

:/ OUTPUT
[WARNING] [{X}apl:3{X}] 'If' with a constant value 'true'!
[WARNING] [{X}apl:4{X}] 'If' with a constant value 'true'!
[WARNING] [{X}apl:9{X}] Possible NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:5{X}]     Variable 'a' becomes NULL-value
/:
