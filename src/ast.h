#ifndef AST_H
#define AST_H

#include "ll.h"
#include "string.h"
#include "token.h"
#include "util.h"
#include "vector.h"
#include <stdlib.h>

struct primary_expression;
struct postfix_expression;
struct postfix_expression_term;
struct assignment_expression;
struct unary_expression;
typedef enum unary_operator {
    and_uo_e,
    star_uo_e,
    plus_uo_e,
    minus_uo_e,
    approx_uo_e,
    bang_uo_e
} unary_operator;
bool unary_operator_eq(unary_operator self, unary_operator other);
struct cast_expression;
struct multiplicative_expression;
struct multiplicative_expression_post;
struct additive_expression;
struct additive_expression_post;
struct shift_expression;
struct shift_expression_post;
struct relational_expression;
struct relational_expression_post;
struct equality_expression;
struct equality_expression_post;
struct and_expression;
struct exclusive_or_expression;
struct inclusive_or_expression;
struct logical_and_expression;
struct logical_or_expression;
struct conditional_expression;
typedef enum assignment_operator {
    eq_ao_e,
    muleq_ao_e,
    diveq_ao_e,
    percenteq_ao_e,
    pluseq_ao_e,
    minuseq_ao_e,
    shiftleq_ao_e,
    shiftreq_ao_e,
    andeq_ao_e,
    xoreq_ao_e,
    oreq_ao_e
} assignment_operator;
bool assignment_operator_eq(const assignment_operator *self, const assignment_operator *other);
struct declaration;
struct init_declarator;
typedef enum storage_class_specifier {
    typedef_scs_e,
    extern_scs_e,
    static_scs_e,
    auto_scs_e,
    register_scs_e
} storage_class_specifier;
bool storage_class_specifier_eq(const storage_class_specifier *self,
                                const storage_class_specifier *other);
struct type_specifier;
struct struct_or_union_specifier;
typedef enum struct_or_union { struct_sou_e, union_sou_e } struct_or_union;
bool struct_or_union_eq(const struct_or_union *self, const struct_or_union *other);
struct struct_declaration;
struct _specifier_qualifier;
struct struct_declarator;
struct enum_specifier;
struct enumerator;
typedef enum type_qualifier { const_tq_e, volatile_tq_e } type_qualifier;
bool type_qualifier_eq(const type_qualifier *self, const type_qualifier *other);
DECLARE_VECTOR(type_qualifier)
TYPEDEF_VECTOR(type_qualifier, type_qualifier_list)
bool type_qualifier_list_eq(const type_qualifier_list *self, const type_qualifier_list *other);
struct declarator;
struct direct_declarator;
struct pointer;
struct parameter_type_list;
struct parameter_declaration;
struct identifier_list;
struct abstract_declarator;
struct direct_abstract_declarator;
struct initializer;
struct statement;
struct labeled_statement;
struct compound_statement;
struct declaration_list;
struct statement_list;
struct expression_statement;
struct selection_statement;
struct iteration_statement;
struct jump_statement;
struct translation_unit;
struct external_declaration;
struct function_definition;

typedef struct assignment_expression {
    union {
        nonnullable struct conditional_expression *cond_expr_p;
        struct {
            nonnullable struct unary_expression *expr;
            nonnullable assignment_operator *op;
            nonnullable struct assignment_expression *assignment;
        } unary_assignment_p;
    } p;
    enum { cond_expr_ae_e, unary_assignment_ae_e } e;
} assignment_expression;
bool assignment_expression_eq(const assignment_expression *self,
                              const assignment_expression *other);
DECLARE_VECTOR(assignment_expression)
TYPEDEF_VECTOR(assignment_expression, argument_expression_list)
bool argument_expression_list_eq(const argument_expression_list *self,
                                 const argument_expression_list *other);
