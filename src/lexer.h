#ifndef LEXER_H
#define LEXER_H

#include "ast.h"
#include "token.h"

typedef struct {
    vector_pp_token *pp_tokens;
    uintptr_t pp_idx;
    ll_ast_token *ast_tokens;
} lexer;

lexer lexer_new(vector_pp_token *tokens);

#endif
