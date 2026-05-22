#ifndef APL_PARSER_H_
#define APL_PARSER_H_

#include <config.h>
#include <std/str.h>
#include <std/set.h>
#include <std/stack.h>
#include <prep/dict.h>
#include <prep/token.h>
#include <prep/token_types.h>
#include <prep/dict.h>
#include <symtab/symtab.h>
#include <ast/ast.h>
#include <ast/astgen.h>
#include <ast/astgen/annot.h>

#define SAVE_TOKEN_POINT    void* __dump_tkn = it->curr;
#define RESTORE_TOKEN_POINT it->curr = __dump_tkn;

/* Support macro for getting the current token from the iterator. */
#define CURRENT_TOKEN       ((token_t*)list_iter_current(it))
#define CREATE_SCOPE_TOKEN  TKN_create_token(SCOPE_TOKEN, NULL, &CURRENT_TOKEN->finfo)
#define CREATE_INDEX_TOKEN  TKN_create_token(INDEXATION_TOKEN, NULL, &CURRENT_TOKEN->finfo)
#define CREATE_CALL_TOKEN   TKN_create_token(CALLING_TOKEN, NULL, &CURRENT_TOKEN->finfo)
#define CREATE_LAMBDA_TOKEN TKN_create_token(LAMBDA_FUNCTION_TOKEN, NULL, &CURRENT_TOKEN->finfo)

#define PARSE_ERROR(msg, ...) \
    fprintf( \
        stderr,                                                                                  \
        "[%s:%li:%li] " msg "\n",                                                                \
        (CURRENT_TOKEN && CURRENT_TOKEN->finfo.file) ? CURRENT_TOKEN->finfo.file->body : "base", \
        CURRENT_TOKEN ? CURRENT_TOKEN->finfo.line : 0,                                           \
        CURRENT_TOKEN ? CURRENT_TOKEN->finfo.column : 0,                                         \
        ##__VA_ARGS__                                                                            \
    )

/*
Pop all avaliable annotations from the current stack and link them to a node.
Params:
    - `ctx` - AST context (ast_ctx_t).
    - `nd` - AST node (ast_node_t).
*/
#define DUMP_ANNOTATION_TO_NODE(ctx, nd)                                                   \
    annotation_t* annot;                                                                   \
    while (ctx->annots.top > ctx->an_off - 1 && stack_pop(&ctx->annots, (void**)&annot)) { \
        list_add(&nd->annots, annot);                                                      \
    }

/*
Resolve type ID by its name and scope id. Will lookup the type in the current 
scope ID from the context.
Params:
    - `t` - Token which represents the type.
    - `ctx` - AST context.
    - `smt` - Symtable.

Returns NO_SYMBOL_ID if it isn't a registered type or id from the table.
*/
symbol_id_t type_lookup(token_t* t, ast_ctx_t* ctx, sym_table_t* smt);
#define EXTRACT_TYPE_TYPE(id, smt) \
    TPTB_get_type_type_id(id, &smt->t) == TYPE_GENERICS ? GENERIC_TYPE_TOKEN : CUSTOM_TYPE_TOKEN

/*
Search for a variable (presented in the node) on the symtable.
Params:
    - `node` - Considering node.
    - `ctx` - AST context.
    - `smt` - Symtable.

Returns 1 on success.
*/
int var_lookup(ast_node_t* node, ast_ctx_t* ctx, sym_table_t* smt);

/*
Reserve current annotations for a node.
Note: Will mark the lower level for annotation which can't be used further.
Note 2: Make sure that you're calling the 'annotation_unreserve' somewhere below.
Params:
    - `ctx` - AST context.

Returns the value for the 'annotation_unreserve' function.
*/
int annotation_reserve(ast_ctx_t* ctx);

/*
Reverse the 'annotation_reserve' effect. Will restore the lower level for annotations,
able to dump.
Params:
    - `ctx` - AST context.

Returns 1 if succeeds.
*/
int annotation_unreserve(ast_ctx_t* ctx, int off);

#define PARSER_ARGS     list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt, long carry
#define PARSER_ARGS_USE (void)it; (void)ctx; (void)smt; (void)carry;

/*
Save the target pointer and update it with a new one.
Params:
    - `l` - Action that will be invoked with a new pointer.
    - `n` - A new pointer.
*/
#define PRESERVE_AST_CARRY_ARG(l, n) \
    void* __dumped = ctx->carry.ptr; \
    ctx->carry.ptr = n;              \
    l;                               \
    ctx->carry.ptr = __dumped;       \

/*
Parse `.apl` element with input tokens.
Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_element(PARSER_ARGS);

/*
Parse `.apl` block with input tokens. Should be invoked on new block.
Note: This is the start gramma symbol (see EBNF in the README).
Snippet:
```apl
someting {
    : Block :
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.
    - `ex` - Exit token type, that will end block parsing.

Returns an ast node.
*/
ast_node_t* apl_parse_block(PARSER_ARGS);

/*
Parse .apl asm block with input tokens. Should be invoked on new ASM token.
Snippet:
```apl
asm( : arguments, statements : ) {
    "",
    : ... :
    ""
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_asm(PARSER_ARGS);

/*
Parse .apl switch block with input tokens. Should be invoked on switch token.
Snippet:
```apl
switch : statement : {
    case : value :; {

    }
    default {

    }
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_switch(PARSER_ARGS);

/*
Parse .apl 'if' block with input tokens. Should be invoked on 'if' token.
Snippet:
```apl
if : statement :; {
}
else {
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_if(PARSER_ARGS);

/*
Parse .apl 'while' block with input tokens. Should be invoked on 'while' token.
Snippet:
```apl
while : statement :; {
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_while(PARSER_ARGS);

/*
Parse .apl 'loop' block with input tokens. Should be invoked on 'loop' token.
Snippet:
```apl
loop {
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_loop(PARSER_ARGS);

/*
Parse .apl declaration array block. Should be invoked on array declaration block.
Snippet:
```apl
arr : name :[: type :, : size :] (opt: = : decl :);
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_array_declaration(PARSER_ARGS);

/*
Parse .apl declaration variable block. Should be invoked on variable declaration block.
Snippet:
```apl
: type : : name : (opt: = : decl :);
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_variable_declaration(PARSER_ARGS);

/*
Parse .apl extern block. Should be invoked on extern block.
Snippet:
```apl
extern : type : : name :;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_extern(PARSER_ARGS);

/*
Parse .apl exit block. Should be invoked on a 'exit' token.
Snippet:
```apl
exit : statement :;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_exit(PARSER_ARGS);

/*
Parse .apl return block. Should be invoked on a 'return' token.
Snippet:
```apl
return : statement :;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_return(PARSER_ARGS);

/*
Parse .apl function's arguments. Helper function for funccall handlers.
Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.
    - `args` - Output arguments number.

Returns an ast node.
*/
ast_node_t* apl_parse_call_arguments(PARSER_ARGS);

/*
Helper function for parsing function / start arguments.
Can handle declaration-like arguments and variadic arguments.
Params:
    - `trg` - Target arguments node.
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns 0 if something went wrong, otherwise 1.
*/
int apl_parse_funcdef_args(PARSER_ARGS);

/*
Parse .apl function with body and params. Should be invoked on function entry body.
Snippet:
```apl
function : name :( : type : : name : (opt: = : decl :) ) {
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_function(PARSER_ARGS);

/*
Parse .apl expression block (function, arithmetics, etc.). Can be invoked on any token type.
Snippet:
```apl
: statement : : op : : statement :;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.
    - `na` - No append.
             Note: By default (0), this function parses an entire 
                   expression with a assign symbol. That means, that
                   expressions such as `a = b`, `a + b = a + b` will
                   be full parsed.
                   1) If you want to parse only the left part (before assign),
                   set this flag to 1.
                   2) If you want to parse only the primary - set this flag to 2.

Returns an ast node.
*/
ast_node_t* apl_parse_expression(PARSER_ARGS);

/*
Parse .apl scope element.
Note: Will parse only one element in the separated scope. This means,
      that any declared variable will be allocated in a one-line scope.

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_line_scope(PARSER_ARGS);

/*
Parse .apl scope block. Should be invoked on scope token.
Snippet:
```apl
{
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.
    - `carry` - Increase the scope id? (0 - no).

Returns an ast node.
*/
ast_node_t* apl_parse_scope(PARSER_ARGS);

/*
Parse .apl start block. Should be invoked on start token.
Snippet:
```apl
start( : arguments : ) {
}
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_start(PARSER_ARGS);

/*
Parse .apl syscall block. Should be invoked on syscall token.
Snippet:
```apl
syscall( : arguments : );
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_syscall(PARSER_ARGS);

/*
Parse .apl breakpoint block. Should be invoked on a breakpoint token.
Snippet:
```apl
lis <msg>;
```

Params:
    - `it` - Current iterator on token list.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_breakpoint(PARSER_ARGS);

/*
Parse .apl break block. Should be invoked on a break token.
Snippet:
```apl
break;
```

Params:
    - `it` - Current iterator on token list.

Returns an ast node.
*/
ast_node_t* apl_parse_break(PARSER_ARGS);

/*
Parse .apl cast block. Should be invoked on a 'as' token.
Snippet:
```apl
i32 b = variable as i32;
```

Params:
    - `it` - Current iterator on token list.

Returns an ast node.
*/
ast_node_t* apl_parse_conv(PARSER_ARGS);

// TODO: docs
ast_node_t* apl_parse_unary(PARSER_ARGS);

/*
Parse an annotation and push it onto the stack.
Params:
    - <parser_args>

Always returns NULL.
*/
ast_node_t* apl_parse_annot(PARSER_ARGS);

/*
Parse a lambda structure.
Params:
    - <parser_args>

Returns an AST node.
*/
ast_node_t* apl_parse_lambda(PARSER_ARGS);

/*
Parse the 'sizeof' keyword.
Params:
    - <parser_args>

Returns an AST node.
*/
ast_node_t* apl_parse_sizeof(PARSER_ARGS);

#endif
