: BUG :
@[entry]
function foo() {
    ptr i32 a = 1;
    ptr i32 b = 1;
    if 1; {
        @[no_fall]
        @[straight]
        switch 1; {
            case 1; { a = 0; }
            case 2; { a = 1; }
            default { a = 1; }
        }
        b = a;
    }
    else {
        a = 2;
    }
    ptr i32 c = b;
    dref c;
}

:/ OUTPUT
[WARNING] 'If' with a constant value 'true'!
    at: {X}.apl:5:8
[WARNING] Condition with a constant value (variable 'tmp' is equals 'true' (1))!
    at: {X}.apl:8:19
    trace: Variable 'tmp' declared as a constant here!
      at: {X}.apl:8:19
[WARNING] Possible NULL-dereference error (variable 'c' is NULL)!
    at: {X}.apl:19:10
    trace: Variable 'c' is assigned with 'b' here
      at: {X}.apl:18:14
    trace: Variable 'b' is assigned with 'a' here
      at: {X}.apl:13:14
    trace: Variable 'a' becomes NULL
      at: {X}.apl:9:29
[WARNING] Condition with a constant value (variable 'tmp' is equals 'false' (0))!
    at: {X}.apl:19:10
    trace: Variable 'tmp' declared as a constant here!
      at: {X}.apl:8:19
/: