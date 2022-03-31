#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "generic.h"
#include "scanner.h"

typedef struct {
    hash_map_ident_char_star defines;
    scanner scanner;
} preprocessor;

vector_pp_token preprocessor_run(string *src);

#endif
