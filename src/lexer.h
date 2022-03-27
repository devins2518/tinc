#ifndef LEXER_H
#define LEXER_H

#include "ast.h"
#include "token.h"

vector_ast_token generate_ast(vector_pp_token *tokens);

#endif
