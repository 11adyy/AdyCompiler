#include <stdio.h>
#include <prep/token.h>
#include <unistd.h>
#include <stdlib.h>
#include <builder.h>
#include <ast/syntax.h>
#include <ast/opt/strdecl.h>
#include <ast/opt/deadscope.h>
#include <ast/opt/offsetopt.h>
#include <ast/parsers/parser.h>
#include <ir/irgen.h>
#include <ir/x86_64_gnu_nasm/x86_64_irgen.h>
#include <asm/asmgen.h>
#include <asm/x86_64_gnu_nasm/x86_64_asmgen.h>
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
            .syscall    = apl_parse_syscall,
            .extrn      = apl_parse_extern,
            .asmer      = apl_parse_asm
        },
        .ir = {
            .funcdef   = IR_generate_funcdef_block,
            .funcret   = IR_generate_return_block,
            .funccall  = IR_generate_funccall_block,
            .function  = IR_generate_function_block,
            .blockgen  = IR_generate_block,
            .elemegen  = IR_generate_elem_block,
            .operand   = IR_generate_operand_block,
            .store     = IR_generate_store_block,
            .ptrload   = IR_generate_ptr_load_block,
            .load      = IR_generate_load_block,
            .assign    = IR_generate_assignment_block,
            .decl      = IR_generate_declaration_block,
            .start     = IR_generate_start_block,
            .exit      = IR_generate_exit_block,
            .syscall   = IR_generate_syscall_block,
            .ifgen     = IR_generate_if_block,
            .whilegen  = IR_generate_while_block,
            .switchgen = IR_generate_switch_block,
            .asmer     = IR_generate_asmblock
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
