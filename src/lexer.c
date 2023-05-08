#include "lexer.h"
#include "stdlib.h"
#include "token.h"
#include <stdio.h>

lexer lexer_new(vector_pp_token *tokens) {
    lexer l;
    l.pp_tokens = tokens;
    l.pp_idx = 0;
    l.ast_tokens = ll_ast_token_new();
    return l;
}