TYPEDEF_VECTOR(assignment_expression, expression)
bool expression_eq(const expression *self, const expression *other);
typedef struct primary_expression {
    union {
        nonnullable ident *ident;
        nonnullable uint64_t *constant;
        nonnullable string_lit *string_lit;
        nonnullable expression *expr;
    } p;
    enum { ident_pe_e, constant_pe_e, string_lit_pe_e, expr_pe_e } e;
} primary_expression;
bool primary_expression_eq(const primary_expression *self, const primary_expression *other);
typedef struct postfix_expression {
    nonnullable primary_expression *pe;
    nullable struct postfix_expression_term *pet;
} postfix_expression;
bool postfix_expression_eq(const postfix_expression *self, const postfix_expression *other);
typedef struct postfix_expression_term {
    union {
        nonnullable expression *array_idx;
        nonnullable argument_expression_list *function_args;
        nonnullable ident *field_op;
        nonnullable ident *deref_op;
    } p;
    nullable struct postfix_expression_term *pet;
    enum postfix_expression_term_disriminant {
        array_poste_term_e,
        function_poste_term_e,
        field_poste_term_e,
        deref_poste_term_e,
        inc_poste_term_e,
        dec_poste_term_e
    } e;
} postfix_expression_term;
bool postfix_expression_term_eq(const postfix_expression_term *self,
                                const postfix_expression_term *other);
typedef struct cast_expression {
    union {
        struct unary_expression *unary_expr;
        struct {
            struct type_name *ty;
            struct cast_expression *ce;
        } cast;
    } p;
    enum { unary_expr_ce_e, ty_name_ce_e } e;
} cast_expression;
bool cast_expression_eq(const cast_expression *self, const cast_expression *other);
typedef struct multiplicative_expression {
    nonnullable struct cast_expression *cast_expr;
    nullable struct multiplicative_expression_post *post;
} multiplicative_expression;
bool multiplicative_expression_eq(const multiplicative_expression *self,
                                  const multiplicative_expression *other);
typedef struct multiplicative_expression_post {
    nonnullable multiplicative_expression *mul_expr;
    enum { mul_mul_expr_post_e, div_mul_expr_post_e, mod_mul_expr_post_e } e;
} multiplicative_expression_post;
bool multiplicative_expression_post_eq(const multiplicative_expression_post *self,
                                       const multiplicative_expression_post *other);
typedef struct additive_expression {
    struct multiplicative_expression *mul_expr;
    struct additive_expression *add_expr;
    enum { mul_expr_only_ae_e, add_expr_plus_ae_e, add_expr_minus_ae_e } e;
} additive_expression;
bool additive_expression_eq(const additive_expression *self, const additive_expression *other);
typedef struct shift_expression {
    struct additive_expression *add_expr;
    struct shift_expression *sft_expr;
    enum { add_expr_only_ae_e, sft_expr_left_se_e, sft_expr_right_se_e } e;
} shift_expression;
bool shift_expression_eq(const shift_expression *self, const shift_expression *other);
typedef struct relational_expression {
    struct shift_expression *sft_expr;
    struct relational_expression *rel_expr;
    enum {
        sft_expr_only_re_e,
        rel_expr_lt_re_e,
        rel_expr_gt_re_e,
        rel_expr_le_re_e,
        rel_expr_ge_re_e
    } e;
} relational_expression;
bool relational_expression_eq(const relational_expression *self,
                              const relational_expression *other);
typedef struct equality_expression {
    struct relational_expression *rel_expr;
    struct equality_expression *eq_expr;
    enum { rel_expr_only_ee_e, eq_expr_eq_ee_e, eq_expr_ne_ee_e } e;
} equality_expression;
bool equality_expression_eq(const equality_expression *self, const equality_expression *other);
typedef struct and_expression {
    struct equality_expression *eq_expr;
    struct and_expression *and_expr;
} and_expression;
bool and_expression_eq(const and_expression *self, const and_expression *other);
typedef struct exclusive_or_expression {
    struct and_expression *and_expr;
    struct exclusive_or_expression *xor_expr;
} exclusive_or_expression;
bool exclusive_or_expression_eq(const exclusive_or_expression *self,
                                const exclusive_or_expression *other);
typedef struct inclusive_or_expression {
    struct exclusive_or_expression *xor_expr;
    struct inclusive_or_expression *ior_expr;
} inclusive_or_expression;
bool inclusive_or_expression_eq(const inclusive_or_expression *self,
                                const inclusive_or_expression *other);
typedef struct logical_and_expression {
    struct inclusive_or_expression *ior_expr;
    struct logical_and_expression *logand_expr;
} logical_and_expression;
bool logical_and_expression_eq(const logical_and_expression *self,
                               const logical_and_expression *other);
typedef struct logical_or_expression {
    struct logical_and_expression *logand_expr;
    struct logical_or_expression *logor_expr;
} logical_or_expression;
bool logical_or_expression_eq(const logical_or_expression *self,
                              const logical_or_expression *other);
typedef struct conditional_expression {
    struct logical_or_expression *cond;
    expression *ter_que;
    struct conditional_expression *ter_col;
} conditional_expression;
bool conditional_expression_eq(const conditional_expression *self,
                               const conditional_expression *other);
typedef conditional_expression constant_expression;
bool constant_expression_eq(const constant_expression *self, const constant_expression *other);
typedef struct unary_expression {
    union {
        postfix_expression *expr;
        struct unary_expression *unary_expr;
        struct {
            unary_operator unary_op;
            struct cast_expression *cast_expr;
        } cast_expr;
        struct type_name *type_name;
    } p;
    enum unary_expression_discriminant {
        expr_ue_e,
        inc_unary_expr_ue_e,
        dec_unary_expr_ue_e,
        unary_op_cast_expr_ue_e,
        sizeof_unary_expr_ue_e,
        sizeof_type_name_ue_e
    } e;
} unary_expression;
bool unary_expression_eq(const unary_expression *self, const unary_expression *other);
typedef struct init_declarator {
    struct declarator *decl;
    struct initializer *init;
} init_declarator;
bool init_declarator_eq(const init_declarator *self, const init_declarator *other);
DECLARE_VECTOR(init_declarator)
TYPEDEF_VECTOR(init_declarator, init_declarator_list)
bool init_declarator_list_eq(const init_declarator_list *self, const init_declarator_list *other);
typedef struct type_specifier {
    union {
        struct struct_or_union_specifier *sou_spec;
        struct enum_specifier *enum_spec;
        ident *type_name;
    } p;
    enum {
        void_ts_e,
        char_ts_e,
        short_ts_e,
        int_ts_e,
        long_ts_e,
        float_ts_e,
        double_ts_e,
        signed_ts_e,
        unsigned_ts_e,
        struct_or_union_specifier_ts_e,
        enum_specifier_ts_e,
        type_name_ts_e
    } e;
} type_specifier;
bool type_specifier_eq(const type_specifier *self, const type_specifier *other);
typedef struct struct_declarator {
    struct declarator *decl;
    constant_expression *const_expr;
} struct_declarator;
bool struct_declarator_eq(const struct_declarator *self, const struct_declarator *other);
DECLARE_VECTOR(struct_declarator)
TYPEDEF_VECTOR(struct_declarator, struct_declarator_list)
bool struct_declarator_list_eq(const struct_declarator_list *self,
                               const struct_declarator_list *other);
typedef struct struct_or_union_specifier {
    struct_declarator_list *fields;
    ident *ident;
    struct_or_union *sou;
} struct_or_union_specifier;
bool struct_or_union_specifier_eq(const struct_or_union_specifier *self,
                                  const struct_or_union_specifier *other);
typedef struct _specifier_qualifier {
    union {
        struct type_specifier *specifier;
        enum type_qualifier *qualifier;
    } p;
    enum { type_specifier_sq_e, type_qualifier_sq_e } e;
} _specifier_qualifier;
bool _specifier_qualifier_eq(const _specifier_qualifier *self, const _specifier_qualifier *other);
DECLARE_VECTOR(_specifier_qualifier)
TYPEDEF_VECTOR(_specifier_qualifier, specifier_qualifier_list)
typedef struct struct_declaration {
    specifier_qualifier_list *specs;
    struct_declarator_list *body;
} struct_declaration;
bool struct_declaration_eq(const struct_declaration *self, const struct_declaration *other);
DECLARE_VECTOR(struct_declaration)
TYPEDEF_VECTOR(struct_declaration, struct_declaration_list)
bool struct_declaration_list_eq(const struct_declaration_list *self,
                                const struct_declaration_list *other);
typedef struct enumerator {
    ident *ident;
    constant_expression *const_expr;
} enumerator;
bool enumerator_eq(const enumerator *self, const enumerator *other);
DECLARE_VECTOR(enumerator)
TYPEDEF_VECTOR(enumerator, enumerator_list)
bool enumerator_list_eq(const enumerator_list *self, const enumerator_list *other);
typedef struct enum_specifier {
    ident *ident;
    enumerator_list *enumerator;
} enum_specifier;
bool enum_specifier_eq(const enum_specifier *self, const enum_specifier *other);
typedef struct declarator {
    struct direct_declarator *direct_decl;
    struct pointer *ptr;
} declarator;
bool declarator_eq(const declarator *self, const declarator *other);
DECLARE_VECTOR(ident)
TYPEDEF_VECTOR(ident, identifier_list)
bool identifier_list_eq(const identifier_list *self, const identifier_list *other);
typedef struct direct_declarator {
    union {
        ident *ident;
        struct declarator *decl;
        struct {
            struct direct_declarator *dd;
            enum {
                const_expr_bracket_ddt_e,
                empty_bracket_ddt_e,
                parameter_list_paren_ddt_e,
                ident_list_paren_ddt_e,
                empty_paren_ddt_e
            } dd_type;
            union {
                constant_expression *bracket;
                struct parameter_type_list *params;
                identifier_list *idents;
            } post;
        } dd;
    } p;
    enum { ident_dd_e, decl_dd_e, dd_dd_e } e;
} direct_declarator;
bool direct_declarator_eq(const direct_declarator *self, const direct_declarator *other);
typedef struct pointer {
    type_qualifier_list *tql;
    struct pointer *ptr;
} pointer;
bool pointer_eq(const pointer *self, const pointer *other);
typedef struct declaration_specifier {
    union {
        enum storage_class_specifier *scs;
        struct type_specifier *specifier;
        enum type_qualifier *qualifier;
    } p;
    enum { scs_ds_e, type_specifier_ds_e, type_qualifier_ds_e } e;
} declaration_specifier;
bool declaration_specifier_eq(const declaration_specifier *self,
                              const declaration_specifier *other);
DECLARE_VECTOR(declaration_specifier)
TYPEDEF_VECTOR(declaration_specifier, declaration_specifiers)
bool declaration_specifiers_eq(const declaration_specifiers *self,
                               const declaration_specifiers *other);
typedef struct parameter_declaration {
    declaration_specifiers *decl_specs;
    union {
        struct declarator *decl;
        struct abstract_declarator *abstract_declarator;
    } p;
    enum { none_pd_e, decl_pd_e, abstract_decl_pd_e } e;
} parameter_declaration;
bool parameter_declaration_eq(const parameter_declaration *self,
                              const parameter_declaration *other);
DECLARE_VECTOR(parameter_declaration)
TYPEDEF_VECTOR(parameter_declaration, parameter_list)
bool parameter_list_eq(const parameter_list *self, const parameter_list *other);
typedef struct parameter_type_list {
    parameter_list *params;
    bool ellipsis;
} parameter_type_list;
bool parameter_type_list_eq(const parameter_type_list *self, const parameter_type_list *other);
typedef struct type_name {
    nonnullable specifier_qualifier_list *sql;
    nullable struct abstract_declarator *abstract_decl;
} type_name;
bool type_name_eq(const type_name *self, const type_name *other);
typedef struct abstract_declarator {
    nullable struct pointer *ptr;
    nullable struct direct_abstract_declarator *direct_abstract_decl;
} abstract_declarator;
bool abstract_declarator_eq(const abstract_declarator *self, const abstract_declarator *other);
typedef struct direct_abstract_declarator {
    union {
        struct abstract_declarator *paren_dad;
        constant_expression *bracket_dad;
        struct parameter_type_list *paren_list;
    } p;
    enum {
        paren_ad_dad_e,
        empty_bracket_dad_e,
        const_expr_bracket_dad_e,
        empty_paren_dad_e,
        paren_paramater_type_list_dad_e
    } e;
    nullable struct direct_abstract_delcarator_term *dad_t;
} direct_abstract_declarator;
bool direct_abstract_declarator_eq(const direct_abstract_declarator *self,
                                   const direct_abstract_declarator *other);
typedef struct direct_abstract_delcarator_term {
    union {
        nullable constant_expression *const_expr;
        nullable parameter_type_list *ptl;
    } p;
    enum { const_expr_dad_e, ptl_dad_e } e;
    nullable struct direct_abstract_delcarator_term *dad_t;
} direct_abstract_declarator_term;
bool direct_abstract_declarator_term_eq(const direct_abstract_declarator_term *self,
                                        const direct_abstract_declarator_term *other);
typedef struct initializer {
    union {
        struct assignment_expression *assignment;
        struct vector_initializer /* initializer_list */ *init_list;
    } p;
    enum { assignment_expression_i_e, init_list_i_e } e;
} initializer;
bool initializer_eq(const initializer *self, const initializer *other);
DECLARE_VECTOR(initializer)
TYPEDEF_VECTOR(initializer, initializer_list)
bool initializer_list_eq(const initializer_list *self, const initializer_list *other);
typedef struct statement {
    union {
        struct labeled_statement *label;
        struct compound_statement *compound;
        struct expression_statement *expr;
        struct selection_statement *selection;
        struct iteration_statement *iter;
        struct jump_statement *jump;
    } p;
    enum {
        labeled_statement_s_e,
        compound_statement_s_e,
        expression_statement_s_e,
        selection_statement_s_e,
        iteration_statement_s_e,
        jump_statement_s_e
    } e;
} statement;
bool statement_eq(const statement *self, const statement *other);
DECLARE_VECTOR(statement)
TYPEDEF_VECTOR(statement, statement_list)
bool statement_list_eq(const statement_list *self, const statement_list *other);
typedef struct labeled_statement {
    struct statement *statement;
    union {
        ident *ident;
        constant_expression *case_const_expr;
    } p;
    enum { ident_ls_e, case_ls_e, default_ls_e } e;
} labeled_statement;
bool labeled_statement_eq(const labeled_statement *self, const labeled_statement *other);
typedef struct declaration {
    declaration_specifiers *decl_specs;
    init_declarator_list *decl_list;
} declaration;
bool declaration_eq(const declaration *self, const declaration *other);
DECLARE_VECTOR(declaration)
TYPEDEF_VECTOR(declaration, declaration_list)
bool declaration_list_eq(const declaration_list *self, const declaration_list *other);
typedef struct compound_statement {
    declaration_list *decls;
    statement_list *statements;
} compound_statement;
bool compound_statement_eq(const compound_statement *self, const compound_statement *other);
typedef struct expression_statement {
    nonnullable expression *expr;
} expression_statement;
bool expression_statement_eq(const expression_statement *self, const expression_statement *other);
typedef struct selection_statement {
    nonnullable struct statement *statement;
    nonnullable expression *expr;
    nonnullable struct statement *else_statement;
    enum { if_ss_e, if_else_ss_e, switch_ss_e } e;
} selection_statement;
bool selection_statement_eq(const selection_statement *self, const selection_statement *other);
typedef struct iteration_statement {
    struct statement *body;
    union {
        expression *while_expr;
        struct {
            struct expression_statement *init;
            struct expression_statement *cond;
            expression *post;
        } for_expr;
    } p;
    enum { while_is_e, do_while_is_e, for_is_e } e;
} iteration_statement;
bool iteration_statement_eq(const iteration_statement *self, const iteration_statement *other);
typedef struct jump_statement {
    union {
        ident *goto_ident;
        expression *return_expr;
    } p;
    enum { goto_js_e, continue_js_e, break_js_e, return_js_e, return_expr_js_e } e;
} jump_statement;
bool jump_statement_eq(const jump_statement *self, const jump_statement *other);
typedef struct function_definition {
    declaration_specifiers *decl_specs;
    struct declarator *sig;
    struct compound_statement *body;
} function_definition;
bool function_definition_eq(const function_definition *self, const function_definition *other);
typedef struct external_declaration {
    union {
        struct function_definition *function_def;
        struct declaration *decl;
    } p;
    enum { function_def_ed_e, decl_ed_e } e;
} external_declaration;
bool external_declaration_eq(const external_declaration *self, const external_declaration *other);
DECLARE_VECTOR(external_declaration)
TYPEDEF_VECTOR(external_declaration, translation_unit)

