#ifndef AST_H
#define AST_H

#include "ll.h"
#include "string.h"
#include "token.h"
#include "util.h"
#include "vector.h"

typedef struct {
    enum {
        void_e,
        char_e,
        short_e,
        int_e,
        long_e,
        float_e,
        double_e,
        signed_e,
        unsigned_e,
        struct_or_union_e,
        enum_e,
        typedef_e
    } e;
} type;

typedef struct {
    type type;
    ident name;
} parameter;
DECLARE_VECTOR(parameter)

typedef struct {
    type type;
    ident name;
    vector_parameter parameters;
} function;

typedef struct {
    union {
        function function;
    } p;
    enum { function_e } e;
} ast_token;
DECLARE_VECTOR(ast_token)

string ast_token_print(ast_token *a);

#endif
