#include "preprocessor.h"

#include <assert.h>
#include <stdio.h>

preprocessor preprocessor_new(string *src) {
    preprocessor p;
    p.defines = hash_map_ident_char_star_new();
    p.scanner = scanner_new(src);
    p.tokens = vector_pp_token_new();
    p.start_of_line = true;
    return p;
}

bool preprocessor_if(preprocessor *p, ident *ident);
bool preprocessor_ifdef(preprocessor *p, ident ident) {
    return hash_map_ident_char_star_lookup(&p->defines, &ident) != NULL;
}
bool preprocessor_ifndef(preprocessor *p, ident ident) {
    return hash_map_ident_char_star_lookup(&p->defines, &ident) == NULL;
}
bool preprocessor_include(preprocessor *p, char *path, char *src);
void preprocessor_define(preprocessor *p, ident ident, char *definition) {
    hash_map_ident_char_star_insert(&p->defines, ident, definition);
}
void preprocessor_undef(preprocessor *p, ident *ident) {
    hash_map_ident_char_star_delete(&p->defines, ident);
}

vector_pp_token preprocessor_run(string *src) {
    preprocessor pp = preprocessor_new(src);
    while (true) {
        pp_token t;
        t = scanner_next(&pp.scanner);
        switch (t.e) {
        case whitespace_e:
            if (t.p.whitespace_p == eof_ws) {
                goto exit;
            } else if (t.p.whitespace_p == nl_ws) {
                pp.start_of_line = true;
            }
            break;
        default:
            pp.start_of_line = false;
            vector_pp_token_add(&pp.tokens, t);
            break;
        }
    }
exit:
    return pp.tokens;
}
