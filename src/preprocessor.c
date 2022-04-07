#include "preprocessor.h"

#include <assert.h>
#include <stdio.h>

preprocessor preprocessor_new(string *src) {
    preprocessor p;
    p.defines = hash_map_ident_string_new();
    p.scanner = scanner_new(src);
    p.tokens = vector_pp_token_new();
    p.start_of_line = true;
    p.ifs = 0;
    return p;
}

bool preprocessor_if(preprocessor *pp, ident *ident);
bool preprocessor_ifdef(preprocessor *pp, ident ident) {
    return hash_map_ident_string_lookup(&pp->defines, &ident) != NULL;
}
bool preprocessor_ifndef(preprocessor *pp, ident ident) {
    return hash_map_ident_string_lookup(&pp->defines, &ident) == NULL;
}
void preprocessor_include(preprocessor *pp, char *path, char *src);
void preprocessor_define(preprocessor *pp, ident ident, int start, int len) {
    string s = string_new(&pp->scanner.src->inner[start], len);
    hash_map_ident_string_insert(&pp->defines, ident, s);
}
void preprocessor_undef(preprocessor *pp, ident *ident) {
    hash_map_ident_string_delete(&pp->defines, ident);
}

bool preprocessor_is_macro(preprocessor *pp, pp_token *token) {
    entry_ident_string *s;
    s = hash_map_ident_string_lookup(&pp->defines, &token->p.ident_p);
    if (s != NULL) {
        string_replace_string(pp->scanner.src, &s->val, token->start, token->end - token->start);
        pp->scanner.index = token->start;
        pp->scanner.curr = token->start;
        return true;
    }
    return false;
}

typedef enum {
    to_elif_else, /* #if/elif false */
    to_endif      /* #if true/elif true/else */
} skip_info;
void preprocessor_skip(preprocessor *pp, skip_info i) {
    int ifs_seen = 0;
    pp_token t;
    while (pp->scanner.index < pp->scanner.src->len) {
        if (pp->scanner.src->inner[pp->scanner.index++] == '#') {
            t = scanner_next(&pp->scanner);
            assert(t.e == ident_e);
            if (string_eq_char_star(&t.p.ident_p, "if") ||
                string_eq_char_star(&t.p.ident_p, "ifdef") ||
                string_eq_char_star(&t.p.ident_p, "ifndef")) {
                ifs_seen++;
            } else {
                if (string_eq_char_star(&t.p.ident_p, "endif") && ifs_seen == 0) {
                    break;
                } else if (string_eq_char_star(&t.p.ident_p, "else") ||
                           string_eq_char_star(&t.p.ident_p, "elif")) {
                    if (ifs_seen != 0)
                        continue;
                    if (i == to_elif_else)
                        break;
                }
            }
        }
    }
    pp->scanner.curr = pp->scanner.index;
}

vector_pp_token preprocessor_run(string *src) {
    preprocessor pp = preprocessor_new(src);
    while (true) {
        pp_token t;
        t = scanner_next(&pp.scanner);
        switch (t.e) {
        case punct_e: {
            pp_token directive;
            if (t.p.punct_p == hash_punct) {
                directive = scanner_next(&pp.scanner);
                assert(directive.e == ident_e);
                if (string_eq_char_star(&directive.p.ident_p, "if")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "ifdef")) {
                    bool present;
                    pp_token t = scanner_skip_ws(&pp.scanner);
                    assert(t.e == ident_e);
                    present = preprocessor_ifdef(&pp, t.p.ident_p);
                    if (present) {
                        pp.ifs++;
                    } else {
                        preprocessor_skip(&pp, to_elif_else);
                    }
                    break;
                } else if (string_eq_char_star(&directive.p.ident_p, "ifndef")) {
                    bool present;
                    pp_token t;
                    t = scanner_skip_ws(&pp.scanner);
                    assert(t.e == ident_e);
                    present = preprocessor_ifdef(&pp, t.p.ident_p);
                    if (present) {
                        preprocessor_skip(&pp, to_elif_else);
                    } else {
                        pp.ifs++;
                    }
                    break;
                } else if (string_eq_char_star(&directive.p.ident_p, "elif")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "else")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "endif")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "include")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "define")) {
                    pp_token t = scanner_skip_ws(&pp.scanner);
                    assert(t.e == ident_e);
                    while (pp.scanner.src->inner[pp.scanner.index++] != '\n') {
                        preprocessor_define(&pp, t.p.ident_p, pp.scanner.curr,
                                            pp.scanner.index - pp.scanner.curr);
                    }
                } else if (string_eq_char_star(&directive.p.ident_p, "undef")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "line")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "error")) {
                } else if (string_eq_char_star(&directive.p.ident_p, "pragma")) {
                } else {
                    vector_pp_token_add(&pp.tokens, pp_error(directive.start, directive.end,
                                                             "Unknown preprocessing directive"));
                }
            } else {
                goto def;
            }
            break;
        }
        case whitespace_e:
            if (t.p.whitespace_p == eof_ws) {
                goto exit;
            } else if (t.p.whitespace_p == nl_ws) {
                pp.start_of_line = true;
            }
            break;
        case ident_e:
            if (preprocessor_is_macro(&pp, &t))
                continue;
            pp_try_keyword(&t);
            goto def;
        default:
        def:
            pp.start_of_line = false;
            vector_pp_token_add(&pp.tokens, t);
            break;
        }
    }
exit:
    return pp.tokens;
}
