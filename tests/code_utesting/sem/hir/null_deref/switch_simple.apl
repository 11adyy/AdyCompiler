@[entry]
function foo() {
    ptr i32 a = 1;
    ptr i32 b = 1;

    @[straight]
    @[no_fall]
    switch 1; {
        case 1; { a = 3; }
        case 2; { a = 2; }
        case 3; { a = 0; }
        default { a = 0; }
    }

    @[straight]
    @[no_fall]
    switch 1; {
        case 1; { b = 1; }
        case 2; { b = 2; }
        default { b = 3; }
    }

    dref a = 1;
    dref b = 1;
}

:/ OUTPUT
#
[WARNING] [{X}apl:8{X}] Condition with a constant value (variable 'tmp' is equals 'true' (1))!
          [{X}apl:8{X}]     Variable 'tmp' declared as a constant here!
[WARNING] [{X}apl:8{X}] Condition with a constant value (variable 'tmp' is equals 'false' (0))!
          [{X}apl:8{X}]     Variable 'tmp' declared as a constant here!
[WARNING] [{X}apl:8{X}] Condition with a constant value (variable 'tmp' is equals 'false' (0))!
          [{X}apl:8{X}]     Variable 'tmp' declared as a constant here!
[WARNING] [{X}apl:17{X}] Condition with a constant value (variable 'tmp' is equals 'true' (1))!
          [{X}apl:17{X}]     Variable 'tmp' declared as a constant here!
[WARNING] [{X}apl:17{X}] Condition with a constant value (variable 'tmp' is equals 'false' (0))!
          [{X}apl:17{X}]     Variable 'tmp' declared as a constant here!
#
[WARNING] [{X}apl:23{X}] Possible NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:{X}]     Variable 'a' becomes NULL-value
          [{X}apl:{X}]     Variable 'a' becomes NULL-value
/:
