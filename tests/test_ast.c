#include <stdio.h>
#include <token.h>
#include <unistd.h>
#include <stdlib.h>
#include <markup.h>
#include <syntax.h>
#include <apl_parser.h>
#include "ast_helper.h"

int main(int argc, char* argv[]) {
    printf("RUNNING TEST %s...\n", argv[0]);
    mm_init();
    
    int fd = open(argv[1], O_RDONLY);
    char data[2048] = { 0 };
    pread(fd, data, 2048, 0);
    printf("Source data: %s\n\n", data);

    token_t* tkn = TKN_tokenize(fd);
    if (!tkn) {
        fprintf(stderr, "ERROR! tkn==NULL!\n");
        return 1;
    }

    MRKP_mnemonics(tkn);
    MRKP_variables(tkn);

    arrmem_ctx_t actx = { .h = NULL };
    varmem_ctx_t vctx = { .h = NULL, .offset = 0 };
    syntax_ctx_t sctx = { .arrs = &actx, .vars = &vctx };
    parser_t p = {
        .block      = apl_parse_block,
        .switchstmt = apl_parse_switch,
        .condop     = apl_parse_condop,
        .arraydecl  = apl_parse_array_declaration,
        .vardecl    = apl_parse_variable_declaration,
        .extrn      = apl_parse_extern,
        .rexit      = apl_parse_rexit,
        .funccall   = apl_parse_funccall,
        .function   = apl_parse_function,
        .import     = apl_parse_import,
        .expr       = apl_parse_expression,
        .scope      = apl_parse_scope,
        .start      = apl_parse_start,
        .syscall    = apl_parse_syscall,
        .asmer      = apl_parse_asm
    };

    STX_create(tkn, &sctx, &p);
    print_ast(sctx.r, 0);

    AST_unload(sctx.r);
    TKN_unload(tkn);
    close(fd);
    return 0;
}

