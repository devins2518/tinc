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
        RESTORE;                                                                                   \
    }
#define GET_CURR_TOK(l) l->pp_tokens->inner[l->pp_idx]
#define ADV_TOK(l) (l->pp_idx)++
#define LATE_MALLOC(var) (var) = malloc(sizeof(*(var)))
#define VOID_FN_CAST(fn) (void *(*)(lexer *))(&fn)
#define SAVE lexer old_l = *l
#define RESTORE *l = old_l;

ident *try_parse_ident(lexer *l);
expression *try_parse_expression(lexer *l);
primary_expression *try_parse_primary_expression(lexer *l);
postfix_expression *try_parse_postfix_expression(lexer *l);
postfix_expression_term *try_parse_postfix_expression_term(lexer *l);
assignment_expression *try_parse_assignment_expression(lexer *l);
argument_expression_list *try_parse_argument_expression_list(lexer *l);
unary_expression *try_parse_unary_expression(lexer *l);
type_name *try_parse_type_name(lexer *l);
unary_operator try_parse_unary_operator(lexer *l);
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
specifier_qualifier_list *try_parse_specifier_qualifier_list(lexer *l);
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
parameter_type_list *try_parse_parameter_type_list(lexer *l);
parameter_list *try_parse_parameter_list(lexer *l);
parameter_declaration *try_parse_parameter_declaration(lexer *l);
identifier_list *try_parse_identifier_list(lexer *l);
abstract_declarator *try_parse_abstract_declarator(lexer *l);
direct_abstract_declarator *try_parse_direct_abstract_declarator(lexer *l);
direct_abstract_declarator_term *try_parse_direct_abstract_declarator_term(lexer *l);
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

bool try_parse_inc_op(lexer *l) {
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == op_e && curr.p.op_p == dblplus_op) {
        ADV_TOK(l);
        return true;
    } else
        return false;
}
bool try_parse_dec_op(lexer *l) {
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == op_e && curr.p.op_p == dblminus_op) {
        ADV_TOK(l);
        return true;
    } else
        return false;
}
bool try_parse_period(lexer *l) {
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == op_e && curr.p.op_p == period_op) {
        ADV_TOK(l);
        return true;
    } else
        return false;
}
bool try_parse_deref_op(lexer *l) {
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == op_e && curr.p.op_p == arrow_op) {
        ADV_TOK(l);
        return true;
    } else
        return false;
}
bool next_is_unary_operator(lexer *l) {
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == op_e) {
        switch (curr.p.op_p) {
        case logand_op:
        case star_op:
        case plus_op:
        case minus_op:
        case approx_op:
        case bang_op:
            return true;
        default:
            return false;
        }
    } else if (curr.e == multi_e && curr.p.multi_p == star_multi) {
        return true;
    } else
        return false;
}
bool try_parse_sizeof(lexer *l) {
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == keyword_e && curr.p.keyword_p == sizeof_kw) {
        ADV_TOK(l);
        return true;
    } else {
        return false;
    }
}
bool try_parse_empty_braced(lexer *l) {
    bool ret = false;
    uint64_t idx = l->pp_idx;
    pp_token curr = l->pp_tokens->inner[idx];
    if (curr.e == punct_e && curr.p.punct_p == lbrace_punct) {
        idx++;
        curr = l->pp_tokens->inner[idx];
        if (curr.e == punct_e && curr.p.punct_p == rbrace_punct) {
            idx++;
            l->pp_idx = idx;
            ret = true;
        }
    }
    return ret;
}
void *try_parse_braced(lexer *l, void *(fn)(lexer *)) {
    void *ret = NULL;
    uint64_t idx = l->pp_idx;
    pp_token curr = l->pp_tokens->inner[idx];
    if (curr.e == punct_e && curr.p.punct_p == lbrace_punct) {
        idx++;
        ret = fn(l);
        curr = l->pp_tokens->inner[idx];
        if (curr.e == punct_e && curr.p.punct_p == rbrace_punct) {
            idx++;
            l->pp_idx = idx;
            goto ret_succ;
        } else {
            goto errdefer_ret;
        }
    }
    ERRDEFER_FREE(ret)
ret_succ:
    return ret;
}
bool try_parse_empty_bracketed(lexer *l) {
    bool ret = false;
    uint64_t idx = l->pp_idx;
    pp_token curr = l->pp_tokens->inner[idx];
    if (curr.e == multi_e && curr.p.multi_p == lbracket_multi) {
        idx++;
        curr = l->pp_tokens->inner[idx];
        if (curr.e == multi_e && curr.p.multi_p == rbracket_multi) {
            idx++;
            l->pp_idx = idx;
            ret = true;
        }
    }
    return ret;
}
void *try_parse_bracketed(lexer *l, void *(fn)(lexer *)) {
    void *ret = NULL;
    uint64_t idx = l->pp_idx;
    pp_token curr = l->pp_tokens->inner[idx];
    if (curr.e == multi_e && curr.p.multi_p == lbracket_multi) {
        idx++;
        ret = fn(l);
        curr = l->pp_tokens->inner[idx];
        if (curr.e == multi_e && curr.p.multi_p == rbracket_multi) {
            idx++;
            l->pp_idx = idx;
            goto ret_succ;
        } else {
            goto errdefer_ret;
        }
    }
    ERRDEFER_FREE(ret)
ret_succ:
    return ret;
}
bool try_parse_empty_parened(lexer *l) {
    bool ret = false;
    uint64_t idx = l->pp_idx;
    pp_token curr = l->pp_tokens->inner[idx];
    if (curr.e == multi_e && curr.p.multi_p == lparen_multi) {
        idx++;
        curr = l->pp_tokens->inner[idx];
        if (curr.e == multi_e && curr.p.multi_p == rparen_multi) {
            idx++;
            l->pp_idx = idx;
            ret = true;
        }
    }
    return ret;
}
void *try_parse_parened(lexer *l, void *(fn)(lexer *)) {
    void *ret = NULL;
    pp_token curr = GET_CURR_TOK(l);
    SAVE;

    if (curr.e == multi_e && curr.p.multi_p == lparen_multi) {
        ADV_TOK(l);
        ret = fn(l);
        curr = GET_CURR_TOK(l);
        if (curr.e == multi_e && curr.p.multi_p == rparen_multi) {
            ADV_TOK(l);
            goto ret_succ;
        } else {
            goto errdefer_ret;
        }
    }

    RESTORE;
    ERRDEFER_FREE(ret)
ret_succ:
    return ret;
}

