#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

IMPL_LINKED_LIST(ast_token)

string ast_token_to_string(ast_token *a) {
    string s;
    switch (a->e) {
    case function_def_ast_e:
        s = string_new_raw("function: ");
        break;
    }
    return s;
}
