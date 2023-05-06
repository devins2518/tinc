#ifndef AST_H
#define AST_H

#include "ll.h"
#include "string.h"
#include "token.h"
#include "util.h"
#include "vector.h"
#include <stdlib.h>

struct expression;
struct primary_expression;
struct postfix_expression;
struct assignment_expression;
struct argument_expression_list;
struct unary_expression;
typedef enum unary_operator {
    and_uo_e,
    star_uo_e,
    plus_uo_e,
    minus_uo_e,
    approx_uo_e,
    bang_uo_e
} unary_operator;
struct cast_expression;
struct multiplicative_expression;
struct additive_expression;
struct shift_expression;
struct relational_expression;
struct equality_expression;
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
struct constant_expression;
struct declaration;
struct declaration_specifiers;
struct init_declarator;
struct init_declarator_list;
typedef enum storage_class_specifier {
    typedef_scs_e,
    extern_scs_e,
    static_scs_e,
    auto_scs_e,
    register_scs_e
} storage_class_specifier;
struct type_specifier;
struct struct_or_union_specifier;
typedef enum struct_or_union { struct_sou_e, union_sou_e } struct_or_union;
struct struct_declaration;
struct struct_declaration_list;
struct _specifier_qualifier;
struct struct_declarator_list;
struct struct_declarator;
struct enum_specifier;
struct enumerator_list;
struct enumerator;
typedef enum type_qualifier { const_tq_e, volatile_tq_e } type_qualifier;
DECLARE_VECTOR(type_qualifier)
TYPEDEF_VECTOR(type_qualifier, type_qualifier_list)
struct declarator;
struct direct_declarator;
struct pointer;
struct parameter_type_list;
struct parameter_list;
struct parameter_declaration;
struct identifier_list;
struct abstract_declarator;
struct direct_abstract_declarator;
struct initializer;
struct initializer_list;
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

