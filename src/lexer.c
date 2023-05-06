#include "lexer.h"
#include "stdlib.h"
#include "token.h"
#include <stdio.h>

typedef struct {
    vector_pp_token *pp_tokens;
    uintptr_t pp_idx;
    ll_ast_token *ast_tokens;
} lexer;

expression *try_parse_expression(lexer *l);
primary_expression *try_parse_primary_expression(lexer *l);
postfix_expression *try_parse_postfix_expression(lexer *l);
assignment_expression *try_parse_assignment_expression(lexer *l);
argument_expression_list *try_parse_argument_expression_list(lexer *l);
unary_expression *try_parse_unary_expression(lexer *l);
unary_operator *try_parse_unary_operator(lexer *l);
cast_expression *try_parse_cast_expression(lexer *l);
multiplicative_expression *try_parse_multiplicative_expression(lexer *l);
additive_expression *try_parse_additive_expression(lexer *l);
shift_expression *try_parse_shift_expression(lexer *l);
relational_expression *try_parse_relational_expression(lexer *l);
equality_expression *try_parse_equality_expression(lexer *l);
and_expression *try_parse_and_expression(lexer *l);
exclusive_or_expression *try_parse_exclusive_or_expression(lexer *l);
inclusive_or_expression *try_parse_inclusive_or_expression(lexer *l);
logical_and_expression *try_parse_logical_and_expression(lexer *l);
logical_or_expression *try_parse_logical_or_expression(lexer *l);
conditional_expression *try_parse_conditional_expression(lexer *l);
assignment_operator *try_parse_assignment_operator(lexer *l);
constant_expression *try_parse_constant_expression(lexer *l);
declaration *try_parse_declaration(lexer *l);
declaration_specifiers *try_parse_declaration_specifiers(lexer *l);
init_declarator *try_parse_init_declarator(lexer *l);
init_declarator_list *try_parse_init_declarator_list(lexer *l);
storage_class_specifier *try_parse_storage_class_specifier(lexer *l);
type_specifier *try_parse_type_specifier(lexer *l);
struct_or_union_specifier *try_parse_struct_or_union_specifier(lexer *l);
struct_or_union *try_parse_struct_or_union(lexer *l);
struct_declaration *try_parse_struct_declaration(lexer *l);
struct_declaration_list *try_parse_struct_declaration_list(lexer *l);
_specifier_qualifier *try_parse__specifier_qualifier(lexer *l);
struct_declarator_list *try_parse_struct_declarator_list(lexer *l);
struct_declarator *try_parse_struct_declarator(lexer *l);
enum_specifier *try_parse_enum_specifier(lexer *l);
enumerator_list *try_parse_enumerator_list(lexer *l);
enumerator *try_parse_enumerator(lexer *l);
type_qualifier *try_parse_type_qualifier(lexer *l);
type_qualifier_list *try_parse_type_qualifier_list(lexer *l);
declarator *try_parse_declarator(lexer *l);
direct_declarator *try_parse_direct_declarator(lexer *l);
pointer *try_parse_pointer(lexer *l);
type_qualifier_list *try_parse_type_qualifier_list(lexer *l);
parameter_type_list *try_parse_parameter_type_list(lexer *l);
parameter_list *try_parse_parameter_list(lexer *l);
parameter_declaration *try_parse_parameter_declaration(lexer *l);
identifier_list *try_parse_identifier_list(lexer *l);
abstract_declarator *try_parse_abstract_declarator(lexer *l);
direct_abstract_declarator *try_parse_direct_abstract_declarator(lexer *l);
initializer *try_parse_initializer(lexer *l);
initializer_list *try_parse_initializer_list(lexer *l);
statement *try_parse_statement(lexer *l);
labeled_statement *try_parse_labeled_statement(lexer *l);
compound_statement *try_parse_compound_statement(lexer *l);
declaration_list *try_parse_declaration_list(lexer *l);
statement_list *try_parse_statement_list(lexer *l);
expression_statement *try_parse_expression_statement(lexer *l);
selection_statement *try_parse_selection_statement(lexer *l);
iteration_statement *try_parse_iteration_statement(lexer *l);
jump_statement *try_parse_jump_statement(lexer *l);
translation_unit *try_parse_translation_unit(lexer *l);
external_declaration *try_parse_external_declaration(lexer *l);
function_definition *try_parse_function_definition(lexer *l);