typedef struct {
    union {
        expression *expr;
        primary_expression *primary_expr;
        postfix_expression *postfix_expr;
        assignment_expression *assignment_expr;
        argument_expression_list *argument_expr_list;
        unary_expression *unary_expr;
        unary_operator *unary_op;
        cast_expression *cast_expr;
        multiplicative_expression *multiplicative_expr;
        additive_expression *additive_expr;
        shift_expression *shift_expr;
        relational_expression *relational_expr;
        equality_expression *equality_expr;
        and_expression *and_expr;
        exclusive_or_expression *exclusive_or_expr;
        inclusive_or_expression *inclusive_or_expr;
        logical_and_expression *logical_and_expr;
        logical_or_expression *logical_or_expr;
        conditional_expression *conditional_expr;
        assignment_operator *assignment_op;
        constant_expression *constant_expr;
        declaration *declaration;
        declaration_specifiers *declaration_specifiers;
        init_declarator *init_declarator;
        init_declarator_list *init_declarator_list;
        storage_class_specifier *scs;
        type_specifier *type_specifier;
        struct_or_union_specifier *struct_or_union_specifier;
        struct_or_union *sou;
        struct_declaration *struct_declaration;
        struct_declaration_list *struct_declaration_list;
        _specifier_qualifier *_specifier_qualifier;
        struct_declarator_list *struct_declarator_list;
        struct_declarator *struct_declarator;
        enum_specifier *enum_specifier;
        enumerator_list *enumerator_list;
        enumerator *enumerator;
        type_qualifier *type_qual;
        type_qualifier_list *type_qual_list;
        declarator *declarator;
        direct_declarator *direct_declarator;
        pointer *pointer;
        type_qualifier_list *type_qualifier_list;
        parameter_type_list *parameter_type_list;
        parameter_list *parameter_list;
        parameter_declaration *parameter_declaration;
        identifier_list *identifier_list;
        abstract_declarator *abstract_declarator;
        direct_abstract_declarator *direct_abstract_declarator;
        initializer *initializer;
        initializer_list *initializer_list;
        statement *statement;
        labeled_statement *labeled_statement;
        compound_statement *compound_statement;
        declaration_list *declaration_list;
        statement_list *statement_list;
        expression_statement *expr_statement;
        selection_statement *selection_statement;
        iteration_statement *iteration_statement;
        jump_statement *jump_statement;
        translation_unit *translation_unit;
        external_declaration *external_declaration;
        function_definition *function_definition;
    } p;
    enum {
        expression_ast_e,
        primary_expression_ast_e,
        postfix_expression_ast_e,
        assignment_expression_ast_e,
        argument_expression_list_ast_e,
        unary_expression_ast_e,
        unary_operator_ast_e,
        cast_expression_ast_e,
        multiplicative_expression_ast_e,
        additive_expression_ast_e,
        shift_expression_ast_e,
        relational_expression_ast_e,
        equality_expression_ast_e,
        and_expression_ast_e,
        exclusive_or_expression_ast_e,
        inclusive_or_expression_ast_e,
        logical_and_expression_ast_e,
        logical_or_expression_ast_e,
        conditional_expression_ast_e,
        assignment_operator_ast_e,
        constant_expression_ast_e,
        declaration_ast_e,
        declaration_specifiers_ast_e,
        init_declarator_ast_e,
        init_declarator_list_ast_e,
        storage_class_specifier_ast_e,
        type_specifier_ast_e,
        struct_or_union_specifier_ast_e,
        struct_or_union_ast_e,
        struct_declaration_ast_e,
        struct_declaration_list_ast_e,
        _specifier_qualifier_ast_e,
        struct_declarator_list_ast_e,
        struct_declarator_ast_e,
        enum_specifier_ast_e,
        enumerator_list_ast_e,
        enumerator_ast_e,
        type_qualifier_ast_e,
        type_qualifier_list_ast_e,
        declarator_ast_e,
        direct_declarator_ast_e,
        pointer_ast_e,
        parameter_type_list_ast_e,
        parameter_list_ast_e,
        parameter_declaration_ast_e,
        identifier_list_ast_e,
        abstract_declarator_ast_e,
        direct_abstract_declarator_ast_e,
        initializer_ast_e,
        initializer_list_ast_e,
        statement_ast_e,
        labeled_statement_ast_e,
        compound_statement_ast_e,
        declaration_list_ast_e,
        statement_list_ast_e,
        expression_statement_ast_e,
        selection_statement_ast_e,
        iteration_statement_ast_e,
        jump_statement_ast_e,
        translation_unit_ast_e,
        external_declaration_ast_e,
        function_definition_ast_e
    } e;
} ast_token;

