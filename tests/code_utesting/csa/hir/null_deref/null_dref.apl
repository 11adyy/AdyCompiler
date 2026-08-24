function foo() {
    i32 a = dref 0;
}

:/ OUTPUT
[WARNING] NULL-dereference error
    at: {X}.apl:2:9
/: