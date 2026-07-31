# Build, install, and package

## Build from source

Build an optimized compiler and run it directly from the repository:

```bash
make release
./builds/$(uname -s | tr '[:upper:]' '[:lower:]')-$(uname -m)/aplc --version
```

The development binary automatically finds the `CCClib` submodule directory in the repository. </br>
Clone with submodules, or initialize them after cloning:

```bash
git clone --recurse-submodules https://github.com/11adyy/AdyCompiler.git
make submodules
```

## Build the standard library from the Makefile

The root `Makefile` has a separate target for the APL runtime library:

```bash
make CCClib
```

This builds the compiler if needed, compiles the implementation files from the standard-library source directory, and writes the static archive here:

```text
builds/<platform>/CCClib/libapl.a
```

For a release-mode runtime archive, pass the same build settings used by the package target:

```bash
make BUILD=release PRINT_PARSE=0 CCClib
```

`make print-config` shows the resolved library paths and inputs:

```text
CCClibDIR
CCClib_SRC_DIR
APLRUNTIMEDIR
CCClib_SOURCES
CCClib_IMPLS
CCClib_ARCHIVE
```

`CCClib_SRC_DIR` defaults to the `CCClib` submodule. Sibling checkouts can still be selected explicitly:

```bash
make CCClib_SRC_DIR=../CCClib CCClib
```

## Install

Install both `aplc` and its APL standard library:

```bash
make release
sudo make install PREFIX=/usr/local
```

The default installation layout is:

```text
/usr/local/bin/aplc
/usr/local/share/apl/include/
/usr/local/share/doc/apl/
```

`DESTDIR` is supported for distribution packaging and staged installations:

```bash
make install PREFIX=/usr DESTDIR=/tmp/apl-package-root
```

The compiler discovers installed headers automatically, so applications can use `#include <stdio_h.apl>` without passing `-I CCClib`. </br>
See the [`CCClib` reference](CCClib-reference.md) for header groups, containers, and usage examples. </br>
Use `APL_INCLUDE_PATH` to override the standard-library directory. The `-I` option adds a project include directory without disabling the standard library:

```bash
APL_INCLUDE_PATH=/opt/apl/include aplc program.apl
aplc -I project/include program.apl
aplc --print-stdlib-path
```

## Build the VS Code extension package

The Docker targets use `VSCODE_DIR`, which defaults to `vscode`:

```bash
make vscode-docker-package
make VSCODE_DIR=../Ady-vscode vscode-docker-package
```

When `vscode` is a submodule and has not been initialized, the Makefile prints the matching `git submodule update` command instead of failing later inside Docker.

## Create a relocatable package

Create an archive containing the compiler, matching headers, runtime archive, and license:

```bash
make package
```

The archive is written to:

```text
builds/apl-<version>-<platform>.tar.gz
```

Its `bin/aplc` executable discovers the adjacent `share/apl/include` directory, so the extracted tree can be moved to another prefix without rebuilding.
