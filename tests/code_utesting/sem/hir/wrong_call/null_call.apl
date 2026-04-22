start() {
    ptr i0 a = 0;
    a(10);
}

:/ OUTPUT
[WARNING] [{X}apl:3:12] NULL-dereference error (variable 'a' is NULL)!
          [{X}apl:2:13]     Variable 'a' is assigned with NULL here
/:
