function foo() {
    i32 a = 1;
    if a; {
        exit 1;
    }
    exit 2;
}

:/ OUTPUT
[WARNING] [{X}apl:3:11] Condition with a constant value (variable 'a' is equals 'true' (1))!
          [{X}apl:3:11]     Variable 'a' declared as a constant here!
/:
