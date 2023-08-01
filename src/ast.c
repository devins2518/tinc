#include "ast.h"
#include "string.h"

#include <stdio.h>
#include <stdlib.h>

#define IMPL_VECTOR_EQ(list, base)                                                                 \
    bool list##_eq(const list *self, const list *other) {                                          \
        uint64_t i;                                                                                \
        bool ret = true;                                                                           \
        if (!self || !other || self->len != other->len)                                            \
            return false;                                                                          \
        for (i = 0; ret && i < self->len; i++) {                                                   \
            ret = base##_eq(&list##_get_inner(self)[i], &list##_get_inner(other)[i]);              \
        }                                                                                          \
        return ret;                                                                                \
    }

IMPL_VECTOR(type_qualifier)
IMPL_TYPEDEF_VECTOR(type_qualifier, type_qualifier_list)
IMPL_VECTOR_EQ(type_qualifier_list, type_qualifier)
IMPL_VECTOR(assignment_expression)
IMPL_TYPEDEF_VECTOR(assignment_expression, argument_expression_list)
IMPL_VECTOR_EQ(argument_expression_list, assignment_expression)
IMPL_TYPEDEF_VECTOR(assignment_expression, expression)
IMPL_VECTOR_EQ(expression, assignment_expression)
IMPL_VECTOR(init_declarator)
IMPL_TYPEDEF_VECTOR(init_declarator, init_declarator_list)
IMPL_VECTOR_EQ(init_declarator_list, init_declarator)
IMPL_VECTOR(struct_declaration)
IMPL_TYPEDEF_VECTOR(struct_declaration, struct_declaration_list)
IMPL_VECTOR_EQ(struct_declaration_list, struct_declaration)
IMPL_VECTOR(_specifier_qualifier)
IMPL_TYPEDEF_VECTOR(_specifier_qualifier, specifier_qualifier_list)
IMPL_VECTOR_EQ(specifier_qualifier_list, _specifier_qualifier)
IMPL_VECTOR(struct_declarator)
IMPL_TYPEDEF_VECTOR(struct_declarator, struct_declarator_list)
IMPL_VECTOR_EQ(struct_declarator_list, struct_declarator)
IMPL_VECTOR(enumerator)
IMPL_TYPEDEF_VECTOR(enumerator, enumerator_list)
IMPL_VECTOR_EQ(enumerator_list, enumerator)
IMPL_VECTOR(parameter_declaration)
IMPL_TYPEDEF_VECTOR(parameter_declaration, parameter_list)
IMPL_VECTOR_EQ(parameter_list, parameter_declaration)
IMPL_VECTOR(ident)
IMPL_TYPEDEF_VECTOR(ident, identifier_list)
IMPL_VECTOR_EQ(identifier_list, ident)
IMPL_VECTOR(initializer)
IMPL_TYPEDEF_VECTOR(initializer, initializer_list)
IMPL_VECTOR_EQ(initializer_list, initializer)
IMPL_VECTOR(statement)
IMPL_TYPEDEF_VECTOR(statement, statement_list)
IMPL_VECTOR_EQ(statement_list, statement)
IMPL_VECTOR(declaration)
IMPL_TYPEDEF_VECTOR(declaration, declaration_list)
IMPL_VECTOR_EQ(declaration_list, declaration)
IMPL_VECTOR(declaration_specifier)
IMPL_TYPEDEF_VECTOR(declaration_specifier, declaration_specifiers)
IMPL_VECTOR_EQ(declaration_specifiers, declaration_specifier)
IMPL_VECTOR(external_declaration)
IMPL_TYPEDEF_VECTOR(external_declaration, translation_unit)
IMPL_VECTOR_EQ(translation_unit, external_declaration)
IMPL_LINKED_LIST(ast_token)

