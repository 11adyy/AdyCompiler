function foo() {
    i32 a = 10 - 10;
    i32 b = 123;

    i64 c = a * b;
    ptr i64 e = c as ptr i64;

    return dref e;
}

:/ OUTPUT
[WARNING] [{X}apl:8:12] NULL-dereference error (variable 'e' is NULL)!
          [{X}apl:6:14]     Variable 'e' is assigned with NULL here
/:
