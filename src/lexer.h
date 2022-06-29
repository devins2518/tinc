#ifndef LEXER_H
#define LEXER_H

#include "ast.h"
#include "token.h"

translation_unit *generate_ast(vector_pp_token *tokens);

#endif
