/* Main parser logic. This parser bases on the BNF that is provided below:
identifier       = "IDENTIFIER" ;
integer_literal  = "INTEGER_LITERAL" ;
string_literal   = "STRING_LITERAL" ;
char_literal     = "CHAR_LITERAL" ;
comment          = "COMMENT" ;
eol              = "EOL" ;

program        = "{" , { top_item } , "}" ;

top_item       = start_function
               | import_op
               | extern_op
               | pp_directive
               | storage_opt , top_decl ;

import_op      = "from" , string_literal , "import" , [ import_list ] ;
import_list    = import_item , { "," , import_item } ;
import_item    = identifier ;

extern_op          = "extern" , ( function_prototype | var_prototype ) ;
var_prototype      = type , identifier ;
function_prototype = "exfunc" , identifier ;

storage_opt    = [ "glob" | "ro" ] ;

top_decl       = var_decl | function_def | function_proto ;

function_def   = "function" , identifier , "(" , [ param_list ] , ")" , [ "=>" , type ] , block ;

function_proto = "function" , identifier , "(" , [ param_list ] , ")" , [ "=>" , type ] , ";" ;

start_function = "start" , "(" , [ param_list ] , ")" , block ;

param_list     = param , { "," , param } ;
param          = type , identifier , [ "=" , expression ] ;

block          = "{" , { statement } , "}" ;

statement      = pp_directive
               | var_decl
               | arr_decl
               | if_statement
               | loop_statement
               | while_statement
               | switch_statement
               | return_statement
               | exit_statement
               | break_statement
               | lis_statement
               | syscall_statement
               | asm_block
               | comment
               | block
               | expression_statement ;

pp_directive   = "#" , pp_body , pp_end ;

pp_end         = eol | ";" ;

pp_body        = pp_line
               | pp_include
               | pp_define
               | pp_undef
               | pp_ifdef
               | pp_ifndef
               | pp_endif ;

pp_line        = "line" , integer_literal , [ string_literal ] ;
pp_include     = "include" , string_literal ;
pp_define      = "define" , identifier , { pp_token } ;
pp_undef       = "undef" , identifier ;
pp_ifdef       = "ifdef" , identifier ;
pp_ifndef      = "ifndef" , identifier ;
pp_endif       = "endif" ;

pp_token       = identifier
               | literal

               | keyword
               | punct_no_semi
               | operator ;

keyword        = "from" | "import" | "extern" | "exfunc" | "glob" | "ro"
               | "function" | "start"
               | "arr"
               | "if" | "else" | "loop" | "while"
               | "switch" | "case" | "default"
               | "return" | "exit" | "break" | "lis"
               | "syscall" | "asm"
               | "not" | "ref" | "dref" | "as"
               | "ptr" | "str"
               | "f64" | "i64" | "u64" | "f32" | "i32" | "u32" | "i16" | "u16" | "i8" | "u8"
               | "line" | "include" | "define" | "undef" | "ifdef" | "ifndef" | "endif" ;

punct_no_semi  = "{" | "}" | "(" | ")" | "[" | "]" | "," ;

operator       = "=>"
               | "==" | "!=" | "<=" | ">=" | "<<" | ">>"
               | "||" | "&&"
               | "+=" | "-=" | "*=" | "/=" | "%=" | "|=" | "^=" | "&=" | "||=" | "&&="
               | "="  | "<"  | ">"  | "+"  | "-"  | "*"  | "/"  | "%"  | "|"  | "^"  | "&" ;

var_decl       = type , identifier , [ "=" , expression ] , ";" ;

arr_decl       = "arr" , identifier , "[" , integer_literal , "," , type , "]" ,
                 [ "=" , ( expression | arr_value ) ] , ";" ;

arr_value      = "{" , [ arr_value_list ] , "}" ;
arr_value_list = expression , { "," , expression } ;

if_statement     = "if" , expression , ";" , block , [ "else" , block ] ;
loop_statement   = "loop" , block ;
while_statement  = "while" , expression , ";" , block ;

(* switch expression; { case literal; block } *)
switch_statement = "switch" , expression , ";" ,
                   "{" , { case_block } , [ default_block ] , "}" ;

case_block       = "case" , literal , ";" , block ;
default_block    = "default" , [ ";" ] , block ;

return_statement = "return" , [ expression ] , ";" ;
exit_statement   = "exit" , expression , ";" ;
break_statement  = "break" , ";" ;
lis_statement    = "lis" , [ string_literal ] , ";" ;

expression_statement = expression , ";" ;

syscall_statement = "syscall" , "(" , [ expression_list ] , ")" , ";" ;
expression_list   = expression , { "," , expression } ;

asm_block      = "asm" , "(" , [ asm_args ] , ")" , "{" , { asm_line } , "}" ;
asm_args       = asm_arg , { "," , asm_arg } ;
asm_arg        = identifier | literal ;
asm_line       = string_literal , [ "," ] ;

expression     = assign ;

assign         = logical_or , [ assign_op , assign ] ;
assign_op      = "=" | "+=" | "-=" | "*=" | "/=" | "%=" | "|=" | "^=" | "&=" | "||=" | "&&=" ;

logical_or     = logical_and , { "||" , logical_and } ;
logical_and    = bit_or      , { "&&" , bit_or } ;

bit_or         = bit_xor     , { "|"  , bit_xor } ;
bit_xor        = bit_and     , { "^"  , bit_and } ;
bit_and        = equality    , { "&"  , equality } ;

equality       = relational  , { ("==" | "!=") , relational } ;
relational     = shift       , { ("<" | "<=" | ">" | ">=") , shift } ;
shift          = add         , { ("<<" | ">>") , add } ;
add            = mul         , { ("+" | "-") , mul } ;
mul            = unary       , { ("*" | "/" | "%") , unary } ;

unary          = unary_op , unary
               | postfix ;

unary_op       = "not" | "+" | "-" | ref_op | dref_op ;

ref_op         = "ref" ;
dref_op        = "dref" ;

postfix        = primary , { postfix_op } ;
postfix_op     = "(" , [ arg_list ] , ")"
               | "[" , expression , { "," , expression } , "]"
               | "as" , type ;

primary        = literal
               | identifier
               | "(" , expression , ")" ;

arg_list       = expression , { "," , expression } ;

type = "f64" | "i64" | "u64" | "f32" | "i32" | "u32" | "i16" | "u16" | "i8" | "u8"
     | "str"
     | "arr" , "[" , integer_literal , "," , type , "]"
     | "ptr" , type ;

literal         = integer_literal | string_literal | char_literal ;
*/

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
#define CURRENT_TOKEN      ((token_t*)list_iter_current(it))
#define CREATE_SCOPE_TOKEN TKN_create_token(SCOPE_TOKEN, NULL, &CURRENT_TOKEN->finfo)
// #define CONSUME_TOKEN(it, expected) \
//     CURRENT_TOKEN ? (CURRENT_TOKEN->t_type == expected ? forward_token(it, 1) : 0) : 0

