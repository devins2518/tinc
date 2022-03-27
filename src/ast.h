#ifndef AST_H
#define AST_H

#include "ll.h"
#include "string.h"
#include "token.h"
#include "util.h"
#include "vector.h"

typedef int logical_and_expression;
typedef int inclusive_or_expression;
typedef int exclusive_or_expression;
typedef int and_expression;
typedef int equality_expression;
typedef int relational_expression;
typedef int shift_expression;
typedef int additive_expression;
typedef int multiplicative_expression;
typedef int cast_expression;
typedef int unary_expression;
typedef int postfix_expression;
typedef int primary_expression;
typedef int constant;
typedef int expression;
typedef int assignment_expression;
typedef int assignment_operator;
typedef int unary_operator;
typedef int type_name;
typedef int parameter_type_list;
typedef int parameter_list;
typedef int parameter_declaration;
typedef int abstract_declarator;
typedef int direct_abstract_declarator;
typedef int enum_specifier;
typedef int enumerator_list;
typedef int enumerator;
typedef int typedef_name;
typedef int declaration;
DECLARE_LINKED_LIST(declaration)
typedef int init_declarator;
typedef int initializer;
typedef int initializer_list;
typedef int compound_statement;
typedef int statement;
typedef int labeled_statement;
typedef int expression_statement;
typedef int selection_statement;
typedef int iteration_statement;
typedef int jump_statement;

typedef struct logical_or_expression {
    logical_and_expression lae;
    struct logical_or_expression *loe;
} logical_or_expression;

typedef struct conditional_expression {
    logical_or_expression loe;
    expression expr;
    struct conditional_expression *cond_expr;
} conditional_expression;

typedef conditional_expression constant_expression;

typedef enum { const_tq, volatile_tq } type_qualifier;
DECLARE_LINKED_LIST(type_qualifier)

typedef struct pointer {
    ll_type_qualifier type_quals;
    struct pointer *ptr;
    bool ptr_pres;
} pointer;

typedef struct {
    ident ident;
    declarator paren_decl;
} direct_declarator;

typedef struct {
    pointer ptr;
    bool ptr_pres;
    direct_declarator decl;
} declarator;

typedef struct {
    declarator decl;
    bool decl_pres;
    constant_expression const_expr;
    bool const_expr_pres;
} struct_declarator;
DECLARE_LINKED_LIST(struct_declarator)

typedef ll_struct_declarator struct_declarator_list;

typedef struct {
    union {
        type_specifier ts_p;
        type_qualifier tq_p;
    } p;
    enum { type_specifier_e_sq, type_qualifier_e_sq } e;
} specifier_qualifier;
DECLARE_LINKED_LIST(specifier_qualifier)

typedef struct {
    ll_specifier_qualifier qualifiers;
    struct_declarator_list list;
} struct_declaration;
DECLARE_LINKED_LIST(struct_declaration)

typedef enum { struct_sou, union_sou } struct_or_union;

typedef struct {
    struct_or_union sou;
    ident ident;
    bool ident_pres;
    ll_struct_declaration decls;
    bool decls_pres;
} struct_or_union_specifier;

typedef struct {
    union {
        struct_or_union_specifier sou_spec_p;
        enum_specifier enum_spec_p;
        typedef_name typedef_name_p;
    } p;
    enum {
        void_e,
        char_e,
        short_e,
        int_e,
        long_e,
        float_e,
        double_e,
        signed_e,
        unsigned_e,
        sou_spec_e,
        enum_spec_e,
        typedef_name_e
    } e;
} type_specifier;

typedef enum {
    auto_scs,
    register_scs,
    static_scs,
    extern_scs,
    typedef_scs
} storage_class_specifier;

typedef struct {
    union {
        storage_class_specifier scs_p;
        type_specifier ts_p;
        type_qualifier tq_p;
    } p;
    enum {
        storage_class_specifier_e,
        type_specifier_e_ds,
        type_qualifier_e_ds
    } e;
} declaration_specifier;
DECLARE_LINKED_LIST(declaration_specifier)

typedef struct {
    ll_declaration_specifier decl_specifier;
    declarator decl;
    ll_declaration decls;
    compound_statement body;
} function_definition;

typedef struct {
    union {
        function_definition function_p;
        declaration_specifier declaration_p;
    } p;
    enum { function_e, declaration_e } e;
} ast_token;
DECLARE_VECTOR(ast_token)

string print_ast_token(ast_token *a);

#endif
