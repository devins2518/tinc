#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

IMPL_VECTOR(ast_token)

string print_ast_token(ast_token *a) {
    string s;
    switch (a->e) {
    case function_e:
        s = string_new_raw("function");
        break;
    case declaration_e:
        s = string_new_raw("declaration");
        break;
    }
    return s;
}
