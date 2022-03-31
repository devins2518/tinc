#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

IMPL_VECTOR(ast_token)

string ast_token_print(ast_token *a) {
    string s;
    switch (a->e) {
    case function_e:
        s = string_new_raw("function: ");
        break;
    }
    return s;
}
