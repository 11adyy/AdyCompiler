#include <ast/astgen/astgen.h>

DEFINE_PARSER(apl_parse_place, {
    ast_node_t* base = AST_create_node(CURRENT_TOKEN);
    PARSER_ASSERT(!base, NULL, "Can't create a base for a palce!");
    PARSER_ASSERT(!consume_token(it, OPEN_BRACKET_TOKEN), base, "Expected the 'OPEN_BRACKET_TOKEN'!");
    
    forward_token(it, 1);
    ast_node_t* buffer = apl_parse_expression(it, ctx, smt, 1);
    PARSER_ASSERT(!buffer, base, "Error during the sizeof body parse! place(<exp>, <type>)!");
    AST_add_node(base, buffer);

    forward_token(it, 1);
    ast_node_t* type = apl_parse_expression(it, ctx, smt, 1);
    PARSER_ASSERT(!type, base, "Error during the sizeof body parse! place(<exp>, <type>)!");
    AST_add_node(base, type);
    type->sinfo.t_id = type_lookup(type->t, ctx, smt);

    forward_token(it, 1);
    return base;
})