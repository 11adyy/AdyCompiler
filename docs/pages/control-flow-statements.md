# Control flow statements

APL control-flow syntax is C-like, but conditions are followed by `;`.

## `if` and `else`

```apl
if condition; {
    statement;
}
else {
    statement;
}
```

Single-statement branches are also supported:

```apl
start() {
    i64 x = 2;
    if x == 1; putc('A');
    else if x == 2; putc('B');
    else putc('C');
    exit 0;
}
```

## `while`

```apl
while condition; {
    statement;
}

while condition; statement;
```

Example:

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

## `loop`

`loop` creates an unconditional loop:

```apl
loop {
    if done; break;
}
```

A counted loop can be created with `@[counter]`:

```apl
@[counter(10)] loop {
    putc('x');
}
```

`@[counter]` accepts a constant.

## `switch`

```apl
switch value; {
    case 1; {
        putc('A');
        break;
    }
    case 2; {
        putc('B');
        break;
    }
    default {
        putc('?');
        break;
    }
}
```

Cases fall through unless you use `break` or annotate the switch with `@[no_fall]`:

```apl
@[no_fall]
switch code; {
    case 'A'; { putc('A'); }
    case 'B'; { putc('B'); }
    default  { putc('?'); }
}
```

By default, `switch` is generated through a binary-search-style decision tree. Use `@[straight]` to request linear case selection.
