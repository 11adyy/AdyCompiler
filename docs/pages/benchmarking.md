# APL code performance evaluation

This page records the current Linux x86-64 and i386 microbenchmark run for APL code generation. The benchmark source of truth is `specs/run_compiler_microbenches.py`; raw commands, exit codes, compile times, and ten runtime repetitions are stored in `specs/compiler_microbench_results.json`.

The current comparison intentionally uses only the compilers available in the system toolchain: APL, GCC, and Clang.

## Setup

Versions:
- `aplc`: capl 3.6.5.1:1706.26
- `gcc`: GCC 15.2.1 20260123 (Red Hat 15.2.1-7)
- `clang`: Clang 21.1.8 (Fedora 21.1.8-4.fc43)
- `nasm`: NASM 2.16.03
- `ld`: GNU ld 2.45.1

Host:
- OS: Linux 7.0.12-101.fc43.x86_64
- Host architecture: x86_64
- Target architectures: x86-64 Linux and i386 Linux
- Runs: 10 per produced binary

The compiler was built with:

```bash
make BUILD=release PRINT_PARSE=0
```

APL binaries were built through an explicit object path. For x86-64 the target triple is `--arch x86_64 --sys-type linux64 --asm-format elf64`; for i386 it is `--arch i386 --sys-type i386 --asm-format elf32`.

```bash
./builds/linux-x86_64/aplc -O3 \
  --arch x86_64 \
  --sys-type linux64 \
  --asm-format elf64 \
  -c \
  --output /tmp/bench_x64.o \
  --emit-asm \
  --asm-output /tmp/bench_x64.asm \
  /tmp/bench.apl

ld -e _main -o /tmp/bench_x64 /tmp/bench_x64.o

./builds/linux-x86_64/aplc -O3 \
  --arch i386 \
  --sys-type i386 \
  --asm-format elf32 \
  -c \
  --output /tmp/bench_i386.o \
  --emit-asm \
  --asm-output /tmp/bench_i386.asm \
  /tmp/bench.apl

ld -m elf_i386 -e _main -o /tmp/bench_i386 /tmp/bench_i386.o
```

GCC and Clang baselines use freestanding `_main` entry points so i386 does not depend on 32-bit libc or CRT startup files:

```bash
gcc -m64 -O3 -std=c11 -ffreestanding -nostdlib -fno-pie -no-pie -Wl,-e,_main bench.c -o bench_gcc_x64
clang -m64 -O3 -std=c11 -ffreestanding -nostdlib -fno-pie -no-pie -Wl,-e,_main bench.c -o bench_clang_x64

gcc -m32 -mstackrealign -O3 -std=c11 -ffreestanding -nostdlib -fno-pie -no-pie -Wl,-e,_main bench.c -o bench_gcc_i386
clang -m32 -mstackrealign -O3 -std=c11 -ffreestanding -nostdlib -fno-pie -no-pie -Wl,-e,_main bench.c -o bench_clang_i386
```

All benchmarked binaries returned the expected exit code in all ten runs.

## Benchmarked Snippets

The APL snippets come from `tests/code_utesting/exec/prod`:

| Benchmark | APL source | Expected exit |
|---|---|---:|
| Empty counted loop | `02_count_to_billion.apl` | 0 |
| Arithmetic recurrence | `04_arith_mix.apl` | 1 |
| Hot branch loop | `05_branch_hot.apl` | 7 |
| Hot function call | `06_function_call_hot.apl` | 13 |
| Global table traversal | `07_table_sum_hot.apl` | 32 |
| Pointer string scan | `08_pointer_string_scan.apl` | 64 |
| Fibonacci recurrence | `09_fibonacci.apl` | 187 |

These examples cover loop overhead, scalar recurrence, predictable branching, function calls, global array traversal, pointer/string traversal, and a short loop-carried dependency.

## Runtime Summary

Mean runtime in seconds over ten runs. Lower is better.

### x86-64 Linux

| Benchmark | APL -O3 | GCC -O3 | Clang -O3 | APL -O0 | GCC -O0 | Clang -O0 |
|---|---:|---:|---:|---:|---:|---:|
| Empty counted loop | 0.261887 | 0.260706 | 0.261217 | 0.943493 | 2.732771 | 2.743791 |
| Arithmetic recurrence | 0.319541 | 0.264630 | 0.021762 | 0.420121 | 0.472506 | 0.426030 |
| Hot branch loop | 0.263617 | 0.080978 | 0.056354 | 0.469712 | 0.522766 | 0.520616 |
| Hot function call | 0.151619 | 0.105209 | 0.026664 | 0.286096 | 0.286031 | 0.315833 |
| Global table traversal | 0.091685 | 0.002133 | 0.002328 | 0.143158 | 0.119041 | 0.140017 |
| Pointer string scan | 0.084198 | 0.004427 | 0.000176 | 0.135586 | 0.095225 | 0.106931 |
| Fibonacci recurrence | 0.000938 | 0.000467 | 0.000470 | 0.001268 | 0.002113 | 0.002122 |

### i386 Linux

| Benchmark | APL -O3 | GCC -O3 | Clang -O3 | APL -O0 | GCC -O0 | Clang -O0 |
|---|---:|---:|---:|---:|---:|---:|
| Empty counted loop | 0.261450 | 0.261913 | 0.261629 | 0.951507 | 2.744684 | 2.751128 |
| Arithmetic recurrence | 0.474456 | 0.327300 | 0.021911 | 0.540225 | 0.535768 | 0.433954 |
| Hot branch loop | 0.381038 | 0.150469 | 0.072008 | 0.464537 | 0.470560 | 0.415575 |
| Hot function call | 0.330364 | 0.163568 | 0.026601 | 0.399027 | 0.396996 | 0.374836 |
| Global table traversal | 0.112236 | 0.009064 | 0.002387 | 0.194468 | 0.121796 | 0.132445 |
| Pointer string scan | 0.142074 | 0.030128 | 0.000196 | 0.191890 | 0.094678 | 0.106399 |
| Fibonacci recurrence | 0.002809 | 0.000456 | 0.000479 | 0.002066 | 0.002117 | 0.002140 |