translation_unit *generate_ast(vector_pp_token *tokens) {
    lexer l;
    l.pp_tokens = tokens;
    l.ast_tokens = ll_ast_token_new();
    try_parse_translation_unit(&l);
    return l.ast_tokens->start->data.p.translation_unit;
}

translation_unit *try_parse_translation_unit(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_translation_unit *");
    exit(EXIT_FAILURE);
}
expression *try_parse_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_expression *");
    exit(EXIT_FAILURE);
}
primary_expression *try_parse_primary_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_primary_expression *");
    exit(EXIT_FAILURE);
}
postfix_expression *try_parse_postfix_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_postfix_expression *");
    exit(EXIT_FAILURE);
}
assignment_expression *try_parse_assignment_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_assignment_expression *");
    exit(EXIT_FAILURE);
}
argument_expression_list *try_parse_argument_expression_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_argument_expression_list *");
    exit(EXIT_FAILURE);
}
unary_expression *try_parse_unary_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_unary_expression *");
    exit(EXIT_FAILURE);
}
unary_operator *try_parse_unary_operator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_unary_operator *");
    exit(EXIT_FAILURE);
}
cast_expression *try_parse_cast_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_cast_expression *");
    exit(EXIT_FAILURE);
}
multiplicative_expression *try_parse_multiplicative_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_multiplicative_expression *");
    exit(EXIT_FAILURE);
}
additive_expression *try_parse_additive_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_additive_expression *");
    exit(EXIT_FAILURE);
}
shift_expression *try_parse_shift_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_shift_expression *");
    exit(EXIT_FAILURE);
}
relational_expression *try_parse_relational_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_relational_expression *");
    exit(EXIT_FAILURE);
}
equality_expression *try_parse_equality_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_equality_expression *");
    exit(EXIT_FAILURE);
}
and_expression *try_parse_and_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_and_expression *");
    exit(EXIT_FAILURE);
}
exclusive_or_expression *try_parse_exclusive_or_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_exclusive_or_expression *");
    exit(EXIT_FAILURE);
}
inclusive_or_expression *try_parse_inclusive_or_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_inclusive_or_expression *");
    exit(EXIT_FAILURE);
}
logical_and_expression *try_parse_logical_and_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_logical_and_expression *");
    exit(EXIT_FAILURE);
}
logical_or_expression *try_parse_logical_or_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_logical_or_expression *");
    exit(EXIT_FAILURE);
}
conditional_expression *try_parse_conditional_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_conditional_expression *");
    exit(EXIT_FAILURE);
}
assignment_operator *try_parse_assignment_operator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_assignment_operator *");
    exit(EXIT_FAILURE);
}
constant_expression *try_parse_constant_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_constant_expression *");
    exit(EXIT_FAILURE);
}
declaration *try_parse_declaration(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_declaration *");
    exit(EXIT_FAILURE);
}
declaration_specifiers *try_parse_declaration_specifiers(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_declaration_specifiers *");
    exit(EXIT_FAILURE);
}
init_declarator *try_parse_init_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_init_declarator *");
    exit(EXIT_FAILURE);
}
init_declarator_list *try_parse_init_declarator_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_init_declarator_list *");
    exit(EXIT_FAILURE);
}
storage_class_specifier *try_parse_storage_class_specifier(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_storage_class_specifier *");
    exit(EXIT_FAILURE);
}
type_specifier *try_parse_type_specifier(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_type_specifier *");
    exit(EXIT_FAILURE);
}
struct_or_union_specifier *try_parse_struct_or_union_specifier(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_or_union_specifier *");
    exit(EXIT_FAILURE);
}
struct_or_union *try_parse_struct_or_union(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_or_union *");
    exit(EXIT_FAILURE);
}
struct_declaration *try_parse_struct_declaration(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_declaration *");
    exit(EXIT_FAILURE);
}
struct_declaration_list *try_parse_struct_declaration_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_declaration_list *");
    exit(EXIT_FAILURE);
}
_specifier_qualifier *try_parse__specifier_qualifier(lexer *l) {
    (void)l;
    printf("unimplemented try_parse__specifier_qualifier *");
    exit(EXIT_FAILURE);
}
struct_declarator_list *try_parse_struct_declarator_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_declarator_list *");
    exit(EXIT_FAILURE);
}
struct_declarator *try_parse_struct_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_declarator *");
    exit(EXIT_FAILURE);
}
enum_specifier *try_parse_enum_specifier(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_enum_specifier *");
    exit(EXIT_FAILURE);
}
enumerator_list *try_parse_enumerator_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_enumerator_list *");
    exit(EXIT_FAILURE);
}
enumerator *try_parse_enumerator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_enumerator *");
    exit(EXIT_FAILURE);
}
type_qualifier *try_parse_type_qualifier(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_type_qualifier *");
    exit(EXIT_FAILURE);
}
type_qualifier_list *try_parse_type_qualifier_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_type_qualifier_list *");
    exit(EXIT_FAILURE);
}
declarator *try_parse_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_declarator *");
    exit(EXIT_FAILURE);
}
direct_declarator *try_parse_direct_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_direct_declarator *");
    exit(EXIT_FAILURE);
}
pointer *try_parse_pointer(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_pointer *");
    exit(EXIT_FAILURE);
}
parameter_type_list *try_parse_parameter_type_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_parameter_type_list *");
    exit(EXIT_FAILURE);
}
parameter_list *try_parse_parameter_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_parameter_list *");
    exit(EXIT_FAILURE);
}
parameter_declaration *try_parse_parameter_declaration(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_parameter_declaration *");
    exit(EXIT_FAILURE);
}
identifier_list *try_parse_identifier_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_identifier_list *");
    exit(EXIT_FAILURE);
}
abstract_declarator *try_parse_abstract_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_abstract_declarator *");
    exit(EXIT_FAILURE);
}
direct_abstract_declarator *try_parse_direct_abstract_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_direct_abstract_declarator *");
    exit(EXIT_FAILURE);
}
initializer *try_parse_initializer(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_initializer *");
    exit(EXIT_FAILURE);
}
initializer_list *try_parse_initializer_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_initializer_list *");
    exit(EXIT_FAILURE);
}
statement *try_parse_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_statement *");
    exit(EXIT_FAILURE);
}
labeled_statement *try_parse_labeled_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_labeled_statement *");
    exit(EXIT_FAILURE);
}
compound_statement *try_parse_compound_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_compound_statement *");
    exit(EXIT_FAILURE);
}
declaration_list *try_parse_declaration_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_declaration_list *");
    exit(EXIT_FAILURE);
}
statement_list *try_parse_statement_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_statement_list *");
    exit(EXIT_FAILURE);
}
expression_statement *try_parse_expression_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_expression_statement *");
    exit(EXIT_FAILURE);
}
selection_statement *try_parse_selection_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_selection_statement *");
    exit(EXIT_FAILURE);
}
iteration_statement *try_parse_iteration_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_iteration_statement *");
    exit(EXIT_FAILURE);
}
jump_statement *try_parse_jump_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_jump_statement *");
    exit(EXIT_FAILURE);
}
external_declaration *try_parse_external_declaration(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_external_declaration *");
    exit(EXIT_FAILURE);
}
function_definition *try_parse_function_definition(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_function_definition *");
    exit(EXIT_FAILURE);
}