bool type_specifier_eq(const type_specifier *self, const type_specifier *other) {
    return self->e == other->e &&
           ((self->e == void_ts_e || self->e == char_ts_e || self->e == short_ts_e ||
             self->e == int_ts_e || self->e == long_ts_e || self->e == float_ts_e ||
             self->e == double_ts_e || self->e == signed_ts_e || self->e == unsigned_ts_e) ||
            (self->e == struct_or_union_specifier_ts_e &&
             struct_or_union_specifier_eq(self->p.sou_spec, other->p.sou_spec)) ||
            (self->e == enum_specifier_ts_e &&
             enum_specifier_eq(self->p.enum_spec, other->p.enum_spec)) ||
            (self->e == type_name_ts_e && ident_eq(self->p.type_name, other->p.type_name)));
}
bool enum_specifier_eq(const enum_specifier *self, const enum_specifier *other) {
    return ((!self->ident && !other->ident) || ident_eq(self->ident, other->ident)) &&
           ((!self->enumerator && !other->enumerator) ||
            enumerator_list_eq(self->enumerator, other->enumerator));
}
bool enumerator_eq(const enumerator *self, const enumerator *other) {
    return ident_eq(self->ident, other->ident) &&
           (!self->const_expr || constant_expression_eq(self->const_expr, other->const_expr));
}
bool constant_expression_eq(const constant_expression *self, const constant_expression *other) {
    return conditional_expression_eq(self, other);
}
bool struct_or_union_specifier_eq(const struct_or_union_specifier *self,
                                  const struct_or_union_specifier *other) {
    return (!self->fields || struct_declarator_list_eq(self->fields, other->fields)) &&
           (!self->ident || ident_eq(self->ident, other->ident)) &&
           struct_or_union_eq(self->sou, other->sou);
}
bool struct_or_union_eq(const struct_or_union *self, const struct_or_union *other) {
    return *self == *other;
}
bool struct_declarator_eq(const struct_declarator *self, const struct_declarator *other) {
    return (!self->decl || declarator_eq(self->decl, other->decl)) &&
           (!self->const_expr || constant_expression_eq(self->const_expr, other->const_expr));
}
bool declarator_eq(const declarator *self, const declarator *other) {
    return (!self->ptr || pointer_eq(self->ptr, other->ptr)) &&
           direct_declarator_eq(self->direct_decl, other->direct_decl);
}
bool pointer_eq(const pointer *self, const pointer *other) {
    return (!self->tql || type_qualifier_list_eq(self->tql, other->tql)) &&
           (!self->ptr || pointer_eq(self->ptr, other->ptr));
}
bool type_qualifier_eq(const type_qualifier *self, const type_qualifier *other) {
    return *self == *other;
}
bool direct_declarator_eq(const direct_declarator *self, const direct_declarator *other) {
    return self->e == other->e &&
           ((self->e == ident_dd_e && ident_eq(self->p.ident, other->p.ident)) ||
            (self->e == decl_dd_e && declarator_eq(self->p.decl, other->p.decl)) ||
            (self->e == dd_dd_e && direct_declarator_eq(self->p.dd.dd, other->p.dd.dd) &&
             (self->p.dd.dd_type == other->p.dd.dd_type &&
              ((self->p.dd.dd_type == const_expr_bracket_ddt_e &&
                constant_expression_eq(self->p.dd.post.bracket, other->p.dd.post.bracket)) ||
               (self->p.dd.dd_type == parameter_list_paren_ddt_e &&
                parameter_type_list_eq(self->p.dd.post.params, other->p.dd.post.params)) ||
               (self->p.dd.dd_type == ident_list_paren_ddt_e &&
                identifier_list_eq(self->p.dd.post.idents, other->p.dd.post.idents))))));
}
bool parameter_type_list_eq(const parameter_type_list *self, const parameter_type_list *other) {
    return parameter_list_eq(self->params, other->params) && self->ellipsis == other->ellipsis;
}
bool parameter_declaration_eq(const parameter_declaration *self,
                              const parameter_declaration *other) {
    return self->e == other->e && declaration_specifiers_eq(self->decl_specs, other->decl_specs) &&
           ((self->e == decl_pd_e && declarator_eq(self->p.decl, other->p.decl)) ||
            (self->e == abstract_decl_pd_e &&
             abstract_declarator_eq(self->p.abstract_declarator, other->p.abstract_declarator)));
}
bool abstract_declarator_eq(const abstract_declarator *self, const abstract_declarator *other) {
    return (!self->ptr && !other->ptr && pointer_eq(self->ptr, other->ptr)) &&
           (!self->direct_abstract_decl && !other->direct_abstract_decl &&
            direct_abstract_declarator_eq(self->direct_abstract_decl, other->direct_abstract_decl));
}
bool declaration_specifier_eq(const declaration_specifier *self,
                              const declaration_specifier *other) {
    return self->e == other->e &&
           ((self->e == scs_ds_e && storage_class_specifier_eq(self->p.scs, other->p.scs)) ||
            (self->e == type_specifier_ds_e &&
             type_specifier_eq(self->p.specifier, other->p.specifier)) ||
            (self->e == type_qualifier_ds_e &&
             type_qualifier_eq(self->p.qualifier, other->p.qualifier)));
}
bool storage_class_specifier_eq(const storage_class_specifier *self,
                                const storage_class_specifier *other) {
    return *self == *other;
}
bool direct_abstract_declarator_eq(const direct_abstract_declarator *self,
                                   const direct_abstract_declarator *other) {
    return self->e == other->e &&
           ((self->e == paren_ad_dad_e &&
             abstract_declarator_eq(self->p.paren_dad, other->p.paren_dad)) ||
            (self->e == const_expr_bracket_dad_e &&
             constant_expression_eq(self->p.bracket_dad, other->p.bracket_dad)) ||
            (self->e == paren_paramater_type_list_dad_e &&
             parameter_type_list_eq(self->p.paren_list, other->p.paren_list))) &&
           (!self->dad_t || direct_abstract_declarator_term_eq(self->dad_t, other->dad_t));
}
bool direct_abstract_declarator_term_eq(const direct_abstract_declarator_term *self,
                                        const direct_abstract_declarator_term *other) {
    return self->e == other->e &&
           ((self->e == const_expr_dad_e &&
             constant_expression_eq(self->p.const_expr, other->p.const_expr)) ||
            (self->e == ptl_dad_e && parameter_type_list_eq(self->p.ptl, other->p.ptl))) &&
           ((!self->dad_t && !other->dad_t) ||
            direct_abstract_declarator_term_eq(self->dad_t, other->dad_t));
}
bool conditional_expression_eq(const conditional_expression *self,
                               const conditional_expression *other) {
    return logical_or_expression_eq(self->cond, other->cond) &&
           ((!self->ter_que && !self->ter_col) ||
            (expression_eq(self->ter_que, other->ter_que) &&
             conditional_expression_eq(self->ter_col, other->ter_col)));
}
bool logical_or_expression_eq(const logical_or_expression *self,
                              const logical_or_expression *other) {
    return logical_and_expression_eq(self->logand_expr, other->logand_expr) &&
           (!self->logor_expr || logical_or_expression_eq(self->logor_expr, other->logor_expr));
}
bool logical_and_expression_eq(const logical_and_expression *self,
                               const logical_and_expression *other) {
    return inclusive_or_expression_eq(self->ior_expr, other->ior_expr) &&
           (!self->logand_expr || logical_and_expression_eq(self->logand_expr, other->logand_expr));
}
bool inclusive_or_expression_eq(const inclusive_or_expression *self,
                                const inclusive_or_expression *other) {
    return exclusive_or_expression_eq(self->xor_expr, other->xor_expr) &&
           (!self->ior_expr || inclusive_or_expression_eq(self->ior_expr, other->ior_expr));
}
bool exclusive_or_expression_eq(const exclusive_or_expression *self,
                                const exclusive_or_expression *other) {
    return and_expression_eq(self->and_expr, other->and_expr) &&
           (!self->xor_expr || exclusive_or_expression_eq(self->xor_expr, other->xor_expr));
}
bool and_expression_eq(const and_expression *self, const and_expression *other) {
    return equality_expression_eq(self->eq_expr, other->eq_expr) &&
           (!self->and_expr || and_expression_eq(self->and_expr, other->and_expr));
}
bool equality_expression_eq(const equality_expression *self, const equality_expression *other) {
    return self->e == other->e && relational_expression_eq(self->rel_expr, other->rel_expr) &&
           (self->e == rel_expr_only_ee_e || equality_expression_eq(self->eq_expr, other->eq_expr));
}
bool relational_expression_eq(const relational_expression *self,
                              const relational_expression *other) {
    return self->e == other->e && shift_expression_eq(self->sft_expr, other->sft_expr) &&
           (self->e == sft_expr_only_re_e ||
            relational_expression_eq(self->rel_expr, other->rel_expr));
}
bool shift_expression_eq(const shift_expression *self, const shift_expression *other) {
    return self->e == other->e && additive_expression_eq(self->add_expr, other->add_expr) &&
           (self->e == add_expr_only_ae_e || shift_expression_eq(self->sft_expr, other->sft_expr));
}
bool additive_expression_eq(const additive_expression *self, const additive_expression *other) {
    return self->e == other->e && multiplicative_expression_eq(self->mul_expr, other->mul_expr) &&
           (self->e == mul_expr_only_ae_e ||
            additive_expression_eq(self->add_expr, other->add_expr));
}
bool multiplicative_expression_eq(const multiplicative_expression *self,
                                  const multiplicative_expression *other) {
    return cast_expression_eq(self->cast_expr, other->cast_expr) &&
           (!self->post || multiplicative_expression_post_eq(self->post, other->post));
}
bool multiplicative_expression_post_eq(const multiplicative_expression_post *self,
                                       const multiplicative_expression_post *other) {
    return self->e == other->e && multiplicative_expression_eq(self->mul_expr, other->mul_expr);
}
bool cast_expression_eq(const cast_expression *self, const cast_expression *other) {
    return self->e == other->e &&
           ((self->e == unary_expr_ce_e &&
             unary_expression_eq(self->p.unary_expr, other->p.unary_expr)) ||
            (self->e == ty_name_ce_e && type_name_eq(self->p.cast.ty, other->p.cast.ty) &&
             cast_expression_eq(self->p.cast.ce, other->p.cast.ce)));
}
bool unary_expression_eq(const unary_expression *self, const unary_expression *other) {
    return self->e == other->e &&
           ((self->e == expr_ue_e && postfix_expression_eq(self->p.expr, other->p.expr)) ||
            ((self->e == inc_unary_expr_ue_e || self->e == dec_unary_expr_ue_e ||
              self->e == sizeof_unary_expr_ue_e) &&
             unary_expression_eq(self->p.unary_expr, other->p.unary_expr)) ||
            (self->e == unary_op_cast_expr_ue_e &&
             unary_operator_eq(self->p.cast_expr.unary_op, other->p.cast_expr.unary_op) &&
             cast_expression_eq(self->p.cast_expr.cast_expr, other->p.cast_expr.cast_expr)) ||
            (self->e == sizeof_type_name_ue_e &&
             type_name_eq(self->p.type_name, other->p.type_name)));
}
bool postfix_expression_eq(const postfix_expression *self, const postfix_expression *other) {
    return primary_expression_eq(self->pe, self->pe) &&
           (!self->pet || postfix_expression_term_eq(self->pet, other->pet));
}
bool postfix_expression_term_eq(const postfix_expression_term *self,
                                const postfix_expression_term *other) {
    return self->e == other->e &&
           (!self->pet || postfix_expression_term_eq(self->pet, other->pet)) &&
           ((self->e == array_poste_term_e &&
             expression_eq(self->p.array_idx, other->p.array_idx)) ||
            (self->e == function_poste_term_e &&
             argument_expression_list_eq(self->p.function_args, other->p.function_args)) ||
            (self->e == field_poste_term_e && ident_eq(self->p.field_op, other->p.field_op)) ||
            (self->e == deref_poste_term_e && ident_eq(self->p.deref_op, other->p.deref_op)) ||
            (self->e == inc_poste_term_e || self->e == dec_poste_term_e));
}
bool primary_expression_eq(const primary_expression *self, const primary_expression *other) {
    return self->e == other->e &&
           ((self->e == ident_pe_e && ident_eq(self->p.ident, other->p.ident)) ||
            (self->e == constant_pe_e && *self->p.constant == *other->p.constant) ||
            (self->e == string_lit_pe_e && ident_eq(self->p.string_lit, other->p.string_lit)) ||
            (self->e == expr_pe_e && expression_eq(self->p.expr, other->p.expr)));
}
bool assignment_expression_eq(const assignment_expression *self,
                              const assignment_expression *other) {
    return self->e == other->e &&
           ((self->e == cond_expr_ae_e &&
             conditional_expression_eq(self->p.cond_expr_p, other->p.cond_expr_p)) ||
            (self->e == unary_assignment_ae_e &&
             (unary_expression_eq(self->p.unary_assignment_p.expr,
                                  other->p.unary_assignment_p.expr) &&
              assignment_operator_eq(self->p.unary_assignment_p.op,
                                     other->p.unary_assignment_p.op) &&
              assignment_expression_eq(self->p.unary_assignment_p.assignment,
                                       other->p.unary_assignment_p.assignment))));
}
bool assignment_operator_eq(const assignment_operator *self, const assignment_operator *other) {
    return *self == *other;
}
bool type_name_eq(const type_name *self, const type_name *other) {
    return specifier_qualifier_list_eq(self->sql, other->sql) &&
           ((!self->abstract_decl && !other->abstract_decl) ||
            abstract_declarator_eq(self->abstract_decl, other->abstract_decl));
}
bool _specifier_qualifier_eq(const _specifier_qualifier *self, const _specifier_qualifier *other) {
    return self->e == other->e && ((self->e == type_specifier_sq_e &&
                                    type_specifier_eq(self->p.specifier, other->p.specifier)) ||
                                   (self->e == type_qualifier_sq_e &&
                                    type_qualifier_eq(self->p.qualifier, other->p.qualifier)));
}
bool unary_operator_eq(unary_operator self, unary_operator other) {
    return self == other;
}
bool declaration_eq(const declaration *self, const declaration *other) {
    return declaration_specifiers_eq(self->decl_specs, other->decl_specs) &&
           ((!self->decl_list && !other->decl_list) ||
            init_declarator_list_eq(self->decl_list, other->decl_list));
}
bool init_declarator_eq(const init_declarator *self, const init_declarator *other) {
    return declarator_eq(self->decl, other->decl) &&
           ((!self->init && !other->init) || initializer_eq(self->init, other->init));
}
bool initializer_eq(const initializer *self, const initializer *other) {
    return self->e == other->e &&
           ((self->e == assignment_expression_i_e &&
             assignment_expression_eq(self->p.assignment, other->p.assignment)) ||
            (self->e == init_list_i_e &&
             initializer_list_eq(self->p.init_list, other->p.init_list)));
}
bool struct_declaration_eq(const struct_declaration *self, const struct_declaration *other) {
    return specifier_qualifier_list_eq(self->specs, other->specs) &&
           struct_declarator_list_eq(self->body, other->body);
}
bool compound_statement_eq(const compound_statement *self, const compound_statement *other) {
    return ((!self->decls && !other->decls) || declaration_list_eq(self->decls, other->decls)) &&
           ((!self->statements && !other->statements) ||
            statement_list_eq(self->statements, other->statements));
}
bool expression_statement_eq(const expression_statement *self, const expression_statement *other) {
    return (!self->expr && !self->expr) || expression_eq(self->expr, other->expr);
}
bool external_declaration_eq(const external_declaration *self, const external_declaration *other) {
    return self->e == other->e &&
           ((self->e == function_def_ed_e &&
             function_definition_eq(self->p.function_def, other->p.function_def)) ||
            (self->e == decl_ed_e && declaration_eq(self->p.decl, other->p.decl)));
}
bool function_definition_eq(const function_definition *self, const function_definition *other) {
    return ((!self->decl_specs && !self->decl_specs) ||
            declaration_specifiers_eq(self->decl_specs, other->decl_specs)) &&
           declarator_eq(self->sig, other->sig) && compound_statement_eq(self->body, other->body);
}
bool statement_eq(const statement *self, const statement *other) {
    return self->e == other->e &&
           ((self->e == labeled_statement_s_e &&
             labeled_statement_eq(self->p.label, other->p.label)) ||
            (self->e == compound_statement_s_e &&
             compound_statement_eq(self->p.compound, other->p.compound)) ||
            (self->e == expression_statement_s_e &&
             expression_statement_eq(self->p.expr, other->p.expr)) ||
            (self->e == selection_statement_s_e &&
             selection_statement_eq(self->p.selection, other->p.selection)) ||
            (self->e == iteration_statement_s_e &&
             iteration_statement_eq(self->p.iter, other->p.iter)) ||
            (self->e == jump_statement_s_e));
}
bool iteration_statement_eq(const iteration_statement *self, const iteration_statement *other) {
    return self->e == other->e && statement_eq(self->body, other->body) &&
           (((self->e == while_is_e || self->e == do_while_is_e) &&
             expression_eq(self->p.while_expr, other->p.while_expr)) ||
            (self->e == for_is_e &&
             expression_statement_eq(self->p.for_expr.init, other->p.for_expr.init) &&
             expression_statement_eq(self->p.for_expr.cond, other->p.for_expr.cond) &&
             (!self->p.for_expr.post ||
              expression_eq(self->p.for_expr.post, other->p.for_expr.post))));
}
bool jump_statement_eq(const jump_statement *self, const jump_statement *other) {
    return self->e == other->e &&
           ((self->e == continue_js_e || self->e == break_js_e || self->e == return_js_e) ||
            (self->e == goto_js_e && ident_eq(self->p.goto_ident, other->p.goto_ident)) ||
            (self->e == return_expr_js_e &&
             expression_eq(self->p.return_expr, other->p.return_expr)));
}
bool labeled_statement_eq(const labeled_statement *self, const labeled_statement *other) {
    return self->e == other->e && statement_eq(self->statement, other->statement) &&
           ((self->e == ident_ls_e && ident_eq(self->p.ident, other->p.ident)) ||
            (self->e == case_ls_e &&
             constant_expression_eq(self->p.case_const_expr, other->p.case_const_expr)) ||
            (self->e == default_ls_e));
}
bool selection_statement_eq(const selection_statement *self, const selection_statement *other) {
    return self->e == other->e && statement_eq(self->statement, other->statement) &&
           expression_eq(self->expr, other->expr) &&
           ((self->e != if_else_ss_e) || statement_eq(self->else_statement, other->else_statement));
}

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
