#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "generic.h"

typedef struct {
    hash_map_pp_token_pp_token defines;
} preprocessor;

preprocessor preprocessor_new();

void run_preprocessor(preprocessor *p, vector_pp_token *t);

#endif
