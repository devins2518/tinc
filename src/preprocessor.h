#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "scanner.h"

DECLARE_HASHMAP(ident, string)

typedef struct {
    hash_map_ident_string defines;
    scanner scanner;
    vector_pp_token tokens;
    bool start_of_line;
    int ifs;
} preprocessor;

preprocessor preprocessor_new(string *src);
vector_pp_token preprocessor_run(preprocessor *pp);
void preprocessor_free(preprocessor pp);

#endif
