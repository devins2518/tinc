#include "parser.h"

#define CHECK(var)                                                                                 \
    if (!var) {                                                                                    \
        goto errdefer_##var;                                                                       \
    }
#define ERRDEFER_FREE(var) errdefer_##var : free(var);
#define ENSURE_NOT_EMPTY(ty, var)                                                                  \
    if (var->len == 0) {                                                                           \
        ty##_free(*var);                                                                           \
        free(var);                                                                                 \
        var = NULL;                                                                                \
    }
#define GET_CURR_TOK(l) l->pp_tokens->inner[l->pp_idx]
#define ADV_TOK(l) (l->pp_idx)++
#define LATE_MALLOC(var) (var) = malloc(sizeof(*(var)))

ident *try_parse_ident(lexer *l);
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
declaration_specifier *try_parse_declaration_specifier(lexer *l);
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

ast_token *generate_ast(vector_pp_token *tokens) {
    lexer l = lexer_new(tokens);
    translation_unit *tu = try_parse_translation_unit(&l);
    return ast_translation_unit(tu);
}

translation_unit *try_parse_translation_unit(lexer *l) {
    translation_unit *tu = malloc(sizeof(*tu));
    external_declaration *ed;
    *tu = translation_unit_new();
    while ((ed = try_parse_external_declaration(l))) {
        translation_unit_add(tu, *ed);
    }
    ENSURE_NOT_EMPTY(translation_unit, tu);
    return tu;
}
ident *try_parse_ident(lexer *l) {
    ident *i = NULL;
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == ident_e) {
        LATE_MALLOC(i);
        *i = string_clone(curr.p.ident_p);
        ADV_TOK(l);
    }
    return i;
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
    declaration *d;
    declaration_specifiers *ds;
    init_declarator_list *idl;

    ds = try_parse_declaration_specifiers(l);
    CHECK(ds);
    idl = try_parse_init_declarator_list(l);
    goto ret_succ;

    ERRDEFER_FREE(ds);
    return NULL;

ret_succ:
    LATE_MALLOC(d);
    d->decl_specs = ds;
    d->decl_list = idl;
    return d;
}
declaration_specifier *try_parse_declaration_specifier(lexer *l) {
    declaration_specifier *ds = NULL;
    storage_class_specifier *scs;
    type_specifier *ts;
    type_qualifier *tq;
    if ((scs = try_parse_storage_class_specifier(l))) {
        LATE_MALLOC(ds);
        ds->e = scs_ds_e;
        ds->p.scs = scs;
    } else if ((ts = try_parse_type_specifier(l))) {
        LATE_MALLOC(ds);
        ds->e = type_specifier_ds_e;
        ds->p.specifier = ts;
    } else if ((tq = try_parse_type_qualifier(l))) {
        LATE_MALLOC(ds);
        ds->e = type_qualifier_ds_e;
        ds->p.qualifier = tq;
    }
    return ds;
}
declaration_specifiers *try_parse_declaration_specifiers(lexer *l) {
    declaration_specifiers *dss = malloc(sizeof(*dss));
    declaration_specifier *ds;
    *dss = declaration_specifiers_new();
    while ((ds = try_parse_declaration_specifier(l))) {
        declaration_specifiers_add(dss, *ds);
    }
    ENSURE_NOT_EMPTY(declaration_specifiers, dss);
    return dss;
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
    storage_class_specifier *scs = NULL;
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == keyword_e) {
        switch (curr.p.keyword_p) {
        case auto_kw:
            LATE_MALLOC(scs);
            *scs = auto_scs_e;
            break;
        case extern_kw:
            LATE_MALLOC(scs);
            *scs = extern_scs_e;
            break;
        case static_kw:
            LATE_MALLOC(scs);
            *scs = static_scs_e;
            break;
        case register_kw:
            LATE_MALLOC(scs);
            *scs = register_scs_e;
            break;
        default:
            break;
        }
    }
    return scs;
}
type_specifier *try_parse_type_specifier(lexer *l) {
    type_specifier *ts = NULL;
    struct_or_union_specifier *sous;
    enum_specifier *es;
    ident *i;
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == keyword_e) {
        if (curr.p.keyword_p == void_kw) {
            LATE_MALLOC(ts);
            ts->e = void_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == char_kw) {
            LATE_MALLOC(ts);
            ts->e = char_kw;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == short_kw) {
            LATE_MALLOC(ts);
            ts->e = short_kw;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == int_kw) {
            LATE_MALLOC(ts);
            ts->e = int_kw;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == long_kw) {
            LATE_MALLOC(ts);
            ts->e = long_kw;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == float_kw) {
            LATE_MALLOC(ts);
            ts->e = float_kw;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == double_kw) {
            LATE_MALLOC(ts);
            ts->e = double_kw;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == signed_kw) {
            LATE_MALLOC(ts);
            ts->e = signed_kw;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == unsigned_kw) {
            LATE_MALLOC(ts);
            ts->e = unsigned_kw;
            ADV_TOK(l);
        }
    } else if ((sous = try_parse_struct_or_union_specifier(l))) {
        LATE_MALLOC(ts);
        ts->e = struct_or_union_specifier_ts_e;
        ts->p.sou_spec = sous;
    } else if ((es = try_parse_enum_specifier(l))) {
        LATE_MALLOC(ts);
        ts->e = enum_specifier_ts_e;
        ts->p.enum_spec = es;
    } else if ((i = try_parse_ident(l))) { // typedef-name
        LATE_MALLOC(ts);
        ts->e = type_name_ts_e;
        ts->p.type_name = i;
    }
    return ts;
}
struct_or_union_specifier *try_parse_struct_or_union_specifier(lexer *l) {
    struct_or_union_specifier *sous;
    struct_or_union *sou;
    ident *ident;
    struct_declarator_list *fields;

    sou = try_parse_struct_or_union(l);
    CHECK(sou);
    ident = try_parse_ident(l);
    fields = try_parse_struct_declarator_list(l);
    goto ret_succ;

    ERRDEFER_FREE(sou)
    return NULL;

ret_succ:
    LATE_MALLOC(sous);
    sous->sou = sou;
    sous->ident = ident;
    sous->fields = fields;
    return sous;
}
struct_or_union *try_parse_struct_or_union(lexer *l) {
    struct_or_union *sou = NULL;
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == keyword_e) {
        if (curr.p.keyword_p == struct_kw) {
            LATE_MALLOC(sou);
            ADV_TOK(l);
            *sou = struct_sou_e;
        } else if (curr.p.keyword_p == union_kw) {
            LATE_MALLOC(sou);
            ADV_TOK(l);
            *sou = union_sou_e;
        }
    }
    return sou;
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
    enum_specifier *es;
    ident *ident = NULL;
    enumerator_list *el = NULL;

    // Parse enum token
    {
        pp_token curr = GET_CURR_TOK(l);
        if (curr.e == keyword_e && curr.p.keyword_p == enum_kw) {
            ADV_TOK(l);
        } else {
            goto ret_fail;
        }
    }
    ident = try_parse_ident(l);
    el = try_parse_enumerator_list(l);
    // Must have one of identifier or definition list
    if (ident || el) {
        goto ret_succ;
    } else {
        goto ret_fail;
    }

