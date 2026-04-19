function foo(i32 a) -> i32 {
    return a - 10;
}

start() {
    ptr i32 a = 0xB8400;
    ptr i32 b = 0xB8400;
    @[no_fall]
    @[straight]
    switch 1; {
        case 1; { 
            a = foo(10);
            if 1; {
                b = a;
            }
        }
        case 2; { a = 1002; }
        default { a = 1111; }
    }

    exit dref b;
}

:/ OUTPUT
[WARNING] [{X}apl:12:28] Function 'foo' has some arguments, which have the wrong type! Consider to use the 'as' operator!
          [{X}apl:12:28]     Value '10' has the 'i8' type! Consider the 'as i32' command!
[WARNING] [{X}apl:13:19] 'If' with a constant value 'true'!
[WARNING] [{X}apl:10:15] Condition with a constant value (variable 'tmp' is equals 'true' (1))!
          [{X}apl:10:15]     Variable 'tmp' declared as a constant here!
[WARNING] [{X}apl:10:15] Condition with a constant value (variable 'tmp' is equals 'false' (0))!
          [{X}apl:10:15]     Variable 'tmp' declared as a constant here!
[WARNING] [{X}apl:21:19] Possible NULL-dereference error (variable 'b' is NULL)!
          [{X}apl:14:19]     Variable 'b' becomes NULL-value
/: