start() {
    ptr i0 a = 0xB800;
    if 1; {
        a = 0;
    }
    a();
}

:/ OUTPUT
[WARNING] 'If' with a constant value 'true'!
    at: {X}.apl:3:8
[WARNING] Possible NULL-dereference error (variable 'a' is NULL)!
    at: {X}.apl:6:11
    trace: Variable 'a' becomes NULL
      at: {X}.apl:4:14
/: