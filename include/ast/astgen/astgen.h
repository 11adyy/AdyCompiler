#ifndef APL_PARSER_H_
#define APL_PARSER_H_

#include <std/str.h>
#include <std/stack.h>
#include <prep/dict.h>
#include <prep/token.h>
#include <prep/token_types.h>
#include <prep/dict.h>
#include <symtab/symtab.h>
#include <ast/ast.h>
#include <ast/astgen.h>

#define SAVE_TOKEN_POINT    void* __dump_tkn = it->curr
#define RESTORE_TOKEN_POINT it->curr = __dump_tkn

/* Support macro for getting the current token from the iterator. */
#define CURRENT_TOKEN ((token_t*)list_iter_current(it))

/*
Search for a variable (presented in the node) on the symtable.
Params:
    - `node` - Considering node.
    - `ctx` - AST context.
    - `smt` - Symtable.

Return 1 if succeed.
*/
int var_lookup(ast_node_t* node, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse `.apl` block with input tokens. Should be invoked on new block.
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
ast_node_t* apl_parse_block(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt, token_type_t ex);

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
ast_node_t* apl_parse_asm(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_switch(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_if(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_while(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_array_declaration(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_variable_declaration(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_extern(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_exit(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_return(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl function call. Should be invoked on funccall token.
Snippet:
```apl
: function name :( : statement : );
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_funccall(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_function(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl import block. Should be invoked on import token.
Snippet:
```apl
from : file : import : name :;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_import(list_iter_t* it, sym_table_t* smt);

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

Returns an ast node.
*/
ast_node_t* apl_parse_expression(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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

Returns an ast node.
*/
ast_node_t* apl_parse_scope(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_start(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
ast_node_t* apl_parse_syscall(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl breakpoint block. Should be invoked on a breakpoint token.
Snippet:
```apl
lis;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_breakpoint(list_iter_t* it);

/*
Parse .apl break block. Should be invoked on a break token.
Snippet:
```apl
break;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_break(list_iter_t* it);

#endif