#define PARSE_ERROR(msg, ...) \
    fprintf( \
        stderr,                                                     \
        "[%s:%li:%li] " msg "\n",                                   \
        CURRENT_TOKEN ? CURRENT_TOKEN->finfo.file->body : "(null)", \
        CURRENT_TOKEN ? CURRENT_TOKEN->finfo.line : 0,              \
        CURRENT_TOKEN ? CURRENT_TOKEN->finfo.column : 0,            \
        ##__VA_ARGS__                                               \
    )

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
ast_node_t* apl_parse_loop(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

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
    - `na` - No assign.
             Note: By default (0), this function parses an entire 
                   expression with a assign symbol. That means, that
                   expressions such as `a = b`, `a + b = a + b` will
                   be full parsed.
                   If you want to parse only the left part (before assign),
                   set this flag to 1.

Returns an ast node.
*/
ast_node_t* apl_parse_expression(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt, int na);

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
lis <msg>;
```

Params:
    - `it` - Current iterator on token list.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_breakpoint(list_iter_t* it, sym_table_t* smt);

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
ast_node_t* apl_parse_break(list_iter_t* it);

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
ast_node_t* apl_parse_conv(list_iter_t* it);

/*
Parse .apl 'ref' command. Should be invoked on a 'ref' token.
Snippet:
```apl
i32 b = ref variable;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_ref(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl 'dref' command. Should be invoked on a 'dref' token.
Snippet:
```apl
i32 b = dref variable;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_dref(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

/*
Parse .apl 'neg' command. Should be invoked on a 'neg' token.
Snippet:
```apl
i32 b = neg variable;
```

Params:
    - `it` - Current iterator on token list.
    - `ctx` - AST ctx.
    - `smt` - Symtable pointer.

Returns an ast node.
*/
ast_node_t* apl_parse_neg(list_iter_t* it, ast_ctx_t* ctx, sym_table_t* smt);

#endif