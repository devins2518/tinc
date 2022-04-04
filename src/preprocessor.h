#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "generic.h"
#include "scanner.h"

typedef struct {
    hash_map_ident_string defines;
    scanner scanner;
    vector_pp_token tokens;
    bool start_of_line;
    int ifs;
} preprocessor;

vector_pp_token preprocessor_run(string *src);

#endif
