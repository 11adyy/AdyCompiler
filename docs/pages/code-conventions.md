# Code conventions
*P.S. It's not a thing, but I'd like to share my prefered code style through this conventions. The compiler itself doesn't care about how a code is written.* </br>
APL encourages code mostly based on C-code conventions.
- **Variables**: use lowercase letters and underscores
```apl
i32 counter = 0;
ptr i32 data_ptr = ref counter;
dref data_ptr = 1;
```

- **Constants**: use uppercase letters with underscores
```apl
extern ptr u8 FRAMEBUFFER;
glob ro i32 WIN_X = 1080;
glob ro i32 WIN_Y = 1920;
```

- **Functions**: use lowercase letters with underscores
```apl
function calculate_sum(ptr i32 arr, i64 length) -> i32 { return 0; }
```

- **Private functions**: use an underscore before a name of a function, if it is a private function
```apl
function _private();
```

- **Scopes**: K&R style
Functions:
```apl
function foo() -> i0 {
}
```

- **Ifs**:
```apl
if cond0; {
}
else if cond1; {
}
else {
}
```

- **Loops**:
```apl
while cond0; {
}
loop {
}
```

- **Entry point**:
```apl
start(i64 argc, ptr ptr i8 argv) {
}
```

- **Comments**: Comments can be written in one line with the start and the end symbol `:` (or `:/` with `/:`) and in several lines with the same logic. Actually, this is a copy of the C's comments '/**/' (without support of the '//' comment style), which means you have to always end your comment with the 'end' comment symbol.
```apl
: Hello there
:
:
Hello there :
: Hello there :
:
Hello there
:
:/ Large comment with a colon:
/:
```

- **File names**: Sneaky case for file names. If this is a 'header' file, add the `_h` path to a name
```
print_h.apl <- Prototypes and includes
print.apl   <- Implementation
```
