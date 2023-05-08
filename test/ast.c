#include "../src/parser.h"
#include "../src/preprocessor.h"
#include <ctest.h>

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
