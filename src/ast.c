#include "ast.h"
#include "string.h"

#include <stdio.h>
#include <stdlib.h>

IMPL_VECTOR(type_qualifier)
IMPL_TYPEDEF_VECTOR(type_qualifier, type_qualifier_list)
IMPL_VECTOR(assignment_expression)
IMPL_TYPEDEF_VECTOR(assignment_expression, argument_expression_list)
IMPL_TYPEDEF_VECTOR(assignment_expression, expression)
IMPL_VECTOR(init_declarator)
IMPL_TYPEDEF_VECTOR(init_declarator, init_declarator_list)
IMPL_VECTOR(struct_declaration)
IMPL_TYPEDEF_VECTOR(struct_declaration, struct_declaration_list)
IMPL_VECTOR(_specifier_qualifier)
IMPL_TYPEDEF_VECTOR(_specifier_qualifier, specifier_qualifier_list)
IMPL_VECTOR(struct_declarator)
IMPL_TYPEDEF_VECTOR(struct_declarator, struct_declarator_list)
IMPL_VECTOR(enumerator)
IMPL_TYPEDEF_VECTOR(enumerator, enumerator_list)
IMPL_VECTOR(parameter_declaration)
IMPL_TYPEDEF_VECTOR(parameter_declaration, parameter_list)
IMPL_VECTOR(ident)
IMPL_TYPEDEF_VECTOR(ident, identifier_list)
IMPL_VECTOR(initializer)
IMPL_TYPEDEF_VECTOR(initializer, initializer_list)
IMPL_VECTOR(statement)
IMPL_TYPEDEF_VECTOR(statement, statement_list)
IMPL_VECTOR(declaration)
IMPL_TYPEDEF_VECTOR(declaration, declaration_list)
IMPL_VECTOR(_decl_spec)
IMPL_TYPEDEF_VECTOR(_decl_spec, declaration_specifiers)
IMPL_VECTOR(external_declaration)
IMPL_TYPEDEF_VECTOR(external_declaration, translation_unit)
IMPL_LINKED_LIST(ast_token)

