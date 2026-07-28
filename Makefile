CC 						?= gcc
AR 						?= ar
PYTHON 					?= python3
RM 						?= rm -f
MKDIR_P 				?= mkdir -p
INSTALL 				?= install

PREFIX 					?= /usr/local
DESTDIR 				?=
BINDIR 					?= $(PREFIX)/bin
LIBDIR 					?= $(PREFIX)/lib
DATADIR 				?= $(PREFIX)/share
CCClibDIR 				?= $(DATADIR)/apl/include
APLRUNTIMEDIR 			?= $(LIBDIR)/apl
DOCDIR 					?= $(DATADIR)/doc/apl
VERSION 				?= 3.6_X

BUILD 					?= debug
AVAILABLE_MEMORY 		?= 67108864
LOGS 					?=
PRINT_PARSE 			?= 1
ENABLE_Z3 				?= auto
INPUT 					?= examples/print.apl
UTEST 					?= code_utesting
STD_UTEST 				?= std_utesting
VSCODE_DOCKER_IMAGE 	?= apl-extension
VSCODE_OUTPUT_DIR 		?= $(CURDIR)/vscode/output
DOCS_BACKEND_BUILD_DIR 	?= docs/back/.build
DOCS_BACKEND_PLATFORM 	?= ../$(DOCS_BACKEND_BUILD_DIR)
DOCS_BACKEND_COMPILER 	?= $(DOCS_BACKEND_BUILD_DIR)/aplc
DOCS_BACKEND_OUTPUT 	?= docs/back/apl_docs_backend

UNAME_S ?= $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	RUN_ARGS ?= 				\
		--arch x86_64 			\
		--sys-type macho64 		\
		--asm-format macho64 	\
		--linker clang
else
	RUN_ARGS ?= 				\
		--arch x86_64 			\
		--sys-type linux64 		\
		--asm-format elf64 		\
		--linker gcc 			\
		--linker-no-pie 
endif

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

SOURCES 		:= $(sort $(shell find src std -type f -name '*.c'))
OUTPUT 			= builds/$(PLATFORM)/aplc
CCClib_IMPLS 	:= $(sort $(shell find CCClib -type f -name '*.apl' ! -name '*_h.apl'))
CCClib_BUILDDIR := builds/$(PLATFORM)/CCClib
CCClib_OBJDIR   := $(CCClib_BUILDDIR)/obj
CCClib_OBJS     := $(patsubst CCClib/%.apl,$(CCClib_OBJDIR)/%.o,$(CCClib_IMPLS))
CCClib_ARCHIVE  := $(CCClib_BUILDDIR)/libapl.a

CPPFLAGS 		+= -Iinclude -DALLOC_BUFFER_SIZE=$(AVAILABLE_MEMORY) -DAPL_DEFAULT_INCLUDE_DIR=\"$(CCClibDIR)\" -DAPL_DEFAULT_RUNTIME_LIB=\"$(APLRUNTIMEDIR)/libapl.a\"
CFLAGS   		+= -Wall -Wno-int-conversion
LDFLAGS  		+=
LDLIBS   		+=

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

$(CCClib_OBJDIR)/%.o: CCClib/%.apl $(OUTPUT)
	@$(MKDIR_P) $(dir $@)
	$(OUTPUT) $(RUN_ARGS) -c --output $@ $<

$(CCClib_ARCHIVE): $(CCClib_OBJS)
	@$(MKDIR_P) $(dir $@)
	$(RM) $@
	$(AR) rcs $@ $^

CCClib: $(CCClib_ARCHIVE) ## Build the APL runtime static library.

docs-backend: ## Build the APL HTTP backend for the docs Playground.
	$(MAKE) PLATFORM=$(DOCS_BACKEND_PLATFORM) BUILD=$(BUILD) PRINT_PARSE=$(PRINT_PARSE) ENABLE_Z3=$(ENABLE_Z3) all CCClib
	$(DOCS_BACKEND_COMPILER) $(RUN_ARGS) docs/back/main.apl --output $(DOCS_BACKEND_OUTPUT)

docs-backend-run: docs-backend ## Build and run the APL docs backend on 127.0.0.1:8000.
	./$(DOCS_BACKEND_OUTPUT)

debug: ## Build a debug compiler.
	$(MAKE) BUILD=debug all

release: ## Build an optimized compiler.
	$(MAKE) BUILD=release PRINT_PARSE=0 all

install: $(OUTPUT) $(CCClib_ARCHIVE) ## Install the compiler and APL standard library under PREFIX.
	$(INSTALL) -d $(DESTDIR)$(BINDIR) $(DESTDIR)$(CCClibDIR) $(DESTDIR)$(APLRUNTIMEDIR) $(DESTDIR)$(DOCDIR)
	$(INSTALL) -m 0755 $(OUTPUT) $(DESTDIR)$(BINDIR)/aplc
	$(INSTALL) -m 0644 CCClib/*.apl $(DESTDIR)$(CCClibDIR)/
	$(INSTALL) -m 0644 $(CCClib_ARCHIVE) $(DESTDIR)$(APLRUNTIMEDIR)/libapl.a
	$(INSTALL) -m 0644 LICENSE $(DESTDIR)$(DOCDIR)/

package: ## Build a relocatable binary tarball with the standard library.
	$(MAKE) BUILD=release PRINT_PARSE=0 -B all CCClib
	$(RM) -r builds/package/apl-$(VERSION)
	$(INSTALL) -d builds/package/apl-$(VERSION)/bin builds/package/apl-$(VERSION)/lib/apl builds/package/apl-$(VERSION)/share/apl/include builds/package/apl-$(VERSION)/share/doc/apl
	$(INSTALL) -m 0755 $(OUTPUT) builds/package/apl-$(VERSION)/bin/aplc
	$(INSTALL) -m 0644 CCClib/*.apl builds/package/apl-$(VERSION)/share/apl/include/
	$(INSTALL) -m 0644 $(CCClib_ARCHIVE) builds/package/apl-$(VERSION)/lib/apl/libapl.a
	$(INSTALL) -m 0644 LICENSE builds/package/apl-$(VERSION)/share/doc/apl/
	tar -C builds/package -czf builds/apl-$(VERSION)-$(PLATFORM).tar.gz apl-$(VERSION)

run: $(OUTPUT) ## Compile INPUT with the built compiler.
	$(OUTPUT) $(RUN_ARGS) $(INPUT)

test: unit-test ## Run module tests.

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

vscode-docker-build: ## Build the VS Code extension Docker image.
	docker build -t $(VSCODE_DOCKER_IMAGE) vscode

vscode-docker-package: vscode-docker-build ## Build and package the VS Code extension in Docker.
	docker run --rm -v $(CURDIR)/vscode:/app -v $(VSCODE_OUTPUT_DIR):/output $(VSCODE_DOCKER_IMAGE)

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
	@echo "LIBDIR=$(LIBDIR)"
	@echo "CCClibDIR=$(CCClibDIR)"
	@echo "APLRUNTIMEDIR=$(APLRUNTIMEDIR)"
	@echo "CCClib_IMPLS=$(CCClib_IMPLS)"
	@echo "CCClib_ARCHIVE=$(CCClib_ARCHIVE)"
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
	@echo "VSCODE_DOCKER_IMAGE=$(VSCODE_DOCKER_IMAGE)"
	@echo "VSCODE_OUTPUT_DIR=$(VSCODE_OUTPUT_DIR)"

help:
	@awk 'BEGIN {FS = ":.*## "; printf "Usage: make <target> [VAR=value]\n\nTargets:\n"} /^[a-zA-Z0-9_.-]+:.*## / {printf "  %-14s %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DELETE_ON_ERROR:
.PHONY: all CCClib debug release install package run test unit-test rewrite-test std-test vscode-docker-build vscode-docker-package clean clean-tests distclean print-sources print-config help
