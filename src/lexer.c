#include "lexer.h"
#include "stdlib.h"
#include "token.h"
#include <stdio.h>

typedef struct {
    vector_pp_token *pp_tokens;
    ll_ast_token *ast_tokens;
} lexer;

/* jump_statement lex_jump_statement(lexer *l); */

ll_ast_token *generate_ast(vector_pp_token *tokens) {
    lexer l;
    l.pp_tokens = tokens;
    l.ast_tokens = ll_ast_token_new();
    (void)tokens;
    printf("unimplemented");
    exit(EXIT_FAILURE);
    return l.ast_tokens;
}
