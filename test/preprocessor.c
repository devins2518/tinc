#include "../src/preprocessor.h"
#include "../src/string.h"
#include <assert.h>

const char *SRC = "\
#define HELLO 3\n\
int main() {\n\
    /* */\n\
    int i = 0;\n\
    int k = HELLO;\n\
    char *c = \"hi\";\n\
    float f = 0.3;\n\
    return 0;\n\
}";

void init_expected_tokens(vector_pp_token *v);

int main() {
    vector_pp_token tokens;
    vector_pp_token tokens_expect = vector_pp_token_new();
    string src = string_new_raw(SRC);
    unsigned int i;
    init_expected_tokens(&tokens_expect);
    tokens = preprocessor_run(&src);
    for (i = 0; i < tokens.len; i++) {
        assert(pp_token_eq(&tokens.inner[i], &tokens_expect.inner[i]));
    }
    return 0;
}

void init_expected_tokens(vector_pp_token *v) {
    pp_token t;
    t.e = keyword_e;
    t.p.keyword_p = int_kw;
    t.start = 16;
    t.end = 18;
    vector_pp_token_add(v, t);
    vector_pp_token_add(v, pp_ident(20, 23, string_new_raw("main")));
    vector_pp_token_add(v, pp_multi(24, 24, lparen_multi));
    vector_pp_token_add(v, pp_multi(25, 25, rparen_multi));
    vector_pp_token_add(v, pp_punct(27, 27, lbrace_punct));
    t.start = 43;
    t.end = 45;
    vector_pp_token_add(v, t);
    vector_pp_token_add(v, pp_ident(47, 47, string_new_raw("i")));
    vector_pp_token_add(v, pp_multi(49, 49, eq_multi));
    vector_pp_token_add(v, pp_pp_number(51, 51, string_new_raw("0")));
    vector_pp_token_add(v, pp_punct(52, 52, semicolon_punct));
    t.start = 58;
    t.end = 60;
    vector_pp_token_add(v, t);
    vector_pp_token_add(v, pp_ident(62, 62, string_new_raw("k")));
    vector_pp_token_add(v, pp_multi(64, 64, eq_multi));
    vector_pp_token_add(v, pp_pp_number(67, 67, string_new_raw("3")));
    vector_pp_token_add(v, pp_punct(68, 68, semicolon_punct));
    t.start = 74;
    t.end = 77;
    t.p.keyword_p = char_kw;
    vector_pp_token_add(v, t);
    vector_pp_token_add(v, pp_multi(80, 80, star_multi));
    vector_pp_token_add(v, pp_ident(81, 81, string_new_raw("c")));
    vector_pp_token_add(v, pp_multi(82, 82, eq_multi));
    vector_pp_token_add(v, pp_string_lit(84, 87, string_new_raw("\"hi\""), false));
    vector_pp_token_add(v, pp_punct(88, 88, semicolon_punct));
    t.start = 94;
    t.end = 98;
    t.p.keyword_p = float_kw;
    vector_pp_token_add(v, t);
    vector_pp_token_add(v, pp_ident(100, 100, string_new_raw("f")));
    vector_pp_token_add(v, pp_multi(102, 102, eq_multi));
    vector_pp_token_add(v, pp_pp_number(104, 106, string_new_raw("0.3")));
    vector_pp_token_add(v, pp_punct(107, 107, semicolon_punct));
    t.start = 113;
    t.end = 118;
    t.p.keyword_p = return_kw;
    vector_pp_token_add(v, t);
    vector_pp_token_add(v, pp_pp_number(120, 120, string_new_raw("0")));
    vector_pp_token_add(v, pp_punct(121, 121, semicolon_punct));
    vector_pp_token_add(v, pp_punct(123, 123, rbrace_punct));
}
