#include "../src/lexer.h"
#include "../src/parser.h"
#include "../src/preprocessor.h"
#include <ctest.h>

extern expression *try_parse_expression(lexer *l);
extern primary_expression *try_parse_primary_expression(lexer *l);
extern postfix_expression *try_parse_postfix_expression(lexer *l);
extern assignment_expression *try_parse_assignment_expression(lexer *l);
extern argument_expression_list *try_parse_argument_expression_list(lexer *l);
extern unary_expression *try_parse_unary_expression(lexer *l);
extern unary_operator try_parse_unary_operator(lexer *l);
extern cast_expression *try_parse_cast_expression(lexer *l);
extern multiplicative_expression *try_parse_multiplicative_expression(lexer *l);
extern additive_expression *try_parse_additive_expression(lexer *l);
extern shift_expression *try_parse_shift_expression(lexer *l);
extern relational_expression *try_parse_relational_expression(lexer *l);
extern equality_expression *try_parse_equality_expression(lexer *l);
extern and_expression *try_parse_and_expression(lexer *l);
extern exclusive_or_expression *try_parse_exclusive_or_expression(lexer *l);
extern inclusive_or_expression *try_parse_inclusive_or_expression(lexer *l);
extern logical_and_expression *try_parse_logical_and_expression(lexer *l);
extern logical_or_expression *try_parse_logical_or_expression(lexer *l);
extern conditional_expression *try_parse_conditional_expression(lexer *l);
extern assignment_operator *try_parse_assignment_operator(lexer *l);
extern constant_expression *try_parse_constant_expression(lexer *l);
extern declaration *try_parse_declaration(lexer *l);
extern declaration_specifier *try_parse_declaration_specifier(lexer *l);
extern declaration_specifiers *try_parse_declaration_specifiers(lexer *l);
extern init_declarator *try_parse_init_declarator(lexer *l);
extern init_declarator_list *try_parse_init_declarator_list(lexer *l);
extern storage_class_specifier *try_parse_storage_class_specifier(lexer *l);
extern type_specifier *try_parse_type_specifier(lexer *l);
extern struct_or_union_specifier *try_parse_struct_or_union_specifier(lexer *l);
extern struct_or_union *try_parse_struct_or_union(lexer *l);
extern struct_declaration *try_parse_struct_declaration(lexer *l);
extern struct_declaration_list *try_parse_struct_declaration_list(lexer *l);
extern _specifier_qualifier *try_parse__specifier_qualifier(lexer *l);
extern struct_declarator_list *try_parse_struct_declarator_list(lexer *l);
extern struct_declarator *try_parse_struct_declarator(lexer *l);
extern enum_specifier *try_parse_enum_specifier(lexer *l);
extern enumerator_list *try_parse_enumerator_list(lexer *l);
extern enumerator *try_parse_enumerator(lexer *l);
extern type_qualifier *try_parse_type_qualifier(lexer *l);
extern type_qualifier_list *try_parse_type_qualifier_list(lexer *l);
extern declarator *try_parse_declarator(lexer *l);
extern direct_declarator *try_parse_direct_declarator(lexer *l);
extern pointer *try_parse_pointer(lexer *l);
extern parameter_type_list *try_parse_parameter_type_list(lexer *l);
extern parameter_list *try_parse_parameter_list(lexer *l);
extern parameter_declaration *try_parse_parameter_declaration(lexer *l);
extern identifier_list *try_parse_identifier_list(lexer *l);
extern abstract_declarator *try_parse_abstract_declarator(lexer *l);
extern direct_abstract_declarator *try_parse_direct_abstract_declarator(lexer *l);
extern initializer *try_parse_initializer(lexer *l);
extern initializer_list *try_parse_initializer_list(lexer *l);
extern statement *try_parse_statement(lexer *l);
extern labeled_statement *try_parse_labeled_statement(lexer *l);
extern compound_statement *try_parse_compound_statement(lexer *l);
extern declaration_list *try_parse_declaration_list(lexer *l);
extern statement_list *try_parse_statement_list(lexer *l);
extern expression_statement *try_parse_expression_statement(lexer *l);
extern selection_statement *try_parse_selection_statement(lexer *l);
extern iteration_statement *try_parse_iteration_statement(lexer *l);
extern jump_statement *try_parse_jump_statement(lexer *l);
extern translation_unit *try_parse_translation_unit(lexer *l);
extern external_declaration *try_parse_external_declaration(lexer *l);
extern function_definition *try_parse_function_definition(lexer *l);

