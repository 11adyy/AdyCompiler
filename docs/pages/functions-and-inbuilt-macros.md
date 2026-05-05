# Functions and inbuilt macros
## Functions
Functions are defined with the `function` keyword. If you want to use a function from another `.apl` file (or from another language that supports the `extern` mechanism), mark it with `glob`.

One important detail: APL renames local functions internally using a pattern such as `__apl_{name}{id}`. If you want to preserve the symbol name for external use, prefer `glob`.

```apl
function min(i32 a) -> i0 { return; }
glob function chloe(i32 a = 10) -> u64 { return a + 10; }
function max(u64 a = chloe(11)) -> i32 { return a + 10; }
```

Name transformation example:
```apl
function foo();      : __apl_foo0 :
glob function foo(); : foo        :
```

**Note:** Global functions do not support overloading or scoping.

## Prototypes
A function may have a prototype, similarly to C. A prototype is a declaration without a body.

```apl
function chloe(i32 a = 10) -> u64;

function max() -> i32 {
    return chloe();
}

function chloe(i32 a = 10) -> u64 {
    return a + 10;
}
```

## Default arguments
APL supports default function arguments. If you omit trailing arguments, the compiler inserts the defaults.

```apl
chloe();              : chloe(10); :
max();                : max(chloe(11)); :
min(max() & chloe()); : min(max(chloe(11)) & chloe(10)); :
```

Restrictions:
- A default argument cannot appear before a non-default one:
```apl
function foo(i32 a = 1, i32 b); : <= Forbidden :
```
- Defaults must be duplicated in both the prototype and the definition.

## Function overloading
APL supports function overloading, but with several restrictions that come from the compiler architecture.

Rules:
- **No return-type overloading** — APL does not distinguish overloads by return type.
- **Local-only overloading** — overloaded functions are neither `glob` nor `extern`.
- **Same scope** - function will search overload candidates only in the same scope with the original one.

This works:
```apl
function foo(i32 a);
function foo();
function foo(i8 a);
```

To make overload resolution explicit, use the `as` keyword:
```apl
foo(10 as i32); : function foo(i32 a); :
: i64 a; :
foo(a as i8);   : function foo(i8 a);  :
```

**Important:** the same type-system rule applies here as everywhere else in APL: **widening may be implicit, but narrowing is allowed only with `as`.** In practice, `as` is also the safest way to select the exact overload you want.

These overload sets are invalid:
```apl
function foo() -> i32;
function foo() -> i0;
```

```apl
function foo(i32 a, i32 b = 1, i32 c = 1);
function foo(i32 a, i32 b = 1);
```

## Generics
APL supports generic functions in the way to simplify system design and reduce the final amount of lines of code. The same result can be performed with overload functions as well, but it will cost additional lines of code which is not a good way of problem solving. </br>
In few words, the generics work almost the same as they do in Rust language. To create a generic function you will need to use `<>` placeholder in a function declaration:
```apl
function chloe<MAX>(MAX a) -> MAX;
```

Then you can use this function 'template' via call with selected types:
```apl
chloe<i32>(1);
```

It will create its own implementation of this function with the selected type like this:
```
function chloe(i32 a) -> i32;
```

Also, it is important to know, that this mechanism supports the nested generic functions which means, you actually able to use the next structure of a program:
```apl
function foo<U, T>(U a, T b) -> U;
function bar<K, L, M>() -> M {
    K a = foo<K, L>(10, 10);
    return a as M;
}
```

**Note 1:** You can create default arguments in the same way as you can do this in regular functions. </br>
**Note 2:** You can declare a generic function as a header in the same way as you can do this with a regular function. </br>
**Note 3:** You can't use overloads with generic functions. Overloads can be used as an alternative approach if you want change the logic of a function. </br>
**Note 4:** Lambda function can't be a generic function.

## Function pointers
A function can be stored as a pointer:

```apl
function foo(i32 a) -> i32;
start() {
    ptr i0 a = foo;
    i32 res = a(100);
}
```

A function pointer has no signature information. Because of that, static analysis, overload resolution, and default arguments no longer apply.

```apl
function foo(i32 a) -> i32;
function foo(u32 a = 10) -> i0;
function bar(i8 a = 'a');

start() {
    ptr i0 a = foo; : Will store the first matching function symbol :
    ptr i0 b = bar;
    b();            : Undefined behavior: no signature, no defaults checked :
}
```

That flexibility can still be useful when several functions share the same effective calling pattern:

```apl
function min(i32 a, i32 b);
function max(i32 a, i32 b);

function logic(ptr i0 func, i32 a, i32 b) {
    func(a, b);
}

start() {
    logic(min, 10, 20);
    logic(max, 10, 20);
}
```

A function pointer does not even have to originate from a function symbol. Any `ptr i0` can be called:

```apl
((0x100 + 0xB045) as ptr i0)(100); : <- Calls code at 0xB145 if valid :
ptr i0 a = 123;
a(100 + 123);                      : <- Calls whatever is located there :
```

## Local functions
A function may define another function inside its body:

```apl
function foo() {
    function bar() {
    }
}
```

Local functions do not capture the parent environment, but they can be returned as pointers:

```apl
function foo() -> ptr i0 {
    function getter() {
        return 10;
    }
    return getter;
}
```

Because local functions have their own scope, local and global functions may reuse the same name:

```apl
function bar() {
    function foo() {
    }
    foo();
}

function foo();

start() {
    foo();
}
```

This is mostly syntax sugar. The same functions could be defined at top level, though then you would need globally unique names.

## Lambda functions
Lambda functions in APL are based on local functions. They do **not** capture outer local variables, so they serve as lightweight logic containers rather than full closures.

```apl
@[entry]
function main() {
    function local(i32 a) { return a + 10; }
    ptr i0 lambda = (i32 a) => a + 10;
    : local(10) == lambda(10) :
}
```

The same idea is useful when passing logic to another function:

```apl
function foo(ptr i0 logic) {
    return logic(10, 10);
}

start() {
    foo((i32 a, i32 b) => { a += b; a + b; });
}
```

Equivalent form with a named local function:

```apl
function foo(ptr i0 logic) {
    return logic(10, 10);
}

start() {
    function local(i32 a, i32 b) {
        a += b;
        return a + b;
    }
    foo(local);
}
```

The main advantage of lambdas is the lack of naming overhead.

## Variadic arguments
APL supports variadic arguments in a C-like way. To define one, place `...` as the final argument:

```apl
function foo(...) -> i0;
```

Use the `poparg` annotation to extract arguments:

```apl
function foo(...) -> i0 {
    @[poparg] i8 a1;
    @[poparg] i8 a2;
}
```

The same annotation can be used in a non-variadic function body as well:

```apl
function foo(i32 a, i32 b) -> i0 {
    @[poparg] i8 a1; : a :
    @[poparg] i8 b1; : b :
}
```

## Calling convention (system information)
Calling convention details depend on the target architecture. For example, `x86_64_gnu_nasm` follows the C calling convention. The same idea applies to `x86_32_gnu_nasm` and `x86_16_gnu_nasm` once those targets are fully ready.

Function results are returned in the target return register (for example `rax`, `ax`, or `al`), and the function preserves registers that it uses when required by the target rules.

```apl
function foo() {
    mov r10, 10
}

push r10 : <= Save r10 :
foo();
i32 res = rax;
pop r10
```

## Built-in macros
APL provides two especially useful built-in mechanisms for low-level programming: `syscall` and `asm`.

### `syscall`
`syscall` is invoked like a regular function call, but it can accept a variable number of arguments depending on the platform ABI.

```apl
str msg = "Hello, World!";
syscall(1, 1, ref msg, strlen(ref msg));
```

### `asm`
`asm` allows inline assembly. You may pass any number of APL values into the argument list and then reference them in the assembly block via `%<num>` placeholders.

```apl
i32 a = 0;
i32 ret;
asm(a, ret) {
    "push rax",
    "mov rax, %0", : mov rax, a   :
    "syscall",
    "mov %1, rax", : mov ret, rax :
    "pop rax"
}
```

**Note:** inline assembly is not optimized by the compiler.

## How inline assembly works (system information)
Inline assembly is powerful, but also dangerous. The compiler cannot safely reason about everything that happens inside the block, so you should preserve the registers you modify and make sure the assembly matches the selected target architecture.

```apl
asm() {
    "push rax",
    "mov rax, 10",
    "pop rax"
}
```

The block is copied almost directly into the final output after placeholder substitution. Because of that:
- write assembly in the syntax required by the target backend,
- avoid labels and jumps when possible,
- prefer `--no-optimizations` if the block depends on non-local control flow assumptions.

Example of a fragile pattern:
```apl
asm() {
    "jmp label1"
}

i32 a; : <= Dead code from the compiler point of view :

asm() {
    "label1:"
}
```
