#include "preprocessor.h"

#include <assert.h>
#include <stdio.h>

preprocessor preprocessor_new() {
    preprocessor p;
    p.defines = hash_map_pp_token_pp_token_new();
    return p;
}

void run_preprocessor(preprocessor *p, vector_pp_token *t) {
    int i;
    vector_pp_token_print(t);
    for (i = 0; i < t->len; i++) {
        if (t->inner[i].e == punct_e && t->inner[i].p.punct_p == hash_punct) {
            string str = t->inner[i + 1].p.ident_p;
            assert(t->inner[i + 1].e == ident_e);
            if (string_eq_char_star(&str, "if")) {
            } else if (string_eq_char_star(&str, "ifdef")) {
            } else if (string_eq_char_star(&str, "ifndef")) {
            } else if (string_eq_char_star(&str, "elif")) {
            } else if (string_eq_char_star(&str, "else")) {
            } else if (string_eq_char_star(&str, "endif")) {
            } else if (string_eq_char_star(&str, "include")) {
            } else if (string_eq_char_star(&str, "define")) {
            } else if (string_eq_char_star(&str, "undef")) {
            } else if (string_eq_char_star(&str, "line")) {
            } else if (string_eq_char_star(&str, "error")) {
            } else if (string_eq_char_star(&str, "pragma")) {
            }
        }
    }
    return;
}
