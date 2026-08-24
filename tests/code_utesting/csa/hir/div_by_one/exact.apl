start() {
    i32 a = 10;
    i32 b = 1;
    exit (a / b) as u8;
}

:/ OUTPUT
[WARNING] Division by one! This expression won't change anything! (variable 'b' is '1')!
    at: {X}.apl:4:10
    trace: Variable 'b' is assigned with '1' here
      at: {X}.apl:3:9
/:
