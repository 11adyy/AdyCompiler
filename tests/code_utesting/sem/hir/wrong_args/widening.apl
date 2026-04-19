function foo(i32 a);
start() {
    foo(10);
}

:/ OUTPUT
[WARNING] [{X}apl:3:14] Function 'foo' has some arguments, which have the wrong type! Consider to use the 'as' operator!
          [{X}apl:3:14]     Value '10' has the 'i8' type! Consider the 'as i32' command!
/: