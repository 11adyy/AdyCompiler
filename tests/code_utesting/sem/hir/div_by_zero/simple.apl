start() {
    i32 a = 0;
    exit (10 / a) as u8;
}

:/ OUTPUT
[WARNING] [{X}.apl:3:10] Division by zero error! (variable 'a' is '0')!
          [{X}.apl:2:9]     Variable 'a' is assigned with '0' here
/: