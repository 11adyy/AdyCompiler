# Build, install, and package

## Build from source

Build an optimized compiler and run it directly from the repository:

```bash
make release
./builds/$(uname -s | tr '[:upper:]' '[:lower:]')-$(uname -m)/aplc --version
```

The development binary automatically finds the `CCClib` directory in the
repository.

## Build the standard library from the Makefile

The root `Makefile` has a separate target for the APL runtime library:

```bash
make CCClib
```

This builds the compiler if needed, compiles the implementation files from
`CCClib/*.apl` that are not headers, and writes the static archive here:

```text
builds/<platform>/CCClib/libapl.a
```

For a release-mode runtime archive, pass the same build settings used by the
package target:

```bash
make BUILD=release PRINT_PARSE=0 CCClib
```

`make print-config` shows the resolved library paths and inputs:

```text
CCClibDIR
APLRUNTIMEDIR
CCClib_IMPLS
CCClib_ARCHIVE
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

The compiler discovers installed headers automatically, so applications can
use `#include <stdio_h.apl>` without passing `-I CCClib`.

See the [`CCClib` reference](CCClib-reference.md) for header groups,
containers, and usage examples.

Use `APL_INCLUDE_PATH` to override the standard-library directory. The `-I`
option adds a project include directory without disabling the standard library:

```bash
APL_INCLUDE_PATH=/opt/apl/include aplc program.apl
aplc -I project/include program.apl
aplc --print-stdlib-path
```

## Create a relocatable package

Create an archive containing the compiler, matching headers, runtime archive,
and license:

```bash
make package
```

The archive is written to:

```text
builds/apl-<version>-<platform>.tar.gz
```

Its `bin/aplc` executable discovers the adjacent `share/apl/include` directory,
so the extracted tree can be moved to another prefix without rebuilding.