ast_token *ast_expression(expression *expr) {
    ast_token *t = malloc(sizeof(expression));
    t->e = expression_ast_e;
    t->p.expr = expr;
    return t;
}
ast_token *ast_primary_expression(primary_expression *primary_expr) {
    ast_token *t = malloc(sizeof(primary_expression));
    t->e = primary_expression_ast_e;
    t->p.primary_expr = primary_expr;
    return t;
}
ast_token *ast_postfix_expression(postfix_expression *postfix_expr) {
    ast_token *t = malloc(sizeof(postfix_expression));
    t->e = postfix_expression_ast_e;
    t->p.postfix_expr = postfix_expr;
    return t;
}
ast_token *ast_assignment_expression(assignment_expression *assignment_expr) {
    ast_token *t = malloc(sizeof(assignment_expression));
    t->e = assignment_expression_ast_e;
    t->p.assignment_expr = assignment_expr;
    return t;
}
ast_token *ast_argument_expression_list(argument_expression_list *argument_expr_list) {
    ast_token *t = malloc(sizeof(argument_expression_list));
    t->e = argument_expression_list_ast_e;
    t->p.argument_expr_list = argument_expr_list;
    return t;
}
ast_token *ast_unary_expression(unary_expression *unary_expr) {
    ast_token *t = malloc(sizeof(unary_expression));
    t->e = unary_expression_ast_e;
    t->p.unary_expr = unary_expr;
    return t;
}
ast_token *ast_unary_operator(unary_operator *unary_op) {
    ast_token *t = malloc(sizeof(unary_operator));
    t->e = unary_operator_ast_e;
    t->p.unary_op = unary_op;
    return t;
}
ast_token *ast_cast_expression(cast_expression *cast_expr) {
    ast_token *t = malloc(sizeof(cast_expression));
    t->e = cast_expression_ast_e;
    t->p.cast_expr = cast_expr;
    return t;
}
ast_token *ast_multiplicative_expression(multiplicative_expression *multiplicative_expr) {
    ast_token *t = malloc(sizeof(multiplicative_expression));
    t->e = multiplicative_expression_ast_e;
    t->p.multiplicative_expr = multiplicative_expr;
    return t;
}
ast_token *ast_additive_expression(additive_expression *additive_expr) {
    ast_token *t = malloc(sizeof(additive_expression));
    t->e = additive_expression_ast_e;
    t->p.additive_expr = additive_expr;
    return t;
}
ast_token *ast_shift_expression(shift_expression *shift_expr) {
    ast_token *t = malloc(sizeof(shift_expression));
    t->e = shift_expression_ast_e;
    t->p.shift_expr = shift_expr;
    return t;
}
ast_token *ast_relational_expression(relational_expression *relational_expr) {
    ast_token *t = malloc(sizeof(relational_expression));
    t->e = relational_expression_ast_e;
    t->p.relational_expr = relational_expr;
    return t;
}
ast_token *ast_equality_expression(equality_expression *equality_expr) {
    ast_token *t = malloc(sizeof(equality_expression));
    t->e = equality_expression_ast_e;
    t->p.equality_expr = equality_expr;
    return t;
}
ast_token *ast_and_expression(and_expression *and_expr) {
    ast_token *t = malloc(sizeof(and_expression));
    t->e = and_expression_ast_e;
    t->p.and_expr = and_expr;
    return t;
}
ast_token *ast_exclusive_or_expression(exclusive_or_expression *exclusive_or_expr) {
    ast_token *t = malloc(sizeof(exclusive_or_expression));
    t->e = exclusive_or_expression_ast_e;
    t->p.exclusive_or_expr = exclusive_or_expr;
    return t;
}
ast_token *ast_inclusive_or_expression(inclusive_or_expression *inclusive_or_expr) {
    ast_token *t = malloc(sizeof(inclusive_or_expression));
    t->e = inclusive_or_expression_ast_e;
    t->p.inclusive_or_expr = inclusive_or_expr;
    return t;
}
ast_token *ast_logical_and_expression(logical_and_expression *logical_and_expr) {
    ast_token *t = malloc(sizeof(logical_and_expression));
    t->e = logical_and_expression_ast_e;
    t->p.logical_and_expr = logical_and_expr;
    return t;
}
ast_token *ast_logical_or_expression(logical_or_expression *logical_or_expr) {
    ast_token *t = malloc(sizeof(logical_or_expression));
    t->e = logical_or_expression_ast_e;
    t->p.logical_or_expr = logical_or_expr;
    return t;
}
ast_token *ast_conditional_expression(conditional_expression *conditional_expr) {
    ast_token *t = malloc(sizeof(conditional_expression));
    t->e = conditional_expression_ast_e;
    t->p.conditional_expr = conditional_expr;
    return t;
}
ast_token *ast_assignment_operator(assignment_operator *assignment_op) {
    ast_token *t = malloc(sizeof(assignment_operator));
    t->e = assignment_operator_ast_e;
    t->p.assignment_op = assignment_op;
    return t;
}
ast_token *ast_constant_expression(constant_expression *constant_expr) {
    ast_token *t = malloc(sizeof(constant_expression));
    t->e = constant_expression_ast_e;
    t->p.constant_expr = constant_expr;
    return t;
}
ast_token *ast_declaration(declaration *decl) {
    ast_token *t = malloc(sizeof(declaration));
    t->e = declaration_ast_e;
    t->p.declaration = decl;
    return t;
}
ast_token *ast_declaration_specifiers(declaration_specifiers *decl_specs) {
    ast_token *t = malloc(sizeof(declaration_specifiers));
    t->e = declaration_specifiers_ast_e;
    t->p.declaration_specifiers = decl_specs;
    return t;
}
ast_token *ast_init_declarator(init_declarator *init_decl) {
    ast_token *t = malloc(sizeof(init_declarator));
    t->e = init_declarator_ast_e;
    t->p.init_declarator = init_decl;
    return t;
}
ast_token *ast_init_declarator_list(init_declarator_list *init_decl_list) {
    ast_token *t = malloc(sizeof(init_declarator_list));
    t->e = init_declarator_list_ast_e;
    t->p.init_declarator_list = init_decl_list;
    return t;
}
ast_token *ast_storage_class_specifier(storage_class_specifier *scs) {
    ast_token *t = malloc(sizeof(storage_class_specifier));
    t->e = storage_class_specifier_ast_e;
    t->p.scs = scs;
    return t;
}
ast_token *ast_type_specifier(type_specifier *type_spec) {
    ast_token *t = malloc(sizeof(type_specifier));
    t->e = type_specifier_ast_e;
    t->p.type_specifier = type_spec;
    return t;
}
ast_token *ast_struct_or_union_specifier(struct_or_union_specifier *sou_spec) {
    ast_token *t = malloc(sizeof(struct_or_union_specifier));
    t->e = struct_or_union_specifier_ast_e;
    t->p.struct_or_union_specifier = sou_spec;
    return t;
}
ast_token *ast_struct_or_union(struct_or_union *sou) {
    ast_token *t = malloc(sizeof(struct_or_union));
    t->e = struct_or_union_ast_e;
    t->p.sou = sou;
    return t;
}
ast_token *ast_struct_declaration(struct_declaration *struct_decl) {
    ast_token *t = malloc(sizeof(struct_declaration));
    t->e = struct_declaration_ast_e;
    t->p.struct_declaration = struct_decl;
    return t;
}
ast_token *ast_struct_declaration_list(struct_declaration_list *struct_decl_list) {
    ast_token *t = malloc(sizeof(struct_declaration_list));
    t->e = struct_declaration_list_ast_e;
    t->p.struct_declaration_list = struct_decl_list;
    return t;
}
ast_token *ast__specifier_qualifier(_specifier_qualifier *_spec_qual) {
    ast_token *t = malloc(sizeof(_specifier_qualifier));
    t->e = _specifier_qualifier_ast_e;
    t->p._specifier_qualifier = _spec_qual;
    return t;
}
ast_token *ast_struct_declarator_list(struct_declarator_list *struct_decl_list) {
    ast_token *t = malloc(sizeof(struct_declarator_list));
    t->e = struct_declarator_list_ast_e;
    t->p.struct_declarator_list = struct_decl_list;
    return t;
}
ast_token *ast_struct_declarator(struct_declarator *struct_decl) {
    ast_token *t = malloc(sizeof(struct_declarator));
    t->e = struct_declarator_ast_e;
    t->p.struct_declarator = struct_decl;
    return t;
}
ast_token *ast_enum_specifier(enum_specifier *enum_spec) {
    ast_token *t = malloc(sizeof(enum_specifier));
    t->e = enum_specifier_ast_e;
    t->p.enum_specifier = enum_spec;
    return t;
}
ast_token *ast_enumerator_list(enumerator_list *enum_list) {
    ast_token *t = malloc(sizeof(enumerator_list));
    t->e = enumerator_list_ast_e;
    t->p.enumerator_list = enum_list;
    return t;
}
ast_token *ast_enumerator(enumerator *e) {
    ast_token *t = malloc(sizeof(enumerator));
    t->e = enumerator_ast_e;
    t->p.enumerator = e;
    return t;
}
ast_token *ast_type_qualifier(type_qualifier *type_qual) {
    ast_token *t = malloc(sizeof(type_qualifier));
    t->e = type_qualifier_ast_e;
    t->p.type_qual = type_qual;
    return t;
}
ast_token *ast_type_qualifier_list(type_qualifier_list *type_qual_list) {
    ast_token *t = malloc(sizeof(type_qualifier_list));
    t->e = type_qualifier_list_ast_e;
    t->p.type_qualifier_list = type_qual_list;
    return t;
}
ast_token *ast_declarator(declarator *decl) {
    ast_token *t = malloc(sizeof(declarator));
    t->e = declarator_ast_e;
    t->p.declarator = decl;
    return t;
}
ast_token *ast_direct_declarator(direct_declarator *direct_decl) {
    ast_token *t = malloc(sizeof(direct_declarator));
    t->e = direct_declarator_ast_e;
    t->p.direct_declarator = direct_decl;
    return t;
}
ast_token *ast_pointer(pointer *ptr) {
    ast_token *t = malloc(sizeof(pointer));
    t->e = pointer_ast_e;
    t->p.pointer = ptr;
    return t;
}
ast_token *ast_parameter_type_list(parameter_type_list *param_type_list) {
    ast_token *t = malloc(sizeof(parameter_type_list));
    t->e = parameter_type_list_ast_e;
    t->p.parameter_type_list = param_type_list;
    return t;
}
ast_token *ast_parameter_list(parameter_list *param_list) {
    ast_token *t = malloc(sizeof(parameter_list));
    t->e = parameter_list_ast_e;
    t->p.parameter_list = param_list;
    return t;
}
ast_token *ast_parameter_declaration(parameter_declaration *param_decl) {
    ast_token *t = malloc(sizeof(parameter_declaration));
    t->e = parameter_declaration_ast_e;
    t->p.parameter_declaration = param_decl;
    return t;
}
ast_token *ast_identifier_list(identifier_list *ident_list) {
    ast_token *t = malloc(sizeof(identifier_list));
    t->e = identifier_list_ast_e;
    t->p.identifier_list = ident_list;
    return t;
}
ast_token *ast_abstract_declarator(abstract_declarator *abstract_decl) {
    ast_token *t = malloc(sizeof(abstract_declarator));
    t->e = abstract_declarator_ast_e;
    t->p.abstract_declarator = abstract_decl;
    return t;
}
ast_token *ast_direct_abstract_declarator(direct_abstract_declarator *direct_abstract_decl) {
    ast_token *t = malloc(sizeof(direct_abstract_declarator));
    t->e = direct_abstract_declarator_ast_e;
    t->p.direct_abstract_declarator = direct_abstract_decl;
    return t;
}
ast_token *ast_initializer(initializer *init) {
    ast_token *t = malloc(sizeof(initializer));
    t->e = initializer_ast_e;
    t->p.initializer = init;
    return t;
}
ast_token *ast_initializer_list(initializer_list *init_list) {
    ast_token *t = malloc(sizeof(initializer_list));
    t->e = initializer_list_ast_e;
    t->p.initializer_list = init_list;
    return t;
}
ast_token *ast_statement(statement *s) {
    ast_token *t = malloc(sizeof(statement));
    t->e = statement_ast_e;
    t->p.statement = s;
    return t;
}
ast_token *ast_labeled_statement(labeled_statement *labeled_s) {
    ast_token *t = malloc(sizeof(labeled_statement));
    t->e = labeled_statement_ast_e;
    t->p.labeled_statement = labeled_s;
    return t;
}
ast_token *ast_compound_statement(compound_statement *cs) {
    ast_token *t = malloc(sizeof(compound_statement));
    t->e = compound_statement_ast_e;
    t->p.compound_statement = cs;
    return t;
}
ast_token *ast_declaration_list(declaration_list *decl_list) {
    ast_token *t = malloc(sizeof(declaration_list));
    t->e = declaration_list_ast_e;
    t->p.declaration_list = decl_list;
    return t;
}
ast_token *ast_statement_list(statement_list *s_list) {
    ast_token *t = malloc(sizeof(statement_list));
    t->e = statement_list_ast_e;
    t->p.statement_list = s_list;
    return t;
}
ast_token *ast_expression_statement(expression_statement *expr_s) {
    ast_token *t = malloc(sizeof(expression_statement));
    t->e = expression_statement_ast_e;
    t->p.expr_statement = expr_s;
    return t;
}
ast_token *ast_selection_statement(selection_statement *selection_s) {
    ast_token *t = malloc(sizeof(selection_statement));
    t->e = selection_statement_ast_e;
    t->p.selection_statement = selection_s;
    return t;
}
ast_token *ast_iteration_statement(iteration_statement *iter_s) {
    ast_token *t = malloc(sizeof(iteration_statement));
    t->e = iteration_statement_ast_e;
    t->p.iteration_statement = iter_s;
    return t;
}
ast_token *ast_jump_statement(jump_statement *jmp_s) {
    ast_token *t = malloc(sizeof(jump_statement));
    t->e = jump_statement_ast_e;
    t->p.jump_statement = jmp_s;
    return t;
}
ast_token *ast_translation_unit(translation_unit *tu) {
    ast_token *t = malloc(sizeof(translation_unit));
    t->e = translation_unit_ast_e;
    t->p.translation_unit = tu;
    return t;
}
ast_token *ast_external_declaration(external_declaration *ed) {
    ast_token *t = malloc(sizeof(external_declaration));
    t->e = external_declaration_ast_e;
    t->p.external_declaration = ed;
    return t;
}
ast_token *ast_function_definition(function_definition *func_def) {
    ast_token *t = malloc(sizeof(function_definition));
    t->e = function_definition_ast_e;
    t->p.function_definition = func_def;
    return t;
}