/* TODO: check */
translation_unit *try_parse_translation_unit(lexer *l) {
    translation_unit *tu = malloc(sizeof(*tu));
    external_declaration *ed;
    SAVE;

    *tu = translation_unit_new();
    while ((ed = try_parse_external_declaration(l))) {
        translation_unit_add(tu, *ed);
    }

    ENSURE_NOT_EMPTY(translation_unit, tu);
    return tu;
}
/* TODO: check */
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
/* TODO: check */
expression *try_parse_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
primary_expression *try_parse_primary_expression(lexer *l) {
    primary_expression *pe;
    ident *i = NULL;
    uint64_t *constant = NULL;
    string_lit *string_lit = NULL;
    expression *e = NULL;

    pp_token curr = GET_CURR_TOK(l);
    if ((i = try_parse_ident(l))) {
        goto ret_succ;
    } else if (curr.e == pp_number_e) {
        LATE_MALLOC(constant);
        *constant = curr.p.pp_number_p;
        goto ret_succ;
    }

    return NULL;

ret_succ:
    LATE_MALLOC(pe);
    if (i) {
        pe->e = ident_pe_e;
        pe->p.ident = i;
    } else if (constant) {
        pe->e = constant_pe_e;
        pe->p.constant = constant;
    } else if (string_lit) {
        pe->e = string_lit_pe_e;
        pe->p.string_lit = string_lit;
    } else if (e) {
        pe->e = expr_pe_e;
        pe->p.expr = e;
    }
    return pe;
}
/* TODO: check */
postfix_expression *try_parse_postfix_expression(lexer *l) {
    postfix_expression *pe;
    primary_expression *primary_e = NULL;
    postfix_expression_term *pet = NULL;
    SAVE;

    primary_e = try_parse_primary_expression(l);
    CHECK(primary_e);
    pet = try_parse_postfix_expression_term(l);
    goto ret_succ;

    ERRDEFER_FREE(primary_e);
    RESTORE;
    return NULL;

ret_succ:
    LATE_MALLOC(pe);
    pe->pe = primary_e;
    pe->pet = pet;
    return pe;
}
/* TODO: check */
postfix_expression_term *try_parse_postfix_expression_term(lexer *l) {
    postfix_expression_term *pet = NULL;
    expression *ai = NULL;
    argument_expression_list *fa = NULL;
    ident *fo = NULL;
    ident *deref_op = NULL;
    postfix_expression_term *child_pet = NULL;
    enum postfix_expression_term_disriminant petd;

    if ((ai = try_parse_bracketed(l, VOID_FN_CAST(try_parse_expression)))) {
        petd = array_poste_term_e;
    } else if (try_parse_empty_parened(l)) {
        petd = function_poste_term_e;
    } else if ((fa = try_parse_parened(l, VOID_FN_CAST(try_parse_argument_expression_list)))) {
        petd = function_poste_term_e;
    } else if (try_parse_period(l)) {
        petd = field_poste_term_e;
        fo = try_parse_ident(l);
        CHECK(fo);
    } else if (try_parse_deref_op(l)) {
        petd = deref_poste_term_e;
        deref_op = try_parse_ident(l);
        CHECK(deref_op);
    } else if (try_parse_inc_op(l)) {
        petd = inc_poste_term_e;
    } else if (try_parse_dec_op(l)) {
        petd = dec_poste_term_e;
    } else {
        goto ret_fail;
    }
    child_pet = try_parse_postfix_expression_term(l);
    goto ret_succ;

ret_fail:
    ERRDEFER_FREE(deref_op);
    ERRDEFER_FREE(fo);
    return NULL;

ret_succ:
    LATE_MALLOC(pet);
    pet->e = petd;
    pet->pet = child_pet;
    if (ai) {
        pet->p.array_idx = ai;
    } else if (fa) {
        pet->p.function_args = fa;
    } else if (fo) {
        pet->p.field_op = fo;
    } else if (deref_op) {
        pet->p.deref_op = deref_op;
    }
    return pet;
}
/* TODO: check */
assignment_expression *try_parse_assignment_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_assignment_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
argument_expression_list *try_parse_argument_expression_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_argument_expression_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
unary_expression *try_parse_unary_expression(lexer *l) {
    unary_expression *ue;
    postfix_expression *pe = NULL;
    unary_expression *child_ue = NULL;
    unary_operator uo;
    cast_expression *ce = NULL;
    type_name *tn = NULL;
    enum unary_expression_discriminant ued;
    SAVE;

    if ((pe = try_parse_postfix_expression(l))) {
        ued = expr_ue_e;
    } else if (try_parse_inc_op(l)) {
        ued = inc_unary_expr_ue_e;
        child_ue = try_parse_unary_expression(l);
        CHECK(child_ue);
    } else if (try_parse_dec_op(l)) {
        ued = dec_unary_expr_ue_e;
        child_ue = try_parse_unary_expression(l);
        CHECK(child_ue);
    } else if ((next_is_unary_operator(l))) {
        ued = unary_op_cast_expr_ue_e;
        uo = try_parse_unary_operator(l);
        ce = try_parse_cast_expression(l);
        CHECK(ce);
    } else if ((try_parse_sizeof(l))) {
        if ((child_ue = try_parse_unary_expression(l))) {
            ued = sizeof_unary_expr_ue_e;
        } else {
            tn = try_parse_parened(l, VOID_FN_CAST(try_parse_type_name));
            CHECK(tn);
            ued = sizeof_type_name_ue_e;
        }
    } else {
        goto ret_fail;
    }
    goto ret_succ;

ret_fail:
    ERRDEFER_FREE(tn)
    ERRDEFER_FREE(ce)
    ERRDEFER_FREE(child_ue)
    RESTORE;
    return NULL;

ret_succ:
    LATE_MALLOC(ue);
    ue->e = ued;
    if (pe) {
        ue->p.expr = pe;
    } else if (child_ue) {
        ue->p.unary_expr = child_ue;
    } else if (ce) {
        ue->p.cast_expr.unary_op = uo;
        ue->p.cast_expr.cast_expr = ce;
    } else if (tn) {
        ue->p.type_name = tn;
    }
    return ue;
}
/* TODO: check */
type_name *try_parse_type_name(lexer *l) {
    type_name *tn;
    specifier_qualifier_list *sql = NULL;
    abstract_declarator *ad = NULL;
    SAVE;

    sql = try_parse_specifier_qualifier_list(l);
    CHECK(sql);
    ad = try_parse_abstract_declarator(l);
    goto ret_succ;

    ERRDEFER_FREE(sql);
    RESTORE;
    return NULL;

ret_succ:
    LATE_MALLOC(tn);
    tn->sql = sql;
    tn->abstract_decl = ad;
    return tn;
}
/* TODO: check */
unary_operator try_parse_unary_operator(lexer *l) {
    unary_operator uo = bang_uo_e + 1;
    pp_token curr = GET_CURR_TOK(l);
    if (curr.e == op_e) {
        switch (curr.p.op_p) {
        case logand_op:
            uo = and_uo_e;
            break;
        case star_op:
            uo = star_uo_e;
            break;
        case plus_op:
            uo = plus_uo_e;
            break;
        case minus_op:
            uo = minus_uo_e;
            break;
        case approx_op:
            uo = approx_uo_e;
            break;
        case bang_op:
            uo = bang_uo_e;
            break;
        default:
            break;
        }
    } else if (curr.e == multi_e && curr.p.multi_p == star_multi) {
        uo = star_uo_e;
    }
    ADV_TOK(l);
    return uo;
}
/* TODO: check */
cast_expression *try_parse_cast_expression(lexer *l) {
    cast_expression *ce;
    unary_expression *ue = NULL;
    type_name *tn = NULL;
    cast_expression *child_ce = NULL;

    if ((ue = try_parse_unary_expression(l))) {
        goto ret_succ;
    } else if ((tn = try_parse_parened(l, VOID_FN_CAST(try_parse_type_name)))) {
        child_ce = try_parse_cast_expression(l);
        CHECK(child_ce);
        goto ret_succ;
    }

    ERRDEFER_FREE(child_ce);
    free(tn);
    return NULL;

ret_succ:
    LATE_MALLOC(ce);
    if (ue) {
        ce->e = unary_expr_ce_e;
        ce->p.unary_expr = ue;
    } else if (tn) {
        ce->e = ty_name_ce_e;
        ce->p.cast.ty = tn;
        ce->p.cast.ce = child_ce;
    }
    return ce;
}
/* TODO: check */
multiplicative_expression *try_parse_multiplicative_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_multiplicative_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
additive_expression *try_parse_additive_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_additive_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
shift_expression *try_parse_shift_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_shift_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
relational_expression *try_parse_relational_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_relational_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
equality_expression *try_parse_equality_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_equality_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
and_expression *try_parse_and_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_and_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
exclusive_or_expression *try_parse_exclusive_or_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_exclusive_or_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
inclusive_or_expression *try_parse_inclusive_or_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_inclusive_or_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
logical_and_expression *try_parse_logical_and_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_logical_and_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
logical_or_expression *try_parse_logical_or_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_logical_or_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
conditional_expression *try_parse_conditional_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_conditional_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
assignment_operator *try_parse_assignment_operator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_assignment_operator *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
constant_expression *try_parse_constant_expression(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_constant_expression *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
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
/* TODO: check */
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
/* TODO: check */
declaration_specifiers *try_parse_declaration_specifiers(lexer *l) {
    declaration_specifiers *dss = malloc(sizeof(*dss));
    declaration_specifier *ds;
    SAVE;

    *dss = declaration_specifiers_new();
    while ((ds = try_parse_declaration_specifier(l))) {
        declaration_specifiers_add(dss, *ds);
    }

    ENSURE_NOT_EMPTY(declaration_specifiers, dss);
    return dss;
}
/* TODO: check */
init_declarator *try_parse_init_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_init_declarator *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
init_declarator_list *try_parse_init_declarator_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_init_declarator_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
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
/* TODO: check */
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
            ts->e = char_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == short_kw) {
            LATE_MALLOC(ts);
            ts->e = short_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == int_kw) {
            LATE_MALLOC(ts);
            ts->e = int_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == long_kw) {
            LATE_MALLOC(ts);
            ts->e = long_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == float_kw) {
            LATE_MALLOC(ts);
            ts->e = float_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == double_kw) {
            LATE_MALLOC(ts);
            ts->e = double_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == signed_kw) {
            LATE_MALLOC(ts);
            ts->e = signed_ts_e;
            ADV_TOK(l);
        } else if (curr.p.keyword_p == unsigned_kw) {
            LATE_MALLOC(ts);
            ts->e = unsigned_ts_e;
            ADV_TOK(l);
        } else if ((sous = try_parse_struct_or_union_specifier(l))) {
            LATE_MALLOC(ts);
            ts->e = struct_or_union_specifier_ts_e;
            ts->p.sou_spec = sous;
        } else if ((es = try_parse_enum_specifier(l))) {
            LATE_MALLOC(ts);
            ts->e = enum_specifier_ts_e;
            ts->p.enum_spec = es;
        }
    } else if ((i = try_parse_ident(l))) { // typedef-name
        LATE_MALLOC(ts);
        ts->e = type_name_ts_e;
        ts->p.type_name = i;
    }
    return ts;
}
/* TODO: check */
struct_or_union_specifier *try_parse_struct_or_union_specifier(lexer *l) {
    struct_or_union_specifier *sous;
    struct_or_union *sou;
    ident *ident;
    struct_declarator_list *fields;

    sou = try_parse_struct_or_union(l);
    CHECK(sou);
    ident = try_parse_ident(l);
    fields = try_parse_braced(l, VOID_FN_CAST(try_parse_struct_declarator_list));
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
/* TODO: check */
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
/* TODO: check */
struct_declaration *try_parse_struct_declaration(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_declaration *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
struct_declaration_list *try_parse_struct_declaration_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_declaration_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
_specifier_qualifier *try_parse__specifier_qualifier(lexer *l) {
    _specifier_qualifier *sq;
    type_specifier *ts = NULL;
    type_qualifier *tq = NULL;
    SAVE;

    ts = try_parse_type_specifier(l);
    if (ts)
        goto ret_succ;
    tq = try_parse_type_qualifier(l);
    if (tq)
        goto ret_succ;

    RESTORE;
    return NULL;

ret_succ:
    LATE_MALLOC(sq);
    if (ts) {
        sq->p.specifier = ts;
        sq->e = type_specifier_sq_e;
    } else if (ts) {
        sq->p.qualifier = tq;
        sq->e = type_qualifier_sq_e;
    }
    return sq;
}
specifier_qualifier_list *try_parse_specifier_qualifier_list(lexer *l) {
    specifier_qualifier_list *sql = malloc(sizeof(*sql));
    _specifier_qualifier *sq;
    SAVE;

    *sql = specifier_qualifier_list_new();
    while ((sq = try_parse__specifier_qualifier(l))) {
        specifier_qualifier_list_add(sql, *sq);
    }

    ENSURE_NOT_EMPTY(specifier_qualifier_list, sql);
    return sql;
}
/* TODO: check */
struct_declarator_list *try_parse_struct_declarator_list(lexer *l) {
    struct_declarator_list *sdl = malloc(sizeof(*sdl));
    struct_declarator *sd;
    SAVE;

    *sdl = struct_declarator_list_new();
    while ((sd = try_parse_struct_declarator(l))) {
        struct_declarator_list_add(sdl, *sd);
    }

    ENSURE_NOT_EMPTY(struct_declarator_list, sdl);
    return sdl;
}
/* TODO: check */
struct_declarator *try_parse_struct_declarator(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_struct_declarator *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
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
    el = try_parse_braced(l, VOID_FN_CAST(try_parse_enumerator_list));
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
/* TODO: check */
enumerator_list *try_parse_enumerator_list(lexer *l) {
    enumerator_list *el = malloc(sizeof(*el));
    enumerator *e;
    SAVE;

    *el = enumerator_list_new();
    while ((e = try_parse_enumerator(l))) {
        enumerator_list_add(el, *e);
    }

    ENSURE_NOT_EMPTY(enumerator_list, el);
    return el;
}
/* TODO: check */
enumerator *try_parse_enumerator(lexer *l) {
    enumerator *e;
    ident *i;
    constant_expression *const_expr = NULL;

    i = try_parse_ident(l);
    CHECK(i);
    // Parse = token
    {
        pp_token curr = GET_CURR_TOK(l);
        if (curr.e == multi_e && curr.p.multi_p == eq_multi) {
            ADV_TOK(l);
            const_expr = try_parse_constant_expression(l);
            CHECK(const_expr)
        }
    }
    goto ret_succ;

    ERRDEFER_FREE(const_expr);
    ERRDEFER_FREE(i);
    return NULL;

ret_succ:
    LATE_MALLOC(e);
    e->ident = i;
    e->const_expr = const_expr;
    return e;
}
/* TODO: check */
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
/* TODO: check */
type_qualifier_list *try_parse_type_qualifier_list(lexer *l) {
    type_qualifier_list *tql = malloc(sizeof(*tql));
    type_qualifier *tq;
    SAVE;

    *tql = type_qualifier_list_new();
    while ((tq = try_parse_type_qualifier(l))) {
        type_qualifier_list_add(tql, *tq);
    }

    ENSURE_NOT_EMPTY(type_qualifier_list, tql);
    return tql;
}
/* TODO: check */
declarator *try_parse_declarator(lexer *l) {
    declarator *d;
    direct_declarator *dd = NULL;
    pointer *p = NULL;

    p = try_parse_pointer(l);
    dd = try_parse_direct_declarator(l);
    CHECK(dd)
    goto ret_succ;

    ERRDEFER_FREE(dd)
    return NULL;

ret_succ:
    LATE_MALLOC(d);
    d->direct_decl = dd;
    d->ptr = p;
    return d;
}
/* TODO: check */
direct_declarator *try_parse_direct_declarator(lexer *l) {
    direct_declarator *dd = NULL;
    ident *i = NULL;
    declarator *d = NULL;

    if ((i = try_parse_ident(l))) {
        LATE_MALLOC(dd);
        dd->e = ident_dd_e;
        dd->p.ident = i;
        return dd;
    } else if ((d = try_parse_parened(l, VOID_FN_CAST(try_parse_declarator)))) {
        LATE_MALLOC(dd);
        dd->e = decl_dd_e;
        dd->p.decl = d;
        return dd;
    } else {
        direct_declarator *child_dd = NULL;
        child_dd = try_parse_direct_declarator(l);
        if (child_dd) {
            constant_expression *ce = NULL;
            parameter_type_list *ptl = NULL;
            identifier_list *il = NULL;
            LATE_MALLOC(dd);
            dd->e = dd_dd_e;
            dd->p.dd.dd = child_dd;
            if ((ce = try_parse_bracketed(l, VOID_FN_CAST(try_parse_constant_expression)))) {
                dd->p.dd.dd_type = const_expr_bracket_ddt_e;
                dd->p.dd.post.bracket = ce;
            } else if (try_parse_empty_bracketed(l)) {
                dd->p.dd.dd_type = empty_bracket_ddt_e;
            } else if ((ptl = try_parse_parened(l, VOID_FN_CAST(try_parse_parameter_type_list)))) {
                dd->p.dd.dd_type = parameter_list_paren_ddt_e;
                dd->p.dd.post.params = ptl;
            } else if ((il = try_parse_parened(l, VOID_FN_CAST(try_parse_identifier_list)))) {
                dd->p.dd.dd_type = empty_paren_ddt_e;
                dd->p.dd.post.idents = il;
            } else if (try_parse_empty_parened(l)) {
                dd->p.dd.dd_type = empty_paren_ddt_e;
            } else {
                free(dd);
                free(child_dd);
                return NULL;
            }
            return dd;
        }
        return NULL;
    }
}
/* TODO: check */
pointer *try_parse_pointer(lexer *l) {
    pointer *p;
    type_qualifier_list *tql = NULL;
    pointer *child_p = NULL;

    // Parse * token
    {
        pp_token curr = GET_CURR_TOK(l);
        if (curr.e == multi_e && curr.p.multi_p == star_multi) {
            ADV_TOK(l);
        } else {
            goto ret_fail;
        }
    }
    tql = try_parse_type_qualifier_list(l);
    child_p = try_parse_pointer(l);
    goto ret_succ;

ret_fail:
    return NULL;

ret_succ:
    LATE_MALLOC(p);
    p->tql = tql;
    p->ptr = child_p;
    return p;
}
/* TODO: check */
parameter_type_list *try_parse_parameter_type_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_parameter_type_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
parameter_list *try_parse_parameter_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_parameter_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
parameter_declaration *try_parse_parameter_declaration(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_parameter_declaration *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
identifier_list *try_parse_identifier_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_identifier_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
abstract_declarator *try_parse_abstract_declarator(lexer *l) {
    abstract_declarator *ad;
    pointer *p = NULL;
    direct_abstract_declarator *dad = NULL;
    SAVE;

    p = try_parse_pointer(l);
    dad = try_parse_direct_abstract_declarator(l);
    if (!p && !dad) {
        RESTORE;
        return NULL;
    }

    LATE_MALLOC(ad);
    ad->ptr = p;
    ad->direct_abstract_decl = dad;
    return ad;
}
/* TODO: check */
direct_abstract_declarator *try_parse_direct_abstract_declarator(lexer *l) {
    direct_abstract_declarator *dad = malloc(sizeof(*dad));
    abstract_declarator *ad = NULL;
    constant_expression *ce = NULL;
    parameter_type_list *ptl = NULL;

    if ((ad = try_parse_parened(l, VOID_FN_CAST(try_parse_abstract_declarator)))) {
        dad->e = paren_ad_dad_e;
        dad->p.paren_dad = ad;
    } else if (try_parse_empty_bracketed(l)) {
        dad->e = empty_bracket_dad_e;
    } else if ((ce = try_parse_bracketed(l, VOID_FN_CAST(try_parse_constant_expression)))) {
        dad->e = const_expr_bracket_dad_e;
        dad->p.bracket_dad = ce;
    } else if (try_parse_empty_parened(l)) {
        dad->e = empty_paren_dad_e;
    } else if ((ptl = try_parse_parened(l, VOID_FN_CAST(try_parse_parameter_type_list)))) {
        dad->e = paren_paramater_type_list_dad_e;
        dad->p.paren_list = ptl;
    } else {
        return NULL;
    }
    dad->dad_t = try_parse_direct_abstract_declarator_term(l);
    return dad;
}
/* TODO: check */
direct_abstract_declarator_term *try_parse_direct_abstract_declarator_term(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_direct_abstract_declarator_term *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
initializer *try_parse_initializer(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_initializer *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
initializer_list *try_parse_initializer_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_initializer_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
statement *try_parse_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_statement *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
labeled_statement *try_parse_labeled_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_labeled_statement *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
compound_statement *try_parse_compound_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_compound_satement *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
declaration_list *try_parse_declaration_list(lexer *l) {
    declaration_list *dl = malloc(sizeof(*dl));
    declaration *d;
    SAVE;

    *dl = declaration_list_new();
    while ((d = try_parse_declaration(l))) {
        declaration_list_add(dl, *d);
    }

    ENSURE_NOT_EMPTY(declaration_list, dl);
    return dl;
}
/* TODO: check */
statement_list *try_parse_statement_list(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_statement_list *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
expression_statement *try_parse_expression_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_expression_statement *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
selection_statement *try_parse_selection_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_selection_statement *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
iteration_statement *try_parse_iteration_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_iteration_statement *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
jump_statement *try_parse_jump_statement(lexer *l) {
    (void)l;
    printf("unimplemented try_parse_jump_statement *");
    exit(EXIT_FAILURE);
}
/* TODO: check */
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
/* TODO: check */
function_definition *try_parse_function_definition(lexer *l) {
    function_definition *fd;
    declaration_specifiers *decl_specs;
    declarator *sig;
    compound_statement *body;

    decl_specs = try_parse_declaration_specifiers(l);
    sig = try_parse_declarator(l);
    CHECK(sig)
    body = try_parse_compound_statement(l);
    CHECK(body)
    goto ret_succ;

    ERRDEFER_FREE(body)
    ERRDEFER_FREE(sig)
    return NULL;

ret_succ:
    LATE_MALLOC(fd);
    fd->decl_specs = decl_specs;
    fd->sig = sig;
    fd->body = body;
    return fd;
}
