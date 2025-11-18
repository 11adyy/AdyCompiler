#ifndef APL_PARSER_H_
#define APL_PARSER_H_

#include <std/str.h>
#include <std/stack.h>
#include <prep/token.h>
#include <prep/token_types.h>
#include <prep/dict.h>
#include <symtab/symtab.h>
#include <ast/ast.h>
#include <ast/astgen.h>

int var_lookup(ast_node_t* node, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl block with input tokens. Should be invoked on new block.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.
- ex - Exit token type, that will end block parsing.

Return ast node.
*/
ast_node_t* apl_parse_block(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt, token_type_t ex);

/*
Parse .apl asm block with input tokens. Should be invoked on new ASM token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_asm(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl switch block with input tokens. Should be invoked on switch token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_switch(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl if block with input tokens. Should be invoked on if token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_condop(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl declaration array block. Should be invoked on array declaration block.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_array_declaration(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl declaration variable block. Should be invoked on variable declaration block.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_variable_declaration(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl extern block. Should be invoked on extern block.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_extern(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl exit and return block. Should be invoked on return or exit token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_rexit(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl function call. Should be invoked on funccall token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_funccall(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl function with body and params. Should be invoked on function entry body.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_function(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl import block. Should be invoked on import token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_import(list_iter_t* it, sym_table_t* smt);

/*
Parse .apl expression block (function, arithmetics, etc.). Can be invoked on any token type.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_expression(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl scope block. Should be invoked on scope token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_scope(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl start block. Should be invoked on start token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_start(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl syscall block. Should be invoked on syscall token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_syscall(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl breakpoint block. Should be invoked on breakpoint token.
Params:
- it - Current iterator on token list.
- ctx - AST ctx.
- smt - Symtable pointer.

Return ast node.
*/
ast_node_t* apl_parse_breakpoint(list_iter_t* it);

#endif