CTEST_SKIP(AST, TEST_GENERATE_AST) {
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

CTEST_SKIP(AST, TEST_PARSE_TRANSLATION_UNIT) {
    string src = string_new_raw("static int p = 0;\n"
                                "int main() {\n"
                                "    int x = 2;\n"
                                "    int y = x + 2;\n"
                                "    int z;\n"
                                "    z = func();\n"
                                "}\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    translation_unit *tu = try_parse_translation_unit(&l);
    translation_unit expected = {0};
    (void)tu;
    (void)expected;
    /* ASSERT_TRUE(translation_unit_eq(tu, &expected)); */
}

CTEST_SKIP(AST, TEST_PARSE_EXPRESSION) {
    string src = string_new_raw("int x = 0, y = 3;\n"
                                "int z = 9;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    expression *e = try_parse_expression(&l);
    expression expected = {0};
    ASSERT_TRUE(expression_eq(e, &expected));
}

#define PARSE_PRIMARY_EXPRESSION_SIZE 4
CTEST_SKIP(AST, TEST_PARSE_PRIMARY_EXPRESSION) {
    string src[PARSE_PRIMARY_EXPRESSION_SIZE] = {
        string_new_raw("hey;\n"),
        string_new_raw("43;\n"),
        string_new_raw("\"hey\";\n"),
        string_new_raw("(1 + 3);\n"),
    };
    primary_expression expected[PARSE_PRIMARY_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_PRIMARY_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        primary_expression *pe = try_parse_primary_expression(&l);
        ASSERT_TRUE(primary_expression_eq(pe, &expected[i]));
    }
}

#define PARSE_POSTFIX_EXPRESSION_SIZE 7
CTEST_SKIP(AST, TEST_PARSE_POSTFIX_EXPRESSION) {
    string src[PARSE_POSTFIX_EXPRESSION_SIZE] = {
        string_new_raw("hey[32]\n"),     string_new_raw("func();\n"),
        string_new_raw("func(a, b);\n"), string_new_raw("hey.there;\n"),
        string_new_raw("hey->there;\n"), string_new_raw("hey++;\n"),
        string_new_raw("hey--;\n"),
    };
    postfix_expression expected[PARSE_POSTFIX_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_POSTFIX_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        postfix_expression *pe = try_parse_postfix_expression(&l);
        ASSERT_TRUE(postfix_expression_eq(pe, &expected[i]));
    }
}

#define PARSE_ASSIGNMENT_EXPRESSION_SIZE 11
CTEST_SKIP(AST, TEST_PARSE_ASSIGNMENT_EXPRESSION) {
    string src[PARSE_ASSIGNMENT_EXPRESSION_SIZE] = {
        string_new_raw("a = b;\n"),   string_new_raw("a *= b;\n"),  string_new_raw("a /= b;\n"),
        string_new_raw("a %= b;\n"),  string_new_raw("a += b;\n"),  string_new_raw("a -= b;\n"),
        string_new_raw("a <<= b;\n"), string_new_raw("a >>= b;\n"), string_new_raw("a &= b;\n"),
        string_new_raw("a ^= b;\n"),  string_new_raw("a |= b;\n"),
    };
    assignment_expression expected[PARSE_ASSIGNMENT_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_ASSIGNMENT_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        assignment_expression *ae = try_parse_assignment_expression(&l);
        ASSERT_TRUE(assignment_expression_eq(ae, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_ARGUMENT_EXPRESSION_LIST) {
    string src = string_new_raw("a, b, c\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    argument_expression_list *ael = try_parse_argument_expression_list(&l);
    argument_expression_list expected = {0};
    ASSERT_TRUE(argument_expression_list_eq(ael, &expected));
}

#define PARSE_UNARY_EXPRESSION_SIZE 5
CTEST(AST, TEST_PARSE_UNARY_EXPRESSION) {
    string src[PARSE_UNARY_EXPRESSION_SIZE] = {
        string_new_raw("++a;\n"), string_new_raw("--a;\n"), string_new_raw("~a;\n"),
        string_new_raw("sizeof a;\n"), string_new_raw("sizeof(int);\n")};
    unary_expression expected[PARSE_UNARY_EXPRESSION_SIZE] = {
        {{.unary_expr =
              &(unary_expression){
                  {&(postfix_expression){&(primary_expression){{&(ident){1, 1, "a"}}, ident_pe_e},
                                         NULL}},
                  expr_ue_e}},
         inc_unary_expr_ue_e},
        {{.unary_expr =
              &(unary_expression){
                  {&(postfix_expression){&(primary_expression){{&(ident){1, 1, "a"}}, ident_pe_e},
                                         NULL}},
                  expr_ue_e}},
         dec_unary_expr_ue_e},
        {{.cast_expr = {approx_uo_e,
                        &(cast_expression){
                            {&(unary_expression){
                                {&(postfix_expression){
                                    &(primary_expression){{&(ident){1, 1, "a"}}, ident_pe_e},
                                    NULL}},
                                expr_ue_e}},
                            unary_expr_ce_e}}},
         unary_op_cast_expr_ue_e},
        {{.unary_expr =
              &(unary_expression){
                  {&(postfix_expression){&(primary_expression){{&(ident){1, 1, "a"}}, ident_pe_e},
                                         NULL}},
                  expr_ue_e}},
         sizeof_unary_expr_ue_e},
        {{.type_name =
              &(type_name){&(specifier_qualifier_list){
                               1, 1,
                               &(_specifier_qualifier){{&(type_specifier){{NULL}, int_ts_e}},
                                                       type_specifier_sq_e}},
                           NULL}},
         sizeof_type_name_ue_e},
    };
    for (int i = 0; i < 5; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        unary_expression *ue = try_parse_unary_expression(&l);
        ASSERT_TRUE(unary_expression_eq(ue, &expected[i]));
    }
}

#define PARSE_UNARY_OPERATOR_SIZE 6
CTEST_SKIP(AST, TEST_PARSE_UNARY_OPERATOR) {
    string src[PARSE_UNARY_OPERATOR_SIZE] = {string_new_raw("&\n"), string_new_raw("+\n"),
                                             string_new_raw("*\n"), string_new_raw("-\n"),
                                             string_new_raw("~\n"), string_new_raw("!\n")};
    unary_operator expected[PARSE_UNARY_OPERATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_UNARY_OPERATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        unary_operator uo = try_parse_unary_operator(&l);
        ASSERT_TRUE(unary_operator_eq(uo, expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_CAST_EXPRESSION) {
    string src = string_new_raw("(int)a;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    cast_expression *ce = try_parse_cast_expression(&l);
    cast_expression expected = {0};
    ASSERT_TRUE(cast_expression_eq(ce, &expected));
}

#define PARSE_MULTIPLICATIVE_EXPRESSION_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_MULTIPLICATIVE_EXPRESSION) {
    string src[PARSE_MULTIPLICATIVE_EXPRESSION_SIZE] = {
        string_new_raw("3 * 1\n"), string_new_raw("3 / 1\n"), string_new_raw("3 % 1\n")};
    multiplicative_expression expected[PARSE_MULTIPLICATIVE_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_MULTIPLICATIVE_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        multiplicative_expression *me = try_parse_multiplicative_expression(&l);
        ASSERT_TRUE(multiplicative_expression_eq(me, &expected[i]));
    }
}

#define PARSE_ADDITIVE_EXPRESSION_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_ADDITIVE_EXPRESSION) {
    string src[PARSE_ADDITIVE_EXPRESSION_SIZE] = {string_new_raw("3 + 1\n"),
                                                  string_new_raw("3 - 1\n")};
    additive_expression expected[PARSE_ADDITIVE_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_ADDITIVE_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        additive_expression *ae = try_parse_additive_expression(&l);
        ASSERT_TRUE(additive_expression_eq(ae, &expected[i]));
    }
}

#define PARSE_SHIFT_EXPRESSION_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_SHIFT_EXPRESSION) {
    string src[PARSE_SHIFT_EXPRESSION_SIZE] = {string_new_raw("3 >> 1\n"),
                                               string_new_raw("3 << 1\n")};
    shift_expression expected[PARSE_SHIFT_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_SHIFT_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        shift_expression *se = try_parse_shift_expression(&l);
        ASSERT_TRUE(shift_expression_eq(se, &expected[i]));
    }
}

#define PARSE_RELATIONAL_EXPRESSION_SIZE 4
CTEST_SKIP(AST, TEST_PARSE_RELATIONAL_EXPRESSION) {
    string src[PARSE_RELATIONAL_EXPRESSION_SIZE] = {
        string_new_raw("3 > 1\n"), string_new_raw("3 >= 1\n"), string_new_raw("3 < 1\n"),
        string_new_raw("3 <= 1\n")};
    relational_expression expected[PARSE_RELATIONAL_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_RELATIONAL_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        relational_expression *re = try_parse_relational_expression(&l);
        ASSERT_TRUE(relational_expression_eq(re, &expected[i]));
    }
}

#define PARSE_EQUALITY_EXPRESSION_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_EQUALITY_EXPRESSION) {
    string src[PARSE_EQUALITY_EXPRESSION_SIZE] = {string_new_raw("3 == 1\n"),
                                                  string_new_raw("3 != 1\n")};
    equality_expression expected[PARSE_EQUALITY_EXPRESSION_SIZE] = {0};
    for (int i = 0; i < PARSE_EQUALITY_EXPRESSION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        equality_expression *se = try_parse_equality_expression(&l);
        ASSERT_TRUE(equality_expression_eq(se, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_AND_EXPRESSION) {
    string src = string_new_raw("3 & 1;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    and_expression *ce = try_parse_and_expression(&l);
    and_expression expected = {0};
    ASSERT_TRUE(and_expression_eq(ce, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_EXCLUSIVE_OR_EXPRESSION) {
    string src = string_new_raw("3 ^ 1;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    exclusive_or_expression *ce = try_parse_exclusive_or_expression(&l);
    exclusive_or_expression expected = {0};
    ASSERT_TRUE(exclusive_or_expression_eq(ce, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_INCLUSIVE_OR_EXPRESSION) {
    string src = string_new_raw("3 | 1;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    inclusive_or_expression *ce = try_parse_inclusive_or_expression(&l);
    inclusive_or_expression expected = {0};
    ASSERT_TRUE(inclusive_or_expression_eq(ce, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_LOGICAL_AND_EXPRESSION) {
    string src = string_new_raw("3 && 1;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    logical_and_expression *ce = try_parse_logical_and_expression(&l);
    logical_and_expression expected = {0};
    ASSERT_TRUE(logical_and_expression_eq(ce, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_LOGICAL_OR_EXPRESSION) {
    string src = string_new_raw("3 || 1;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    logical_or_expression *ce = try_parse_logical_or_expression(&l);
    logical_or_expression expected = {0};
    ASSERT_TRUE(logical_or_expression_eq(ce, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_CONDITIONAL_EXPRESSION) {
    string src = string_new_raw("a ? b : c;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    conditional_expression *ce = try_parse_conditional_expression(&l);
    conditional_expression expected = {0};
    ASSERT_TRUE(conditional_expression_eq(ce, &expected));
}

#define PARSE_ASSIGNMENT_OPERATOR_SIZE 11
CTEST_SKIP(AST, TEST_PARSE_ASSIGNMENT_OPERATOR) {
    string src[PARSE_ASSIGNMENT_OPERATOR_SIZE] = {
        string_new_raw("=\n"),   string_new_raw("*=\n"),  string_new_raw("/=\n"),
        string_new_raw("%=\n"),  string_new_raw("+=\n"),  string_new_raw("-=\n"),
        string_new_raw("<<=\n"), string_new_raw(">>=\n"), string_new_raw("&=\n"),
        string_new_raw("^=\n"),  string_new_raw("|=\n"),
    };
    assignment_operator expected[PARSE_ASSIGNMENT_OPERATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_ASSIGNMENT_OPERATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        assignment_operator *ao = try_parse_assignment_operator(&l);
        ASSERT_TRUE(assignment_operator_eq(ao, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_CONSTANT_EXPRESSION) {
    string src = string_new_raw("1 ? 2 : 3;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    constant_expression *ce = try_parse_constant_expression(&l);
    constant_expression expected = {0};
    ASSERT_TRUE(constant_expression_eq(ce, &expected));
}

#define PARSE_DECLARATION_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_DECLARATION) {
    string src[PARSE_DECLARATION_SIZE] = {
        string_new_raw("int;\n"),
        string_new_raw("int a = 0;\n"),
    };
    declaration expected[PARSE_DECLARATION_SIZE] = {0};
    for (int i = 0; i < PARSE_DECLARATION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        declaration *d = try_parse_declaration(&l);
        ASSERT_TRUE(declaration_eq(d, &expected[i]));
    }
}

#define PARSE_DECLARATION_SPECIFIER_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_DECLARATION_SPECIFIER) {
    string src[PARSE_DECLARATION_SPECIFIER_SIZE] = {
        string_new_raw("typedef\n"),
        string_new_raw("void\n"),
        string_new_raw("const\n"),
    };
    declaration_specifier expected[PARSE_DECLARATION_SPECIFIER_SIZE] = {0};
    for (int i = 0; i < PARSE_DECLARATION_SPECIFIER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        declaration_specifier *ds = try_parse_declaration_specifier(&l);
        ASSERT_TRUE(declaration_specifier_eq(ds, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_DECLARATION_SPECIFIERS) {
    string src = string_new_raw("typedef void const\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    declaration_specifiers *ds = try_parse_declaration_specifiers(&l);
    declaration_specifiers expected = {0};
    ASSERT_TRUE(declaration_specifiers_eq(ds, &expected));
}

#define PARSE_INIT_DECLARATOR_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_INIT_DECLARATOR) {
    string src[PARSE_INIT_DECLARATOR_SIZE] = {
        string_new_raw("char *c;\n"),
        string_new_raw("char *c = 'c';\n"),
    };
    init_declarator expected[PARSE_INIT_DECLARATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_INIT_DECLARATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        init_declarator *id = try_parse_init_declarator(&l);
        ASSERT_TRUE(init_declarator_eq(id, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_INIT_DECLARATOR_LIST) {
    string src = string_new_raw("int a = 0, b = 1, c = 2;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    init_declarator_list *idl = try_parse_init_declarator_list(&l);
    init_declarator_list expected = {0};
    ASSERT_TRUE(init_declarator_list_eq(idl, &expected));
}

#define PARSE_STORAGE_CLASS_SPECIFIER_SIZE 5
CTEST_SKIP(AST, TEST_PARSE_STORAGE_CLASS_SPECIFIER) {
    string src[PARSE_STORAGE_CLASS_SPECIFIER_SIZE] = {
        string_new_raw("typedef\n"), string_new_raw("extern\n"),   string_new_raw("static\n"),
        string_new_raw("auto\n"),    string_new_raw("register\n"),
    };
    storage_class_specifier expected[PARSE_STORAGE_CLASS_SPECIFIER_SIZE] = {0};
    for (int i = 0; i < PARSE_STORAGE_CLASS_SPECIFIER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        storage_class_specifier *scs = try_parse_storage_class_specifier(&l);
        ASSERT_TRUE(storage_class_specifier_eq(scs, &expected[i]));
    }
}

#define PARSE_STRUCT_OR_UNION_SPECIFIER_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_STRUCT_OR_UNION_SPECIFIER) {
    string src[PARSE_STRUCT_OR_UNION_SPECIFIER_SIZE] = {
        string_new_raw("struct hi { int there; }\n"),
        string_new_raw("struct { int there; }\n"),
        string_new_raw("struct hi\n"),
    };
    struct_or_union_specifier expected[PARSE_STRUCT_OR_UNION_SPECIFIER_SIZE] = {0};
    for (int i = 0; i < PARSE_STRUCT_OR_UNION_SPECIFIER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        struct_or_union_specifier *sous = try_parse_struct_or_union_specifier(&l);
        ASSERT_TRUE(struct_or_union_specifier_eq(sous, &expected[i]));
    }
}

#define PARSE_STRUCT_OR_UNION_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_STRUCT_OR_UNION) {
    string src[PARSE_STRUCT_OR_UNION_SIZE] = {
        string_new_raw("struct\n"),
        string_new_raw("union\n"),
    };
    struct_or_union expected[PARSE_STRUCT_OR_UNION_SIZE] = {0};
    for (int i = 0; i < PARSE_STRUCT_OR_UNION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        struct_or_union *sou = try_parse_struct_or_union(&l);
        ASSERT_TRUE(struct_or_union_eq(sou, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_STRUCT_DECLARATION) {
    string src = string_new_raw("int hey;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    struct_declaration *sd = try_parse_struct_declaration(&l);
    struct_declaration expected = {0};
    ASSERT_TRUE(struct_declaration_eq(sd, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_STRUCT_DECLARATION_LIST) {
    string src = string_new_raw("int hey; char c;\n");
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    struct_declaration_list *sdl = try_parse_struct_declaration_list(&l);
    struct_declaration_list expected = {0};
    ASSERT_TRUE(struct_declaration_list_eq(sdl, &expected));
}

#define PARSE__SPECIFIER_QUALIFIER_SIZE 2
CTEST_SKIP(AST, TEST_PARSE__SPECIFIER_QUALIFIER) {
    string src[PARSE__SPECIFIER_QUALIFIER_SIZE] = {
        string_new_raw("void\n"),
        string_new_raw("const\n"),
    };
    _specifier_qualifier expected[PARSE__SPECIFIER_QUALIFIER_SIZE] = {0};
    for (int i = 0; i < PARSE__SPECIFIER_QUALIFIER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        _specifier_qualifier *sq = try_parse__specifier_qualifier(&l);
        ASSERT_TRUE(_specifier_qualifier_eq(sq, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_STRUCT_DECLARATOR_LIST) {
    string src = string_new_raw("a, b, : 4, c, : 4, d\n");
    struct_declarator_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    struct_declarator_list *sq = try_parse_struct_declarator_list(&l);
    ASSERT_TRUE(struct_declarator_list_eq(sq, &expected));
}

#define PARSE_STRUCT_DECLARATOR_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_STRUCT_DECLARATOR) {
    string src[PARSE_STRUCT_DECLARATOR_SIZE] = {
        string_new_raw(": 4\n"),
        string_new_raw("a\n"),
    };
    struct_declarator expected[PARSE_STRUCT_DECLARATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_STRUCT_DECLARATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        struct_declarator *sq = try_parse_struct_declarator(&l);
        ASSERT_TRUE(struct_declarator_eq(sq, &expected[i]));
    }
}

#define PARSE_ENUM_SPECIFIER_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_ENUM_SPECIFIER) {
    string src[PARSE_ENUM_SPECIFIER_SIZE] = {
        string_new_raw("enum hi { there }\n"),
        string_new_raw("enum { there }\n"),
        string_new_raw("enum hi\n"),
    };
    enum_specifier expected[PARSE_ENUM_SPECIFIER_SIZE] = {0};
    for (int i = 0; i < PARSE_ENUM_SPECIFIER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        enum_specifier *sous = try_parse_enum_specifier(&l);
        ASSERT_TRUE(enum_specifier_eq(sous, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_ENUMERATOR_LIST) {
    string src = string_new_raw("a, b, c = 4");
    enumerator_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    enumerator_list *sq = try_parse_enumerator_list(&l);
    ASSERT_TRUE(enumerator_list_eq(sq, &expected));
}

#define PARSE_ENUMERATOR_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_ENUMERATOR) {
    string src[PARSE_ENUMERATOR_SIZE] = {
        string_new_raw("hey\n"),
        string_new_raw("hey = 3\n"),
    };
    enumerator expected[PARSE_ENUMERATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_ENUMERATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        enumerator *sq = try_parse_enumerator(&l);
        ASSERT_TRUE(enumerator_eq(sq, &expected[i]));
    }
}

#define PARSE_TYPE_QUALIFIER_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_TYPE_QUALIFIER) {
    string src[PARSE_TYPE_QUALIFIER_SIZE] = {
        string_new_raw("const\n"),
        string_new_raw("volatile\n"),
    };
    type_qualifier expected[PARSE_TYPE_QUALIFIER_SIZE] = {0};
    for (int i = 0; i < PARSE_TYPE_QUALIFIER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        type_qualifier *sq = try_parse_type_qualifier(&l);
        ASSERT_TRUE(type_qualifier_eq(sq, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_TYPE_QUALIFIER_LIST) {
    string src = string_new_raw("const volatile");
    type_qualifier_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    type_qualifier_list *sq = try_parse_type_qualifier_list(&l);
    ASSERT_TRUE(type_qualifier_list_eq(sq, &expected));
}

#define PARSE_DECLARATOR_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_DECLARATOR) {
    string src[PARSE_DECLARATOR_SIZE] = {
        string_new_raw("hi\n"),
        string_new_raw("*hi\n"),
    };
    declarator expected[PARSE_DECLARATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_DECLARATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        declarator *sq = try_parse_declarator(&l);
        ASSERT_TRUE(declarator_eq(sq, &expected[i]));
    }
}

#define PARSE_DIRECT_DECLARATOR_SIZE 7
CTEST_SKIP(AST, TEST_PARSE_DIRECT_DECLARATOR) {
    string src[PARSE_DIRECT_DECLARATOR_SIZE] = {
        string_new_raw("hi\n"),
        string_new_raw("(hi)\n"),
        string_new_raw("hi[4]\n"),
        string_new_raw("hi[]\n"),
        string_new_raw("hi(int a, int b)\n"),
        string_new_raw("hi(a, b)\n"),
        string_new_raw("hi()\n"),
    };
    direct_declarator expected[PARSE_DIRECT_DECLARATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_DIRECT_DECLARATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        direct_declarator *sq = try_parse_direct_declarator(&l);
        ASSERT_TRUE(direct_declarator_eq(sq, &expected[i]));
    }
}

#define PARSE_POINTER_SIZE 4
CTEST(AST, TEST_PARSE_POINTER) {
    string src[PARSE_POINTER_SIZE] = {
        string_new_raw("*\n"),
        string_new_raw("*const\n"),
        string_new_raw("**\n"),
        string_new_raw("*const *\n"),
    };
    pointer expected[PARSE_POINTER_SIZE] = {
        {NULL, NULL},
        {&(type_qualifier_list){1, 1, &(type_qualifier){const_tq_e}}, NULL},
        {NULL, &(pointer){NULL, NULL}},
        {&(type_qualifier_list){1, 1, &(type_qualifier){const_tq_e}}, &(pointer){NULL, NULL}},
    };
    for (int i = 0; i < PARSE_POINTER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        pointer *sq = try_parse_pointer(&l);
        ASSERT_TRUE(pointer_eq(sq, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_PARAMETER_TYPE_LIST) {
    string src = string_new_raw("int a, int b, ...");
    parameter_type_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    parameter_type_list *sq = try_parse_parameter_type_list(&l);
    ASSERT_TRUE(parameter_type_list_eq(sq, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_PARAMETER_LIST) {
    string src = string_new_raw("int a, int b");
    parameter_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    parameter_list *sq = try_parse_parameter_list(&l);
    ASSERT_TRUE(parameter_list_eq(sq, &expected));
}

#define PARSE_PARAMETER_DECLARATION_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_PARAMETER_DECLARATION) {
    string src[PARSE_PARAMETER_DECLARATION_SIZE] = {
        string_new_raw("char\n"),
        string_new_raw("char hi\n"),
        string_new_raw("char *\n"),
    };
    parameter_declaration expected[PARSE_PARAMETER_DECLARATION_SIZE] = {0};
    for (int i = 0; i < PARSE_PARAMETER_DECLARATION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        parameter_declaration *sq = try_parse_parameter_declaration(&l);
        ASSERT_TRUE(parameter_declaration_eq(sq, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_IDENTIFIER_LIST) {
    string src = string_new_raw("a, b, c");
    identifier_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    identifier_list *sq = try_parse_identifier_list(&l);
    ASSERT_TRUE(identifier_list_eq(sq, &expected));
}

#define PARSE_ABSTRACT_DELCLARATOR_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_ABSTRACT_DECLARATOR) {
    string src[PARSE_ABSTRACT_DELCLARATOR_SIZE] = {
        string_new_raw("*\n"),
        string_new_raw("[]\n"),
        string_new_raw("*[]\n"),
    };
    abstract_declarator expected[PARSE_ABSTRACT_DELCLARATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_ABSTRACT_DELCLARATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        abstract_declarator *sq = try_parse_abstract_declarator(&l);
        ASSERT_TRUE(abstract_declarator_eq(sq, &expected[i]));
    }
}

#define PARSE_DIRECT_ABSTRACT_DECLARATOR_SIZE 9
CTEST_SKIP(AST, TEST_PARSE_DIRECT_ABSTRACT_DECLARATOR) {
    string src[PARSE_DIRECT_ABSTRACT_DECLARATOR_SIZE] = {
        string_new_raw("(*)\n"),     string_new_raw("[]\n"),      string_new_raw("[4]\n"),
        string_new_raw("(*) []\n"),  string_new_raw("(*) [4]\n"), string_new_raw("()\n"),
        string_new_raw("(int a)\n"), string_new_raw("(*)()\n"),   string_new_raw("(*)(int a)\n"),
    };
    direct_abstract_declarator expected[PARSE_DIRECT_ABSTRACT_DECLARATOR_SIZE] = {0};
    for (int i = 0; i < PARSE_DIRECT_ABSTRACT_DECLARATOR_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        direct_abstract_declarator *sq = try_parse_direct_abstract_declarator(&l);
        ASSERT_TRUE(direct_abstract_declarator_eq(sq, &expected[i]));
    }
}

#define PARSE_INITIALIZER_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_INITIALIZER) {
    string src[PARSE_INITIALIZER_SIZE] = {
        string_new_raw("a = b;\n"),
        string_new_raw("{ a = b }\n"),
        string_new_raw("{ a = b, }\n"),
    };
    initializer expected[PARSE_INITIALIZER_SIZE] = {0};
    for (int i = 0; i < PARSE_INITIALIZER_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        initializer *sq = try_parse_initializer(&l);
        ASSERT_TRUE(initializer_eq(sq, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_INITIALIZER_LIST) {
    string src = string_new_raw("a = b, b = c");
    initializer_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    initializer_list *sq = try_parse_initializer_list(&l);
    ASSERT_TRUE(initializer_list_eq(sq, &expected));
}

#define PARSE_STATEMENT_SIZE 6
CTEST_SKIP(AST, TEST_PARSE_STATEMENT) {
    string src[PARSE_STATEMENT_SIZE] = {
        string_new_raw("a: b = c;\n"),
        string_new_raw("{}\n"),
        string_new_raw("a = b;\n"),
        string_new_raw("if (a == b) {}\n"),
        string_new_raw("while (a == b) {}\n"),
        string_new_raw("continue;\n"),
    };
    statement expected[PARSE_STATEMENT_SIZE] = {0};
    for (int i = 0; i < PARSE_STATEMENT_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        statement *sq = try_parse_statement(&l);
        ASSERT_TRUE(statement_eq(sq, &expected[i]));
    }
}

#define PARSE_LABELED_STATEMENT_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_LABELED_STATEMENT) {
    string src[PARSE_LABELED_STATEMENT_SIZE] = {
        string_new_raw("a: b = c;\n"),
        string_new_raw("case 2: b = c;\n"),
        string_new_raw("default: b = c;\n"),
    };
    labeled_statement expected[PARSE_LABELED_STATEMENT_SIZE] = {0};
    for (int i = 0; i < PARSE_LABELED_STATEMENT_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        labeled_statement *sq = try_parse_labeled_statement(&l);
        ASSERT_TRUE(labeled_statement_eq(sq, &expected[i]));
    }
}

#define PARSE_COMPOUND_STATEMENT_SIZE 4
CTEST_SKIP(AST, TEST_PARSE_COMPOUND_STATEMENT) {
    string src[PARSE_COMPOUND_STATEMENT_SIZE] = {
        string_new_raw("{}\n"),
        string_new_raw("{;}\n"),
        string_new_raw("{int a;}\n"),
        string_new_raw("{int a; a = b;}\n"),
    };
    compound_statement expected[PARSE_COMPOUND_STATEMENT_SIZE] = {0};
    for (int i = 0; i < PARSE_COMPOUND_STATEMENT_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        compound_statement *sq = try_parse_compound_statement(&l);
        ASSERT_TRUE(compound_statement_eq(sq, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_DECLARATION_LIST) {
    string src = string_new_raw("int a = 0; int b = 0;\n");
    declaration_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    declaration_list *d = try_parse_declaration_list(&l);
    ASSERT_TRUE(declaration_list_eq(d, &expected));
}

CTEST_SKIP(AST, TEST_PARSE_STATEMENT_LIST) {
    string src = string_new_raw("{} {}\n");
    statement_list expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    statement_list *d = try_parse_statement_list(&l);
    ASSERT_TRUE(statement_list_eq(d, &expected));
}

#define PARSE_EXPRESSION_STATEMENT_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_EXPRESSION_STATEMENT) {
    string src[PARSE_EXPRESSION_STATEMENT_SIZE] = {
        string_new_raw(";\n"),
        string_new_raw("a = 0;\n"),
    };
    expression_statement expected[PARSE_EXPRESSION_STATEMENT_SIZE] = {0};
    for (int i = 0; i < PARSE_EXPRESSION_STATEMENT_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        expression_statement *sq = try_parse_expression_statement(&l);
        ASSERT_TRUE(expression_statement_eq(sq, &expected[i]));
    }
}

#define PARSE_SELECTION_STATEMENT_SIZE 3
CTEST_SKIP(AST, TEST_PARSE_SELECTION_STATEMENT) {
    string src[PARSE_SELECTION_STATEMENT_SIZE] = {
        string_new_raw("if (a == 0) {}\n"),
        string_new_raw("if (a == 0) {} else {}\n"),
        string_new_raw("switch (a == 0) {}\n"),
    };
    selection_statement expected[PARSE_SELECTION_STATEMENT_SIZE] = {0};
    for (int i = 0; i < PARSE_SELECTION_STATEMENT_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        selection_statement *sq = try_parse_selection_statement(&l);
        ASSERT_TRUE(selection_statement_eq(sq, &expected[i]));
    }
}

#define PARSE_ITERATION_STATEMENT_SIZE 4
CTEST_SKIP(AST, TEST_PARSE_ITERATION_STATEMENT) {
    string src[PARSE_ITERATION_STATEMENT_SIZE] = {
        string_new_raw("while (a) {}\n"),
        string_new_raw("do {} while (a)\n"),
        string_new_raw("for (;;) {}\n"),
        string_new_raw("for (;; a) {}\n"),
    };
    iteration_statement expected[PARSE_ITERATION_STATEMENT_SIZE] = {0};
    for (int i = 0; i < PARSE_ITERATION_STATEMENT_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        iteration_statement *sq = try_parse_iteration_statement(&l);
        ASSERT_TRUE(iteration_statement_eq(sq, &expected[i]));
    }
}

#define PARSE_JUMP_STATEMENT_SIZE 5
CTEST_SKIP(AST, TEST_PARSE_JUMP_STATEMENT) {
    string src[PARSE_JUMP_STATEMENT_SIZE] = {
        string_new_raw("goto a;\n"), string_new_raw("continue;\n"), string_new_raw("break;\n"),
        string_new_raw("return;\n"), string_new_raw("return 0;\n"),
    };
    jump_statement expected[PARSE_JUMP_STATEMENT_SIZE] = {0};
    for (int i = 0; i < PARSE_JUMP_STATEMENT_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        jump_statement *sq = try_parse_jump_statement(&l);
        ASSERT_TRUE(jump_statement_eq(sq, &expected[i]));
    }
}

#define PARSE_EXTERNAL_DECLARATION_SIZE 2
CTEST_SKIP(AST, TEST_PARSE_EXTERNAL_DECLARATION) {
    string src[PARSE_EXTERNAL_DECLARATION_SIZE] = {
        string_new_raw("int i = 0;\n"),
        string_new_raw("int main() {}\n"),
    };
    external_declaration expected[PARSE_EXTERNAL_DECLARATION_SIZE] = {0};
    for (int i = 0; i < PARSE_EXTERNAL_DECLARATION_SIZE; i++) {
        preprocessor pp = preprocessor_new(&src[i]);
        vector_pp_token tokens = preprocessor_run(&pp);
        lexer l = lexer_new(&tokens);
        external_declaration *sq = try_parse_external_declaration(&l);
        ASSERT_TRUE(external_declaration_eq(sq, &expected[i]));
    }
}

CTEST_SKIP(AST, TEST_PARSE_FUNCTION_DEFINITION) {
    string src = string_new_raw("int main() {}\n");
    function_definition expected = {0};
    preprocessor pp = preprocessor_new(&src);
    vector_pp_token tokens = preprocessor_run(&pp);
    lexer l = lexer_new(&tokens);
    function_definition *d = try_parse_function_definition(&l);
    ASSERT_TRUE(function_definition_eq(d, &expected));
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
