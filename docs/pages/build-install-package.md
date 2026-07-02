# Build, install, and package

## Build from source

Build an optimized compiler and run it directly from the repository:

```bash
make release
./builds/$(uname -s | tr '[:upper:]' '[:lower:]')-$(uname -m)/aplc --version
```

The development binary automatically finds the `CCClib` directory in the
repository.

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

Use `APL_INCLUDE_PATH` to override the standard-library directory. The `-I`
option adds a project include directory without disabling the standard library:

```bash
APL_INCLUDE_PATH=/opt/apl/include aplc program.apl
aplc -I project/include program.apl
aplc --print-stdlib-path
```

## Create a relocatable package

Create an archive containing the compiler, matching headers, license, and
library documentation:

```bash
make package
```

The archive is written to:

```text
builds/apl-<version>-<platform>.tar.gz
```

Its `bin/aplc` executable discovers the adjacent `share/apl/include` directory,
so the extracted tree can be moved to another prefix without rebuilding.
