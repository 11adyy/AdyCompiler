CC ?= gcc
PYTHON ?= python3
RM ?= rm -f
MKDIR_P ?= mkdir -p
INSTALL ?= install

PREFIX ?= /usr/local
DESTDIR ?=
BINDIR ?= $(PREFIX)/bin
DATADIR ?= $(PREFIX)/share
CCClibDIR ?= $(DATADIR)/apl/include
DOCDIR ?= $(DATADIR)/doc/apl
VERSION ?= 3.6_X

BUILD ?= debug
AVAILABLE_MEMORY ?= 16777216
LOGS ?=
PRINT_PARSE ?= 1
ENABLE_Z3 ?= auto
INPUT ?= examples/print.apl
RUN_ARGS ?= --arch x86_64 --sys-type linux64 --asm-format elf64 --linker gcc --linker-no-pie
MODULE ?= asm
TEST_CODE ?= dummy_data/simple.apl
UTEST ?= code_utesting
STD_UTEST ?= std_utesting

Z3_AVAILABLE := $(shell pkg-config --exists z3 2>/dev/null && echo 1 || echo 0)
ifeq ($(ENABLE_Z3),auto)
	Z3_ENABLED := $(Z3_AVAILABLE)
else
	Z3_ENABLED := $(ENABLE_Z3)
endif

ifeq ($(Z3_ENABLED),1)
	Z3_CFLAGS ?= $(shell pkg-config --cflags z3 2>/dev/null)
	Z3_LDLIBS ?= $(shell pkg-config --libs z3 2>/dev/null)
	ifeq ($(strip $(Z3_LDLIBS)),)
		Z3_LDLIBS = -lz3
	endif
else
	Z3_CFLAGS :=
	Z3_LDLIBS :=
endif

PLATFORM ?= $(shell uname -s | tr '[:upper:]' '[:lower:]')-$(shell uname -m | tr '[:upper:]' '[:lower:]')

SOURCES := $(sort $(shell find src std -type f -name '*.c'))
OUTPUT = builds/$(PLATFORM)/aplc

CPPFLAGS += -Iinclude -DALLOC_BUFFER_SIZE=$(AVAILABLE_MEMORY) -DAPL_DEFAULT_INCLUDE_DIR=\"$(CCClibDIR)\"
CFLAGS += -Wall -Wno-int-conversion
LDFLAGS +=
LDLIBS +=

ifeq ($(BUILD),debug)
	CFLAGS += -g -O0
else ifeq ($(BUILD),release)
	CFLAGS += -O2
else
	$(error Unknown BUILD=$(BUILD), use debug or release)
endif

ifeq ($(PRINT_PARSE),1)
	CPPFLAGS += -DPRINT_PARSE
endif

ifeq ($(Z3_ENABLED),1)
	CPPFLAGS += -DAPL_ENABLE_Z3 $(Z3_CFLAGS)
	LDLIBS += $(Z3_LDLIBS)
endif

ifneq ($(filter error,$(LOGS)),)
	CPPFLAGS += -DERROR_LOGS
endif

ifneq ($(filter warn,$(LOGS)),)
	CPPFLAGS += -DWARNING_LOGS
endif

ifneq ($(filter info,$(LOGS)),)
	CPPFLAGS += -DINFO_LOGS
endif

ifneq ($(filter debug,$(LOGS)),)
	CPPFLAGS += -DDEBUG_LOGS
endif

ifneq ($(filter io,$(LOGS)),)
	CPPFLAGS += -DIO_OPERATION_LOGS
endif

ifneq ($(filter mem,$(LOGS)),)
	CPPFLAGS += -DMEM_OPERATION_LOGS
endif

ifneq ($(filter logging,$(LOGS)),)
	CPPFLAGS += -DLOGGING_LOGS
endif

ifneq ($(filter special,$(LOGS)),)
	CPPFLAGS += -DSPECIAL_LOGS
endif

all: $(OUTPUT) ## Build the compiler with the current configuration.

$(OUTPUT): $(SOURCES)
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@ $(LDFLAGS) $(LDLIBS)

debug: ## Build a debug compiler.
	$(MAKE) BUILD=debug all

release: ## Build an optimized compiler.
	$(MAKE) BUILD=release PRINT_PARSE=0 all

install: $(OUTPUT) ## Install the compiler and APL standard library under PREFIX.
	$(INSTALL) -d $(DESTDIR)$(BINDIR) $(DESTDIR)$(CCClibDIR) $(DESTDIR)$(DOCDIR)
	$(INSTALL) -m 0755 $(OUTPUT) $(DESTDIR)$(BINDIR)/aplc
	$(INSTALL) -m 0644 CCClib/*.apl $(DESTDIR)$(CCClibDIR)/
	$(INSTALL) -m 0644 LICENSE $(DESTDIR)$(DOCDIR)/

package: ## Build a relocatable binary tarball with the standard library.
	$(MAKE) BUILD=release PRINT_PARSE=0 -B all
	$(RM) -r builds/package/apl-$(VERSION)
	$(INSTALL) -d builds/package/apl-$(VERSION)/bin builds/package/apl-$(VERSION)/share/apl/include builds/package/apl-$(VERSION)/share/doc/apl
	$(INSTALL) -m 0755 $(OUTPUT) builds/package/apl-$(VERSION)/bin/aplc
	$(INSTALL) -m 0644 CCClib/*.apl builds/package/apl-$(VERSION)/share/apl/include/
	$(INSTALL) -m 0644 LICENSE builds/package/apl-$(VERSION)/share/doc/apl/
	tar -C builds/package -czf builds/apl-$(VERSION)-$(PLATFORM).tar.gz apl-$(VERSION)

run: $(OUTPUT) ## Compile INPUT with the built compiler.
	$(OUTPUT) $(RUN_ARGS) $(INPUT)

test: ## Run integration tests, e.g. make test MODULE=asm.
	cd tests && $(PYTHON) integrated_testing.py --run --module $(MODULE) --test-code $(TEST_CODE) --compiler $(CC) --output-dir bin --base ../

unit-test: ## Run module tests, e.g. make unit-test UTEST=code_utesting/ast.
	cd tests && $(PYTHON) module_testing.py --path $(UTEST) --compiler $(CC) --output-dir bin --base ../

rewrite-test: ## Rewrite OUTPUT blocks for module tests.
	cd tests && $(PYTHON) module_testing.py --path $(UTEST) --compiler $(CC) --output-dir bin --base ../ --force-rewrite

std-test: ## Run std library tests, e.g. make std-test or make std-test STD_UTEST=std_utesting/list.
	@if [ "$(STD_UTEST)" = "std_utesting" ]; then \
		for dir in tests/std_utesting/*; do \
			if [ -d "$$dir" ]; then \
				name=$$(basename "$$dir"); \
				cd tests && $(PYTHON) std_testing.py --path "std_utesting/$$name" --compiler $(CC) --output-dir bin --base ../ || exit 1; \
				cd ..; \
			fi; \
		done; \
	else \
		cd tests && $(PYTHON) std_testing.py --path $(STD_UTEST) --compiler $(CC) --output-dir bin --base ../; \
	fi

CCClib-test: $(OUTPUT) ## Parse all shipped APL standard library headers.
	$(OUTPUT) --without-compilation tests/CCClib_smoke.apl

clean: ## Remove compiler build outputs.
	$(RM) -r builds

clean-tests: ## Remove test binaries.
	$(RM) -r tests/bin

distclean: clean clean-tests ## Remove all generated build/test outputs.

print-sources:
	@printf "%s\n" $(SOURCES)

print-config:
	@echo "CC=$(CC)"
	@echo "BUILD=$(BUILD)"
	@echo "PLATFORM=$(PLATFORM)"
	@echo "OUTPUT=$(OUTPUT)"
	@echo "PREFIX=$(PREFIX)"
	@echo "CCClibDIR=$(CCClibDIR)"
	@echo "CPPFLAGS=$(CPPFLAGS)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "LDFLAGS=$(LDFLAGS)"
	@echo "LDLIBS=$(LDLIBS)"
	@echo "ENABLE_Z3=$(ENABLE_Z3)"
	@echo "Z3_AVAILABLE=$(Z3_AVAILABLE)"
	@echo "Z3_ENABLED=$(Z3_ENABLED)"
	@echo "Z3_CFLAGS=$(Z3_CFLAGS)"
	@echo "Z3_LDLIBS=$(Z3_LDLIBS)"
	@echo "LOGS=$(LOGS)"
	@echo "INPUT=$(INPUT)"
	@echo "RUN_ARGS=$(RUN_ARGS)"

help:
	@awk 'BEGIN {FS = ":.*## "; printf "Usage: make <target> [VAR=value]\n\nTargets:\n"} /^[a-zA-Z0-9_.-]+:.*## / {printf "  %-14s %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DELETE_ON_ERROR:
.PHONY: all debug release install package run test unit-test rewrite-test std-test CCClib-test clean clean-tests distclean print-sources print-config help