string ast_token_to_string(ast_token *a) {
    string s;
    switch (a->e) {
    case function_definition_ast_e:
    case expression_ast_e:
    case primary_expression_ast_e:
    case postfix_expression_ast_e:
    case assignment_expression_ast_e:
    case argument_expression_list_ast_e:
    case unary_expression_ast_e:
    case unary_operator_ast_e:
    case cast_expression_ast_e:
    case multiplicative_expression_ast_e:
    case additive_expression_ast_e:
    case shift_expression_ast_e:
    case relational_expression_ast_e:
    case equality_expression_ast_e:
    case and_expression_ast_e:
    case exclusive_or_expression_ast_e:
    case inclusive_or_expression_ast_e:
    case logical_and_expression_ast_e:
    case logical_or_expression_ast_e:
    case conditional_expression_ast_e:
    case assignment_operator_ast_e:
    case constant_expression_ast_e:
    case declaration_ast_e:
    case declaration_specifiers_ast_e:
    case init_declarator_ast_e:
    case init_declarator_list_ast_e:
    case storage_class_specifier_ast_e:
    case type_specifier_ast_e:
    case struct_or_union_specifier_ast_e:
    case struct_or_union_ast_e:
    case struct_declaration_ast_e:
    case struct_declaration_list_ast_e:
    case _specifier_qualifier_ast_e:
    case struct_declarator_list_ast_e:
    case struct_declarator_ast_e:
    case enum_specifier_ast_e:
    case enumerator_list_ast_e:
    case enumerator_ast_e:
    case type_qualifier_ast_e:
    case type_qualifier_list_ast_e:
    case declarator_ast_e:
    case direct_declarator_ast_e:
    case pointer_ast_e:
    case parameter_type_list_ast_e:
    case parameter_list_ast_e:
    case parameter_declaration_ast_e:
    case identifier_list_ast_e:
    case abstract_declarator_ast_e:
    case direct_abstract_declarator_ast_e:
    case initializer_ast_e:
    case initializer_list_ast_e:
    case statement_ast_e:
    case labeled_statement_ast_e:
    case compound_statement_ast_e:
    case declaration_list_ast_e:
    case statement_list_ast_e:
    case expression_statement_ast_e:
    case selection_statement_ast_e:
    case iteration_statement_ast_e:
    case jump_statement_ast_e:
    case translation_unit_ast_e:
    case external_declaration_ast_e:
        printf("ast_tok_to_string unimplemented");
        exit(EXIT_FAILURE);
    }
    return s;
}
