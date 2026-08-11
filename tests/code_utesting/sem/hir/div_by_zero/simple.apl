start() {
    i32 a = 0;
    exit (10 / a) as u8;
}

:/ OUTPUT
[WARNING] Division by zero error! (variable 'a' is '0')!
    at: {X}.apl:3:10
    trace: Variable 'a' is assigned with '0' here
      at: {X}.apl:2:9
/:
