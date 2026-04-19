start() {
    ptr i0 a = 0xB800;
    if 1; {
        a = 0;
    }
    a();
}

:/ OUTPUT
[WARNING] [{X}apl:3:11] 'If' with a constant value 'true'!
[WARNING] [{X}apl:6:7] Possible NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:4:11]     Variable 'a' becomes NULL-value
/:
