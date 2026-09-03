# Build, install, and package

## Install from source

To install the compiler, clone the repository first:

```bash
git clone --recurse-submodules https://github.com/11adyy/AdyCompiler.git
```

Then, if you want to use the VS Code extension and the standard APL library, run:

```bash
make submodules
```

### Dependencies

After cloning, make sure your system has the required packages. On Ubuntu, run:

```bash
sudo apt install gcc nasm
```

For Fedora:

```bash
sudo dnf install gcc nasm
```

*P.S.:* You can also install the `z3` package. It improves the static analyzer's overall performance, but it is optional.

## Build the compiler

Once the dependencies are installed, build the compiler with:

```bash
make all
```

*P.S.:* This command will create the `build` directory.

To run the compiler, use:

```bash
./builds/$(uname -s | tr '[:upper:]' '[:lower:]')-$(uname -m)/aplc --version
```

## Build the standard library from the Makefile

To build the APL standard library, run:

```bash
make CCClib
```

This builds the compiler if needed, compiles the implementation files from the standard-library source directory, and writes the static archive here:

```
builds/<platform>/CCClib/libapl.a
```

`CCClib_SRC_DIR` defaults to the `CCClib` submodule. Sibling checkouts can still be selected explicitly:

```bash
make CCClib_SRC_DIR=../CCClib CCClib
```

## Install

Finally, if you want to use the `aplc` command instead of an absolute path, run:

```bash
sudo make install
```

The default installation layout is:

```text
/usr/local/bin/aplc
/usr/local/share/apl/include/
/usr/local/share/doc/apl/
/usr/local/share/bash-completion/completions/aplc
/usr/local/share/zsh/site-functions/_aplc
/usr/local/share/fish/vendor_completions.d/aplc.fish
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

## Shell completion

`make install` installs TAB completion for bash, zsh, and fish. Open a new shell after installation; most distributions load files from the standard completion directories automatically.

For a local checkout without installing, load completion manually:

```bash
# bash
source completions/aplc.bash

# zsh
fpath=("$PWD/completions" $fpath)
autoload -Uz compinit
compinit

# fish
mkdir -p ~/.config/fish/completions
ln -sf "$PWD/completions/aplc.fish" ~/.config/fish/completions/aplc.fish
```

The install paths can be overridden for unusual distributions:

```bash
make install PREFIX=/usr \
  BASH_COMPLETION_DIR=/usr/share/bash-completion/completions \
  ZSH_COMPLETION_DIR=/usr/share/zsh/site-functions \
  FISH_COMPLETION_DIR=/usr/share/fish/vendor_completions.d
```

## Build the VS Code extension package

The Docker targets use `VSCODE_DIR`, which defaults to `vscode`:

```bash
make vscode-docker-package
make VSCODE_DIR=../Ady-vscode vscode-docker-package
```