## Empty Counted Loop

Source: `tests/code_utesting/exec/prod/02_count_to_billion.apl`

<div
  class="benchmark-card"
  data-title="Empty counted loop, x86-64"
  data-labels="gcc -O3|clang -O3|apl -O3|apl -O0|gcc -O0|clang -O0"
  data-values="0.260706|0.261217|0.261887|0.943493|2.732771|2.743791"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

<div
  class="benchmark-card"
  data-title="Empty counted loop, i386"
  data-labels="apl -O3|clang -O3|gcc -O3|apl -O0|gcc -O0|clang -O0"
  data-values="0.261450|0.261629|0.261913|0.951507|2.744684|2.751128"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

## Arithmetic Recurrence

Source: `tests/code_utesting/exec/prod/04_arith_mix.apl`

<div
  class="benchmark-card"
  data-title="Arithmetic recurrence, x86-64"
  data-labels="clang -O3|gcc -O3|apl -O3|apl -O0|clang -O0|gcc -O0"
  data-values="0.021762|0.264630|0.319541|0.420121|0.426030|0.472506"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

<div
  class="benchmark-card"
  data-title="Arithmetic recurrence, i386"
  data-labels="clang -O3|gcc -O3|clang -O0|apl -O3|gcc -O0|apl -O0"
  data-values="0.021911|0.327300|0.433954|0.474456|0.535768|0.540225"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

## Hot Branch Loop

Source: `tests/code_utesting/exec/prod/05_branch_hot.apl`

<div
  class="benchmark-card"
  data-title="Hot branch loop, x86-64"
  data-labels="clang -O3|gcc -O3|apl -O3|apl -O0|clang -O0|gcc -O0"
  data-values="0.056354|0.080978|0.263617|0.469712|0.520616|0.522766"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

<div
  class="benchmark-card"
  data-title="Hot branch loop, i386"
  data-labels="clang -O3|gcc -O3|apl -O3|clang -O0|apl -O0|gcc -O0"
  data-values="0.072008|0.150469|0.381038|0.415575|0.464537|0.470560"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

## Hot Function Call

Source: `tests/code_utesting/exec/prod/06_function_call_hot.apl`

<div
  class="benchmark-card"
  data-title="Hot function call, x86-64"
  data-labels="clang -O3|gcc -O3|apl -O3|apl -O0|gcc -O0|clang -O0"
  data-values="0.026664|0.105209|0.151619|0.286096|0.286031|0.315833"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

<div
  class="benchmark-card"
  data-title="Hot function call, i386"
  data-labels="clang -O3|gcc -O3|apl -O3|clang -O0|gcc -O0|apl -O0"
  data-values="0.026601|0.163568|0.330364|0.374836|0.396996|0.399027"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

## Global Table Traversal

Source: `tests/code_utesting/exec/prod/07_table_sum_hot.apl`

<div
  class="benchmark-card"
  data-title="Global table traversal, x86-64"
  data-labels="gcc -O3|clang -O3|apl -O3|gcc -O0|clang -O0|apl -O0"
  data-values="0.002133|0.002328|0.091685|0.119041|0.140017|0.143158"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

<div
  class="benchmark-card"
  data-title="Global table traversal, i386"
  data-labels="clang -O3|gcc -O3|apl -O3|gcc -O0|clang -O0|apl -O0"
  data-values="0.002387|0.009064|0.112236|0.121796|0.132445|0.194468"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

## Pointer String Scan

Source: `tests/code_utesting/exec/prod/08_pointer_string_scan.apl`

<div
  class="benchmark-card"
  data-title="Pointer string scan, x86-64"
  data-labels="clang -O3|gcc -O3|apl -O3|gcc -O0|clang -O0|apl -O0"
  data-values="0.000176|0.004427|0.084198|0.095225|0.106931|0.135586"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

<div
  class="benchmark-card"
  data-title="Pointer string scan, i386"
  data-labels="clang -O3|gcc -O3|gcc -O0|clang -O0|apl -O3|apl -O0"
  data-values="0.000196|0.030128|0.094678|0.106399|0.142074|0.191890"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

## Fibonacci Recurrence

Source: `tests/code_utesting/exec/prod/09_fibonacci.apl`

<div
  class="benchmark-card"
  data-title="Fibonacci recurrence, x86-64"
  data-labels="gcc -O3|clang -O3|apl -O3|apl -O0|clang -O0|gcc -O0"
  data-values="0.000467|0.000470|0.000938|0.001268|0.002113|0.002122"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

<div
  class="benchmark-card"
  data-title="Fibonacci recurrence, i386"
  data-labels="gcc -O3|clang -O3|apl -O0|gcc -O0|clang -O0|apl -O3"
  data-values="0.000456|0.000479|0.002066|0.002117|0.002140|0.002809"
  data-dataset-label="Runtime"
  data-y-label="Seconds"
  data-tooltip-suffix=" s"
>
  <div class="benchmark-chart-wrap">
    <canvas class="benchmark-chart"></canvas>
  </div>
</div>

## Notes

The benchmark is still a microbenchmark suite, not a whole-program performance claim. The table and string scans are especially sensitive to how aggressively C compilers simplify loops and memory reads. The raw JSON keeps the exact commands and run values so failures or suspicious outliers can be audited instead of papered over.
