start() {
    syscall(0x2000004, 1 as i32, 0 as ptr i0, 12);
}

:/ OUTPUT
[WARNING] [{X}apl:2:63] NULL-dereference error (variable 'tmp' is NULL)!
          [{X}apl:2:44]     Variable 'tmp' is assigned with NULL here
/: