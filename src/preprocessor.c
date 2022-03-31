#include "preprocessor.h"

#include <assert.h>
#include <stdio.h>

preprocessor preprocessor_new(string *src) {
    preprocessor p;
    p.defines = hash_map_ident_char_star_new();
    p.scanner = scanner_new(src);
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
            if (t.p.whitespace_p == eof_ws)
                goto exit;
        default:
            printf("%.*s\n", pp_token_print(&t).len, pp_token_print(&t).inner);
            break;
        }
    }
exit:
    printf("unimplemented");
    exit(EXIT_FAILURE);
}
