start() {
    ptr i32 a = 1;
    @[straight]
    switch 1; {
        case 1; { a = 1; break; }
        case 2; { a = 0; }
        default { a = 0; }
    }
    dref a = 0;
}

:/ OUTPUT
[WARNING] Condition with a constant value (variable 'tmp' is equals 'true' (1))!
    at: {X}.apl:4:15
    trace: Variable 'tmp' declared as a constant here!
      at: {X}.apl:4:15
[WARNING] Possible NULL-dereference error (variable 'a' is NULL)!
    at: {X}.apl:9:16
    trace: Variable 'a' becomes NULL
      at: {X}.apl:7:23
[WARNING] Condition with a constant value (variable 'tmp' is equals 'false' (0))!
    at: {X}.apl:9:16
    trace: Variable 'tmp' declared as a constant here!
      at: {X}.apl:4:15
/: