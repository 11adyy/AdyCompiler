#include <stdio.h>
#include <prep/token.h>
#include <unistd.h>
#include <stdlib.h>
#include <ast/syntax.h>
#include <prep/markup.h>
#include <sem/semantic.h>
#include <ast/parsers/apl_parser.h>
#include "ast_helper.h"

int main(int argc, char* argv[]) {
    printf("RUNNING TEST %s...\n", argv[0]);
    mm_init();
    
    int fd = open(argv[1], O_RDONLY);
    char data[512] = { 0 };
    pread(fd, data, 512, 0);
    printf("Source data: %s\n", data);

    token_t* tkn = TKN_tokenize(fd);
    if (!tkn) {
        fprintf(stderr, "ERROR! tkn==NULL!\n");
        return 1;
    }

    MRKP_mnemonics(tkn);
    MRKP_variables(tkn);

    arrtab_ctx_t actx  = { .h = NULL };
    vartab_ctx_t vctx  = { .h = NULL, .offset = 0 };
    functab_ctx_t fctx = { .h = NULL };
    syntax_ctx_t sctx  = { 
        .symtb = {
            .arrs  = &actx,
            .vars  = &vctx,
            .funcs = &fctx
        }
    };

    parser_t p = {
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
    };

    STX_create(tkn, &sctx, &p);
    print_ast(sctx.r, 0);

    SMT_check(sctx.r, &sctx.symtb);

    AST_unload(sctx.r);
    TKN_unload(tkn);
    close(fd);
    return 0;
}

