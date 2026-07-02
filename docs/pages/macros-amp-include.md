# Macros & include

APL has a small preprocessor. It runs before tokenization and supports:

- `#include`
- `#define`
- `#undef`
- `#ifdef`
- `#ifndef`

It also inserts `#line` markers internally so diagnostics and later compiler stages can track source locations after includes are expanded.

## Includes

Quoted includes first search relative to the current file:

```apl
#include "print_h.apl"
```

System-style includes search the directory passed with `-I`, then the standard
library shipped with the compiler:

```apl
#include <stdio_h.apl>
```

Example command:

```bash
./builds/linux-x86_64/aplc -I examples --output app main.apl
```

The standard library location can be overridden with `APL_INCLUDE_PATH` and
inspected with `aplc --print-stdlib-path`.

## Header pattern

Implementation file:

```apl
function strlen(ptr i8 s) -> i64 {
    i64 l = 0;
    while dref s; {
        s += 1;
        l += 1;
    }

    return l;
}
```

Header file:

```apl
#ifndef STRING_H_
#define STRING_H_ 0

function strlen(ptr i8 s) -> i64;

#endif
```

Use the header from another file:

```apl
#include "string_h.apl"

start() {
    i64 n = strlen(ref "abc");
    exit n as u8;
}
```

## Defines

`#define` performs identifier replacement. Function-like macro definitions may be parsed enough to skip their parameter list, but function-style macro expansion is not implemented as a C-compatible feature.

```apl
#define COUNT 3

arr data[COUNT, i8] = { 'A', 'B', 'C' };
```

Conditional compilation:

```apl
#ifndef PRINT_H_
#define PRINT_H_ 0
function print(ptr i8 s) -> i0;
#endif
```

Remove a definition:

```apl
#undef PRINT_H_
```

## Comments

APL uses colon comments:

```apl
: one-line comment :

:/ block comment
   across several lines /:
```

The preprocessor removes these comments before tokenization while preserving strings and character literals.