typedef struct primary_expression {
    union {
        ident ident;
        constant_tk constant;
        string_lit string_lit;
        struct expression *expr;
    } p;
    enum { ident_pe_e, constant_pe_e, string_lit_pe_e, expr_pe_e } e;
} primary_expression;
typedef struct postfix_expression {
    primary_expression *expr;
    union {
        struct expression *array_idx;
        struct argument_expression_list *function_args;
        ident field_op;
        ident deref_op;
    } p;
    enum {
        array_poste_e,
        function_poste_e,
        field_poste_e,
        deref_poste_e,
        inc_poste_e,
        dec_poste_e
    } e;
} postfix_expression;
typedef struct assignment_expression {
    union {
        struct conditional_expression *cond_expr_p;
        struct {
            struct unary_expression *expr;
            assignment_operator *op;
            struct assignment_expression *assignment;
        } unary_assignment_p;
    } p;
    enum { cond_expr_ae_e, unary_assignment_ae_e } e;
} assignment_expression;
DECLARE_VECTOR(assignment_expression)
TYPEDEF_VECTOR(assignment_expression, argument_expression_list)
TYPEDEF_VECTOR(assignment_expression, expression)
typedef struct cast_expression {
    union {
        struct unary_expression *unary_expr;
        struct type_name *ty;
    } p;
    enum { unary_expr_ce_e, ty_name_ce_e } e;
} cast_expression;
typedef struct multiplicative_expression {
    struct cast_expression *cast_expr;
    struct multiplicative_expression *mul_expr;
    enum { cast_expr_only_me_e, mul_expr_mul_me_e, mul_expr_div_me_e, mul_expr_per_me_e } e;
} multiplicative_expression;
typedef struct additive_expression {
    struct multiplicative_expression *mul_expr;
    struct additive_expression *add_expr;
    enum { mul_expr_only_ae_e, add_expr_plus_ae_e, add_expr_minus_ae_e } e;
} additive_expression;
typedef struct shift_expression {
    struct additive_expression *add_expr;
    struct shift_expression *sft_expr;
    enum { add_expr_only_ae_e, sft_expr_left_se_e, sft_expr_right_se_e } e;
} shift_expression;
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
typedef struct equality_expression {
    struct relational_expression *rel_expr;
    struct equality_expression *eq_expr;
    enum { rel_expr_only_ee_e, eq_expr_eq_ee_e, eq_expr_ne_ee_e } e;
} equality_expression;
typedef struct and_expression {
    struct equality_expression *eq_expr;
    struct and_expression *and_expr;
    bool and_present;
} and_expression;
typedef struct exclusive_or_expression {
    struct and_expression *and_expr;
    struct xor_expression *xor_expr;
    bool xor_present;
} exclusive_or_expression;
typedef struct inclusive_or_expression {
    struct xor_expression *xor_expr;
    struct ior_expression *ior_expr;
    bool ior_present;
} inclusive_or_expression;
typedef struct logical_and_expression {
    struct inclusive_or_expression *ior_expr;
    struct logical_and_expression *logand_expr;
    bool logand_present;
} logical_and_expression;
typedef struct logical_or_expression {
    struct logical_and_expression *logand_expr;
    struct logical_or_expression *logor_expr;
    bool logor_present;
} logical_or_expression;
typedef struct conditional_expression {
    struct logical_and_expression *cond;
    struct expression *ter_que;
    struct conditional_expression *ter_col;
    bool ternary_present;
} conditional_expression;
typedef conditional_expression constant_expression;
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
    enum {
        expr_ue_e,
        inc_unary_expr_ue_e,
        dec_unary_expr_ue_e,
        sizeof_unary_expr_ue_e,
        sizeof_type_name_ue_e
    } e;
} unary_expression;
typedef struct init_declarator {
    struct declarator *decl;
    bool initialized;
    struct initializer *init;
} init_declarator;
DECLARE_VECTOR(init_declarator)
TYPEDEF_VECTOR(init_declarator, init_declarator_list)
typedef struct type_specifier {
    union {
        struct struct_or_union_specifier *sou_spec;
        struct enum_specifier *enum_spec;
        ident type_name;
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
typedef struct struct_or_union_specifier {
    bool present;
    struct specifier_qualifier_list *specs;
    struct struct_declarator_list *fields;
} struct_or_union_specifier;
typedef struct struct_declaration {
    struct specifier_qualifier_list *specs;
    struct struct_declarator_list *body;
} struct_declaration;
DECLARE_VECTOR(struct_declaration)
TYPEDEF_VECTOR(struct_declaration, struct_declaration_list)
typedef struct _specifier_qualifier {
    union {
        struct type_specifier *specifier;
        enum type_qualifier *qualifier;
    } p;
    enum { type_specifier_sq_e, type_qualifier_sq_e } e;
} _specifier_qualifier;
DECLARE_VECTOR(_specifier_qualifier)
TYPEDEF_VECTOR(_specifier_qualifier, specifier_qualifier_list)
typedef struct struct_declarator {
    struct declarator *decl;
    struct constant_expression *const_expr;
    enum { decl_only_sd_e, colon_const_expr_sd_e, decl_const_expr_sd_e } e;
} struct_declarator;
DECLARE_VECTOR(struct_declarator)
TYPEDEF_VECTOR(struct_declarator, struct_declarator_list)
typedef struct enum_specifier {
    ident ident;
    bool ident_present;
    struct enumerator_list *enumerator;
    bool enumerator_present;
} enum_specifier;
typedef struct enumerator {
    ident ident;
    struct constant_expression *const_expr;
    bool const_expr_present;
} enumerator;
DECLARE_VECTOR(enumerator)
TYPEDEF_VECTOR(enumerator, enumerator_list)
typedef struct declarator {
    struct direct_declarator *direct_decl;
    struct pointer *ptr;
    bool ptr_present;
} declarator;
typedef struct direct_declarator {
    union {
        ident ident;
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
                struct constant_expression *bracket;
                struct parameter_type_list *params;
                struct identifier_list *idents;
            } post;
        } dd;
    } p;
    enum { ident_dd_e, paren_decl_dd_e, dd_bracket_dd_e, dd_paren_dd_e } e;
} direct_declarator;
typedef struct pointer {
    struct type_qualifier_list *tql;
    struct pointer *ptr;
    enum { empty_ptr_e, tql_ptr_e, ptr_ptr_e, tql_ptr_ptr_e } e;
} pointer;
typedef struct parameter_declaration {
    struct declaration_specifiers *decl_specs;
    union {
        struct declarator *decl;
        struct abstract_declarator *abstract_declarator;
    } p;
    enum { none_pd_e, decl_pd_e, abstract_decl_pd_e } e;
} parameter_declaration;
DECLARE_VECTOR(parameter_declaration)
TYPEDEF_VECTOR(parameter_declaration, parameter_list)
typedef struct parameter_type_list {
    parameter_list params;
    bool ellipsis;
} parameter_type_list;
DECLARE_VECTOR(ident)
TYPEDEF_VECTOR(ident, identifier_list)
typedef struct type_name {
    struct specifier_qualifier_list *sql;
    struct abstract_declarator *abstract_decl;
    bool abstract_decl_present;
} type_name;
typedef struct abstract_declarator {
    struct pointer *ptr;
    bool ptr_present;
    struct direct_abstract_declarator *direct_abstract_decl;
    bool direct_abstract_decl_present;
} abstract_declarator;
typedef struct direct_abstract_declarator {
    union {
        struct abstract_declarator *paren_dad;
        struct constant_expression *bracket_dad;
        struct direct_abstract_declarator *dad_dad;
        struct {
            struct direct_abstract_declarator *dad;
            struct constant_expression *const_expr;
        } dad_const_expr_dad;
        struct parameter_type_list *paren_list;
        struct {
            struct direct_abstract_declarator *dad;
            struct parameter_type_list *paren_list;
        } dad_param_list_dad;
    } p;
    enum {
        paren_ad_dad_e,
        empty_bracket_dad_e,
        const_expr_bracket_dad_e,
        self_empty_bracket_dad_e,
        self_const_expr_bracket_dad_e,
        empty_paren_dad_e,
        paren_paramater_type_list_dad_e,
        self_empty_paren_dad_e,
        self_const_paramater_type_dad_e
    } e;
} direct_abstract_declarator;
typedef struct initializer {
    union {
        struct assignment_expression *assignment;
        struct initializer_list *init_list;
    } p;
    enum { assignment_expression_i_e, init_list_i_e } e;
} initializer;
DECLARE_VECTOR(initializer)
TYPEDEF_VECTOR(initializer, initializer_list)
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
DECLARE_VECTOR(statement)
TYPEDEF_VECTOR(statement, statement_list)
typedef struct labeled_statement {
    struct statement *statement;
    union {
        ident ident;
        struct constant_expression *case_const_expr;
    } p;
    enum { ident_ls_e, case_ls_e, default_ls_e } e;
} labeled_statement;
typedef struct compound_statement {
    struct declaration_list *decls;
    struct statement_list *statements;
} compound_statement;
typedef struct declaration {
    struct declaration_specifiers *decl_specs;
    struct init_declarator_list *decl_list;
    bool decl_list_present;
} declaration;
DECLARE_VECTOR(declaration)
TYPEDEF_VECTOR(declaration, declaration_list)
typedef struct _decl_spec {
    union {
        enum storage_class_specifier *scs;
        struct type_specifier *specifier;
        enum type_qualifier *qualifier;
    } p;
    enum { scs_ds_e, type_specifier_ds_e, type_qualifier_ds_e } e;
} _decl_spec;
DECLARE_VECTOR(_decl_spec)
TYPEDEF_VECTOR(_decl_spec, declaration_specifiers)
typedef struct expression_statement {
    struct expression *expr;
    bool expr_present;
} expression_statement;
typedef struct selection_statement {
    struct statement *statement;
    struct expression *expr;
    struct statement *else_statement;
    bool else_present;
} selection_statement;
typedef struct iteration_statement {
    struct statement *body;
    union {
        struct expression *while_expr;
        struct {
            struct expression_statement *init;
            struct expression_statement *cond;
            struct expression *post;
            bool post_present;
        } for_expr;
    } p;
    enum { while_is_e, do_while_is_e, for_wo_expr_is_e, for_w_expr_is_e } e;
} iteration_statement;
typedef struct jump_statement {
    union {
        ident goto_ident;
        struct expression *return_expr;
    } p;
    enum { goto_js_e, continue_js_e, break_js_e, return_js_e, return_expr_js_e } e;
} jump_statement;
typedef struct function_definition {
    declaration_specifiers *decl_specs;
    bool decl_specs_present;
    declaration_list *decl_list;
    bool decl_list_present;
    struct declarator *sig;
    struct compound_statement *body;
} function_definition;
typedef struct external_declaration {
    union {
        struct function_definition *function_def;
        struct declaration *decl;
    } p;
    enum { function_def_ed_e, decl_ed_e } e;
} external_declaration;
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
