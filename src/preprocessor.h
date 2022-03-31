#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "generic.h"
#include "scanner.h"

typedef struct {
    hash_map_ident_char_star defines;
    scanner scanner;
    vector_pp_token tokens;
    bool start_of_line;
} preprocessor;

vector_pp_token preprocessor_run(string *src);

#endif
