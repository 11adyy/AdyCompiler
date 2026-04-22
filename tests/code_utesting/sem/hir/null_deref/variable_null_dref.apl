function foo() {
    ptr i32 a = 0;
    i32 b = dref a;
}

:/ OUTPUT
[WARNING] [{X}apl:3:9] NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:2:14]     Variable 'a' is assigned with NULL here
/:
