#include <stdio.h>
#include <prep/token.h>
#include <unistd.h>
#include <stdlib.h>
#include <ast/syntax.h>
#include <ast/opt/strdecl.h>
#include <ast/opt/deadscope.h>
#include <ast/opt/offsetopt.h>
#include <asm/asmgen.h>
#include <builder.h>
#include <ast/parsers/apl_parser.h>
#include <asm/x86_64_gnu_nasm/x86_64_gnu_nasm_asm.h>
#include "ast_helper.h"

int main(int argc, char* argv[]) {
    printf("RUNNING TEST %s...\n", argv[0]);
    mm_init();

    char output[256] = { 0 };
    sprintf(output, "%s.bin", argv[1]);

    builder_ctx_t bctx = { 
        .p = {
            .block      = apl_parse_block,
            .switchstmt = apl_parse_switch,
            .condop     = apl_parse_condop,
            .arraydecl  = apl_parse_array_declaration,
            .vardecl    = apl_parse_variable_declaration,
            .rexit      = apl_parse_rexit,
            .funccall   = apl_parse_funccall,
            .function   = apl_parse_function,
            .import     = apl_parse_import,
            .expr       = apl_parse_expression,
            .scope      = apl_parse_scope,
            .start      = apl_parse_start,
            .syscall    = apl_parse_syscall
        },
        .g = {
            .datagen  = x86_64_generate_data,
            .funcdef  = x86_64_generate_funcdef,
            .funcret  = x86_64_generate_return,
            .funccall = x86_64_generate_funccall,
            .function = x86_64_generate_function,
            .blockgen = x86_64_generate_block,
            .elemegen = x86_64_generate_elem,
            .operand  = x86_64_generate_operand,
            .store    = x86_64_generate_store,
            .ptrload  = x86_64_generate_ptr_load,
            .load     = x86_64_generate_load,
            .assign   = x86_64_generate_assignment,
            .decl     = x86_64_generate_declaration,
            .start    = x86_64_generate_start,
            .exit     = x86_64_generate_exit,
            .syscall  = x86_64_generate_syscall,
            .ifgen    = x86_64_generate_if,
            .whilegen = x86_64_generate_while,
            .switchgen= x86_64_generate_switch
        },
        .prms = {
            .save_asm = 1, .syntax = 1, 
            .asm_compiler = DEFAULT_ASM_COMPILER, 
            .arch         = DEFAULT_ARCH,
            .linker       = DEFAULT_LINKER, 
            .linker_arch  = DEFAULT_LINKER_ARCH, 
            .linker_flags = LINKER_FLAGS, 
            .save_path    = output
        }
    };

    BLD_add_target(argv[1], &bctx);
    BLD_build(&bctx);
    return 0;
}