// Small helper functions to convert an explicit language construct to an AST token
ast_token *ast_expression(expression *expr);
ast_token *ast_primary_expression(primary_expression *primary_expr);
ast_token *ast_postfix_expression(postfix_expression *postfix_expr);
ast_token *ast_assignment_expression(assignment_expression *assignment_expr);
ast_token *ast_argument_expression_list(argument_expression_list *argument_expr_list);
ast_token *ast_unary_expression(unary_expression *unary_expr);
ast_token *ast_unary_operator(unary_operator *unary_op);
ast_token *ast_cast_expression(cast_expression *cast_expr);
ast_token *ast_multiplicative_expression(multiplicative_expression *multiplicative_expr);
ast_token *ast_additive_expression(additive_expression *additive_expr);
ast_token *ast_shift_expression(shift_expression *shift_expr);
ast_token *ast_relational_expression(relational_expression *relational_expr);
ast_token *ast_equality_expression(equality_expression *equality_expr);
ast_token *ast_and_expression(and_expression *and_expr);
ast_token *ast_exclusive_or_expression(exclusive_or_expression *exclusive_or_expr);
ast_token *ast_inclusive_or_expression(inclusive_or_expression *inclusive_or_expr);
ast_token *ast_logical_and_expression(logical_and_expression *logical_and_expr);
ast_token *ast_logical_or_expression(logical_or_expression *logical_or_expr);
ast_token *ast_conditional_expression(conditional_expression *conditional_expr);
ast_token *ast_assignment_operator(assignment_operator *assignment_op);
ast_token *ast_constant_expression(constant_expression *constant_expr);
ast_token *ast_declaration(declaration *decl);
ast_token *ast_declaration_specifiers(declaration_specifiers *decl_specs);
ast_token *ast_init_declarator(init_declarator *init_decl);
ast_token *ast_init_declarator_list(init_declarator_list *init_decl_list);
ast_token *ast_storage_class_specifier(storage_class_specifier *scs);
ast_token *ast_type_specifier(type_specifier *type_spec);
ast_token *ast_struct_or_union_specifier(struct_or_union_specifier *sou_spec);
ast_token *ast_struct_or_union(struct_or_union *sou);
ast_token *ast_struct_declaration(struct_declaration *struct_decl);
ast_token *ast_struct_declaration_list(struct_declaration_list *struct_decl_list);
ast_token *ast__specifier_qualifier(_specifier_qualifier *_spec_qual);
ast_token *ast_struct_declarator_list(struct_declarator_list *struct_decl_list);
ast_token *ast_struct_declarator(struct_declarator *struct_decl);
ast_token *ast_enum_specifier(enum_specifier *enum_spec);
ast_token *ast_enumerator_list(enumerator_list *enum_list);
ast_token *ast_enumerator(enumerator *e);
ast_token *ast_type_qualifier(type_qualifier *type_qual);
ast_token *ast_type_qualifier_list(type_qualifier_list *type_qual_list);
ast_token *ast_declarator(declarator *decl);
ast_token *ast_direct_declarator(direct_declarator *direct_decl);
ast_token *ast_pointer(pointer *ptr);
ast_token *ast_parameter_type_list(parameter_type_list *param_type_list);
ast_token *ast_parameter_list(parameter_list *param_list);
ast_token *ast_parameter_declaration(parameter_declaration *param_decl);
ast_token *ast_identifier_list(identifier_list *ident_list);
ast_token *ast_abstract_declarator(abstract_declarator *abstract_decl);
ast_token *ast_direct_abstract_declarator(direct_abstract_declarator *direct_abstract_decl);
ast_token *ast_initializer(initializer *init);
ast_token *ast_initializer_list(initializer_list *init_list);
ast_token *ast_statement(statement *s);
ast_token *ast_labeled_statement(labeled_statement *labeled_s);
ast_token *ast_compound_statement(compound_statement *cs);
ast_token *ast_declaration_list(declaration_list *decl_list);
ast_token *ast_statement_list(statement_list *s_list);
ast_token *ast_expression_statement(expression_statement *expr_s);
ast_token *ast_selection_statement(selection_statement *selection_s);
ast_token *ast_iteration_statement(iteration_statement *iter_s);
ast_token *ast_jump_statement(jump_statement *jmp_s);
ast_token *ast_translation_unit(translation_unit *tu);
ast_token *ast_external_declaration(external_declaration *ed);
ast_token *ast_function_definition(function_definition *func_def);

DECLARE_LINKED_LIST(ast_token)

string ast_token_to_string(ast_token *a);

#endif