ret_fail:
    free(ident);
    free(el);
    return NULL;

ret_succ:
    LATE_MALLOC(es);
    es->ident = ident;
    es->enumerator = el;
    return es;
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
    type_qualifier *tq = NULL;
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == keyword_e) {
        if (curr.p.keyword_p == const_kw) {
            LATE_MALLOC(tq);
            ADV_TOK(l);
            *tq = const_tq_e;
        } else if (curr.p.keyword_p == volatile_tq_e) {
            LATE_MALLOC(tq);
            ADV_TOK(l);
            *tq = volatile_tq_e;
        }
    }
    return tq;
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
    printf("unimplemented try_parse_compound_satement *");
    exit(EXIT_FAILURE);
}
declaration_list *try_parse_declaration_list(lexer *l) {
    declaration_list *dl = malloc(sizeof(*dl));
    declaration *d;
    *dl = declaration_list_new();
    while ((d = try_parse_declaration(l))) {
        declaration_list_add(dl, *d);
    }
    ENSURE_NOT_EMPTY(declaration_list, dl);
    return dl;
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
    external_declaration *ed = NULL;
    function_definition *fd;
    declaration *d;
    if ((fd = try_parse_function_definition(l))) {
        ed = malloc(sizeof(*ed));
        ed->e = function_def_ed_e;
        ed->p.function_def = fd;
    } else if ((d = try_parse_declaration(l))) {
        ed = malloc(sizeof(*ed));
        ed->e = decl_ed_e;
        ed->p.decl = d;
    }
    return ed;
}
function_definition *try_parse_function_definition(lexer *l) {
    function_definition *fd;
    declaration_specifiers *decl_specs;
    bool decl_specs_present;
    declaration_list *decl_list;
    bool decl_list_present;
    declarator *sig;
    compound_statement *body;

    decl_specs = try_parse_declaration_specifiers(l);
    decl_specs_present = decl_specs != NULL;
    decl_list = try_parse_declaration_list(l);
    decl_list_present = decl_list != NULL;
    sig = try_parse_declarator(l);
    CHECK(sig)
    body = try_parse_compound_statement(l);
    CHECK(body)
    goto ret_succ;

    ERRDEFER_FREE(body)
    ERRDEFER_FREE(sig)
    return NULL;

ret_succ:
    fd = malloc(sizeof(*fd));
    fd->decl_specs = decl_specs;
    fd->decl_specs_present = decl_specs_present;
    fd->decl_list = decl_list;
    fd->decl_list_present = decl_list_present;
    fd->sig = sig;
    fd->body = body;
    return fd;
}
