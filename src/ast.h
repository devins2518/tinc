#ifndef AST_H
#define AST_H

#include "ll.h"
#include "string.h"
#include "token.h"
#include "util.h"
#include "vector.h"

typedef struct {
    enum { function_e, declaration_e } e;
} ast_token;
DECLARE_VECTOR(ast_token)

string print_ast_token(ast_token *a);

#endif
