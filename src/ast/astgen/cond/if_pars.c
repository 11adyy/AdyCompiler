#include <ast/astgen/astgen.h>

ast_node_t* apl_parse_if(PARSER_ARGS) {
    PARSER_ARGS_USE;
    SAVE_TOKEN_POINT;
    
    ast_node_t* node = AST_create_node(CURRENT_TOKEN);
    if (!node) {
        PARSE_ERROR("Can't create a base for the '%s' statement!", IF_COMMAND);
        RESTORE_TOKEN_POINT;
        return NULL;
    }
    
    stack_top(&ctx->scopes.stack, (void**)&node->sinfo.s_id);
    
    forward_token(it, 1);
    ast_node_t* cond = apl_parse_expression(it, ctx, smt, 1);
    if (!cond) {
        PARSE_ERROR("Error during the condition parsing in the '%s' structure! %s <stmt>", IF_COMMAND, IF_COMMAND);
        AST_unload(node);
        RESTORE_TOKEN_POINT;
        return NULL;
    }

    AST_add_node(node, cond);

    ast_node_t* tbranch = NULL;
    if (!consume_token(it, OPEN_BLOCK_TOKEN)) tbranch = apl_parse_line_scope(it, ctx, smt, carry);
    else tbranch = apl_parse_scope(it, ctx, smt, carry);
    if (!tbranch) {
        PARSE_ERROR("Error during the true branch parsing in the '%s' statement!", IF_COMMAND);
        AST_unload(node);
        RESTORE_TOKEN_POINT;
        return NULL;
    }
    
    AST_add_node(node, tbranch);

    if (CURRENT_TOKEN && CURRENT_TOKEN->t_type == ELSE_TOKEN) {
        ast_node_t* fbranch = NULL;
        forward_token(it, 1);
        switch (CURRENT_TOKEN->t_type) {
            case OPEN_BLOCK_TOKEN: fbranch = apl_parse_scope(it, ctx, smt, carry);      break;
            case IF_TOKEN:         fbranch = apl_parse_if(it, ctx, smt, carry);         break;
            default:               fbranch = apl_parse_line_scope(it, ctx, smt, carry); break;
        }
        
        if (!fbranch) {
            PARSE_ERROR("Error during the false branch parsing in the '%s' statement!", IF_COMMAND);
            AST_unload(node);
            RESTORE_TOKEN_POINT;
            return NULL;
        }
        
        AST_add_node(node, fbranch);
    }
    
    return node;
}
