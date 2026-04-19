function foo() {
    ptr i32 a = 0;
    a[0] = 0;
}

:/ OUTPUT
[WARNING] [{X}apl:3{X}] NULL-dereference error (variable 'tmp' is NULL)!
          [{X}apl:3:11]     Variable 'tmp' is assigned with NULL here
/:
