#include "../src/lexer.h"
#include "../src/parser.h"
#include "../src/preprocessor.h"
#include <ctest.h>

extern type_specifier *try_parse_type_specifier(lexer *);

CTEST(AST, TEST_GENERATE_AST) {
    string src = string_new_raw("#define HELLO\n"
                                "int main() {\n"
                                "    int x = 3;\n"
                                "    return x;\n"
                                "}");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    ast_token *ast = generate_ast(&tokens);
    ASSERT_TRUE(ast->e == translation_unit_ast_e);
    ASSERT_TRUE(ast->p.translation_unit->len == 1);
}

#define PARSE_TYPE_SPECIFIER_SIZE 12
CTEST(PARSER, TEST_PARSE_TYPE_SPECIFIER) {
    string src[PARSE_TYPE_SPECIFIER_SIZE] = {
        string_new_raw("void\n"),      string_new_raw("char\n"),
        string_new_raw("short\n"),     string_new_raw("int\n"),
        string_new_raw("long\n"),      string_new_raw("float\n"),
        string_new_raw("double\n"),    string_new_raw("signed\n"),
        string_new_raw("unsigned\n"),  string_new_raw("struct hey;\n"),
        string_new_raw("enum hey;\n"), string_new_raw("hey;\n"),
    };
    string hey = string_new_raw("hey");
    type_specifier expected[PARSE_TYPE_SPECIFIER_SIZE] = {
        {{0}, void_ts_e},
        {{0}, char_ts_e},
        {{0}, short_ts_e},
        {{0}, int_ts_e},
        {{0}, long_ts_e},
        {{0}, float_ts_e},
        {{0}, double_ts_e},
        {{0}, signed_ts_e},
        {{0}, unsigned_ts_e},
        {{.sou_spec = &(struct_or_union_specifier){.fields = 0,
                                                   .ident = &hey,
                                                   &(struct_or_union){struct_sou_e}}},
         .e = struct_or_union_specifier_ts_e},
        {{.enum_spec =
              &(enum_specifier){
                  .ident = &hey,
              }},
         enum_specifier_ts_e},
        {{.type_name = &hey}, type_name_ts_e}};
    for (int i = 0; i < PARSE_TYPE_SPECIFIER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        type_specifier *ts = try_parse_type_specifier(&l);
        ASSERT_TRUE(type_specifier_eq(ts, &expected[i]));
    }
}
