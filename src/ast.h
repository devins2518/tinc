#ifndef AST_H
#define AST_H

#include "ll.h"
#include "string.h"
#include "sys/ttycom.h"
#include "sys/wait.h"
#include "token.h"
#include "util.h"
#include "vector.h"

struct expression;
struct primary_expression;
struct postfix_expression;
struct assignment_expression;
struct argument_expression_list;
struct unary_expression;
typedef enum { and_uo_e, star_uo_e, plus_uo_e, minus_uo_e, approx_uo_e, bang_uo_e } unary_operator;
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
typedef enum {
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
typedef enum {
    typedef_scs_e,
    extern_scs_e,
    static_scs_e,
    auto_scs_e,
    register_scs_e
} storage_class_specifier;
struct type_specifier;
struct struct_or_union_specifier;
typedef enum { struct_sou_e, union_sou_e } struct_or_union;
struct struct_declaration;
struct struct_declaration_list;
struct _specifier_qualifier;
struct struct_declarator_list;
struct struct_declarator;
struct enum_specifier;
struct enumerator_list;
struct enumerator;
typedef enum { const_tq_e, volatile_tq_e } type_qualifier;
DECLARE_VECTOR(type_qualifier)
typedef vector_type_qualifier type_qualifier_list;
struct declarator;
struct direct_declarator;
struct pointer;
struct type_qualifier_list;
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

typedef struct {
    union {
        ident ident;
        constant_tk constant;
        string_lit string_lit;
        struct expression *expr;
    } p;
    enum { ident_pe_e, constant_pe_e, string_lit_pe_e, expr_pe_e } e;
} primary_expression;
typedef struct {
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
typedef struct {
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
typedef vector_assignment_expression argument_expression_list;
typedef struct {
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
typedef struct {
    struct declarator *decl;
    bool initialized;
    struct initializer *init;
} init_declarator;
DECLARE_VECTOR(init_declarator)
typedef vector_init_declarator init_declarator_list;
typedef struct {
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
typedef struct {
    bool present;
    struct specifier_qualifier_list *specs;
    struct struct_declarator_list *fields;
} struct_or_union_specifier;
typedef struct {
    struct specifier_qualifier_list *specs;
    struct struct_declarator_list *body;
} struct_declaration;
DECLARE_VECTOR(struct_declaration)
typedef vector_struct_declaration struct_declaration_list;
typedef struct {
    union {
        struct type_specifier *specifier;
        struct type_qualifier *qualifier;
    } p;
    enum { type_specifier_sq_e, type_qualifier_sq_e } e;
} _specifier_qualifier;
DECLARE_VECTOR(_specifier_qualifier)
typedef vector__specifier_qualifier specifier_qualifier_list;
typedef struct {
    struct declarator *decl;
    struct constant_expression *const_expr;
    enum { decl_only_sd_e, colon_const_expr_sd_e, decl_const_expr_sd_e } e;
} struct_declarator;
DECLARE_VECTOR(struct_declarator)
typedef vector_struct_declarator struct_declarator_list;
typedef struct {
    ident ident;
    bool ident_present;
    struct enumerator_list *enumerator;
    bool enumerator_present;
} enum_specifier;
typedef struct {
    ident ident;
    struct constant_expression *const_expr;
    bool const_expr_present;
} enumerator;
DECLARE_VECTOR(enumerator)
typedef vector_enumerator enumerator_list;
typedef struct {
    struct direct_declarator *direct_decl;
    struct pointer *ptr;
    bool ptr_present;
} declarator;
typedef struct {
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
typedef struct {
    struct type_qualifier_list *tql;
    struct pointer *ptr;
    enum { empty_ptr_e, tql_ptr_e, ptr_ptr_e, tql_ptr_ptr_e } e;
} pointer;
typedef struct {
    struct declaration_specifiers *decl_specs;
    union {
        struct declarator *decl;
        struct abstract_declarator *abstract_declarator;
    } p;
    enum { none_pd_e, decl_pd_e, abstract_decl_pd_e } e;
} parameter_declaration;
DECLARE_VECTOR(parameter_declaration)
typedef vector_parameter_declaration parameter_list;
typedef struct {
    parameter_list params;
    bool ellipsis;
} parameter_type_list;
DECLARE_VECTOR(ident)
typedef vector_ident identifier_list;
typedef struct {
    struct specifier_qualifier_list *sql;
    struct abstract_declarator *abstract_decl;
    bool abstract_decl_present;
} type_name;
typedef struct {
    struct pointer *ptr;
    bool ptr_present;
    struct direct_abstract_declarator *direct_abstract_decl;
    bool direct_abstract_decl_present;
} abstract_declarator;
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

typedef struct {
    union {
        struct function_definition *function_def;
    } p;
    enum { function_def_ast_e } e;
} ast_token;
DECLARE_LINKED_LIST(ast_token)

string ast_token_to_string(ast_token *a);

#endif
