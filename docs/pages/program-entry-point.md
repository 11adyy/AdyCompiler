# Program entry point

A APL file can define an executable entry point in two ways:

- with the `start` keyword;
- with `@[entry]` or `@[entry("symbol_name")]` on a function.

## `start`

```apl
start() {
    exit 0;
}
```

`start` does not declare a return type. It may accept arguments:

```apl
start(i64 argc, ptr ptr i8 argv) {
    exit 0;
}
```

It can also be variadic and read arguments with `@[poparg]`:

```apl
start(...) {
    @[poparg] i64 argc;
    @[poparg] ptr ptr i8 argv;
    exit 0;
}
```

## `@[entry]`

`@[entry]` turns a normal function into the entry point:

```apl
@[entry]
function main() -> i0 {
    exit 0;
}
```

The default emitted entry symbol comes from the compiler configuration. Current defaults are host-dependent: Linux builds default to `main`, while the non-Linux default path uses `_main`. You can override it in source:

```apl
@[entry("_start")]
function main() -> i0 {
    exit 0;
}
```

or from the command line:

```bash
./builds/<platform>/aplc --entry-name _start main.apl
```

## Rules

- An entry point should finish with `exit <code>;`.
- `exit` accepts a process exit code; keep it in the 0..255 range.
- A plain function named `main` is not special unless it has `@[entry]`.
- More than one entry point is an error.
- If a file has no entry point, it can still be compiled as part of a larger build or used as a library-like unit.
- `@[naked]` can be used on an entry point when you want to suppress normal entry/exit routines.
