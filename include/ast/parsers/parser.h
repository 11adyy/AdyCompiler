#ifndef APL_PARSER_H_
#define APL_PARSER_H_

#include <std/str.h>
#include <prep/token.h>
#include <prep/token_types.h>
#include <std/stack.h>
#include <prep/dict.h>
#include <ast/ast.h>
#include <ast/synctx.h>
#include <symtab/symtab.h>

int var_lookup(ast_node_t* node, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_block.c */
ast_node_t* apl_parse_block(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt, token_type_t ex);

/* apl_asm.c */
ast_node_t* apl_parse_asm(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_cond.c */
ast_node_t* apl_parse_switch(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);
ast_node_t* apl_parse_condop(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_decl.c */
ast_node_t* apl_parse_array_declaration(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);
ast_node_t* apl_parse_variable_declaration(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_func.c */
ast_node_t* apl_parse_extern(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);
ast_node_t* apl_parse_rexit(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);
ast_node_t* apl_parse_funccall(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);
ast_node_t* apl_parse_function(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_import.c */
ast_node_t* apl_parse_import(list_iter_t* it, sym_table_t* smt);

/* apl_op.c */
ast_node_t* apl_parse_expression(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_scope.c */
ast_node_t* apl_parse_scope(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_start.c */
ast_node_t* apl_parse_start(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);

/* apl_syscall.c */
ast_node_t* apl_parse_syscall(list_iter_t* it, syntax_ctx_t* ctx, sym_table_t* smt);
ast_node_t* apl_parse_breakpoint(list_iter_t* it);

#endif