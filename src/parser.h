#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

ast_token *generate_ast(vector_pp_token *tokens);

#endif
