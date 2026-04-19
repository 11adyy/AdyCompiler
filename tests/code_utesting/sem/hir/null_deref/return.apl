function foo() -> ptr i32 {
    return 0;
}

start() {
    ptr i32 a = foo();
    exit dref a;
}

:/ OUTPUT
[WARNING] [{X}apl:7:19] NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:6:17]     Variable 'a' is assigned with NULL here
/:
