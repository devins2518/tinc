#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ident_eq(const ident *self, const ident *other) {
    return string_eq(self, other);
}

string pp_token_to_string(pp_token *t) {
    string s;
    switch (t->e) {
    case keyword_e:
        s = string_new_raw("keyword: ");
        switch (t->p.keyword_p) {
        case auto_kw:
            string_append_char_star(&s, "auto");
            break;
        case break_kw:
            string_append_char_star(&s, "break");
            break;
        case case_kw:
            string_append_char_star(&s, "case");
            break;
        case char_kw:
            string_append_char_star(&s, "char");
            break;
        case const_kw:
            string_append_char_star(&s, "const");
            break;
        case continue_kw:
            string_append_char_star(&s, "continue");
            break;
        case default_kw:
            string_append_char_star(&s, "default");
            break;
        case do_kw:
            string_append_char_star(&s, "do");
            break;
        case double_kw:
            string_append_char_star(&s, "double");
            break;
        case else_kw:
            string_append_char_star(&s, "else");
            break;
        case enum_kw:
            string_append_char_star(&s, "enum");
            break;
        case extern_kw:
            string_append_char_star(&s, "extern");
            break;
        case float_kw:
            string_append_char_star(&s, "float");
            break;
        case for_kw:
            string_append_char_star(&s, "for");
            break;
        case goto_kw:
            string_append_char_star(&s, "goto");
            break;
        case if_kw:
            string_append_char_star(&s, "if");
            break;
        case int_kw:
            string_append_char_star(&s, "int");
            break;
        case long_kw:
            string_append_char_star(&s, "long");
            break;
        case register_kw:
            string_append_char_star(&s, "register");
            break;
        case return_kw:
            string_append_char_star(&s, "return");
            break;
        case short_kw:
            string_append_char_star(&s, "short");
            break;
        case signed_kw:
            string_append_char_star(&s, "signed");
            break;
        case sizeof_kw:
            string_append_char_star(&s, "sizeof");
            break;
        case static_kw:
            string_append_char_star(&s, "static");
            break;
        case struct_kw:
            string_append_char_star(&s, "struct");
            break;
        case switch_kw:
            string_append_char_star(&s, "switch");
            break;
        case typedef_kw:
            string_append_char_star(&s, "typedef");
            break;
        case union_kw:
            string_append_char_star(&s, "union");
            break;
        case unsigned_kw:
            string_append_char_star(&s, "unsigned");
            break;
        case void_kw:
            string_append_char_star(&s, "void");
            break;
        case volatile_kw:
            string_append_char_star(&s, "volatile");
            break;
        case while_kw:
            string_append_char_star(&s, "while");
            break;
        }
        break;
    case header_name_e:
        s = string_new_raw("header: ");
        string_append_string(&s, &t->p.header_name_p);
        break;
    case ident_e:
        s = string_new_raw("ident: ");
        string_append_string(&s, &t->p.ident_p);
        break;
    case pp_number_e: {
        char buf[1000];
        snprintf(buf, 1000, "%llu", t->p.pp_number_p);
        s = string_new_raw("pp_number: ");
        string_append_char_star(&s, buf);
        break;
    }
    case char_const_e:
        s = string_new_raw("char_const: ");
        string_append_string(&s, &t->p.char_const_p);
        break;
    case string_lit_e:
        s = string_new_raw("string_lit: ");
        string_append_string(&s, &t->p.string_lit_p.str);
        break;
    case op_e:
        switch (t->p.op_p) {
        case lbracket_op:
            s = string_new_raw("op: [");
            break;
        case rbracket_op:
            s = string_new_raw("op: ]");
            break;
        case lparen_op:
            s = string_new_raw("op: (");
            break;
        case rparen_op:
            s = string_new_raw("op: )");
            break;
        case period_op:
            s = string_new_raw("op: .");
            break;
        case arrow_op:
            s = string_new_raw("op: ->");
            break;
        case dblplus_op:
            s = string_new_raw("op: ++");
            break;
        case dblminus_op:
            s = string_new_raw("op: --");
            break;
        case logand_op:
            s = string_new_raw("op: &");
            break;
        case star_op:
            s = string_new_raw("op: *");
            break;
        case plus_op:
            s = string_new_raw("op: +");
            break;
        case minus_op:
            s = string_new_raw("op: -");
            break;
        case approx_op:
            s = string_new_raw("op: ~");
            break;
        case bang_op:
            s = string_new_raw("op: !");
            break;
        case sizeof_op:
            s = string_new_raw("op: sizeof");
            break;
        case div_op:
            s = string_new_raw("op: /");
            break;
        case percent_op:
            s = string_new_raw("op: %");
            break;
        case shiftl_op:
            s = string_new_raw("op: <<");
            break;
        case shiftr_op:
            s = string_new_raw("op: >>");
            break;
        case lt_op:
            s = string_new_raw("op: <");
            break;
        case gt_op:
            s = string_new_raw("op: >");
            break;
        case lteq_op:
            s = string_new_raw("op: <=");
            break;
        case gteq_op:
            s = string_new_raw("op: >=");
            break;
        case eqeq_op:
            s = string_new_raw("op: ==");
            break;
        case bangeq_op:
            s = string_new_raw("op: !=");
            break;
        case logxor_op:
            s = string_new_raw("op: ^");
            break;
        case logor_op:
            s = string_new_raw("op: |");
            break;
        case dbland_op:
            s = string_new_raw("op: &&");
            break;
        case dblor_op:
            s = string_new_raw("op: ||");
            break;
        case ternaryq_op:
            s = string_new_raw("op: ?");
            break;
        case ternaryc_op:
            s = string_new_raw("op: :");
            break;
        case eq_op:
            s = string_new_raw("op: =");
            break;
        case stareq_op:
            s = string_new_raw("op: *=");
            break;
        case diveq_op:
            s = string_new_raw("op: /=");
            break;
        case percenteq_op:
            s = string_new_raw("op: %=");
            break;
        case pluseq_op:
            s = string_new_raw("op: +=");
            break;
        case minuseq_op:
            s = string_new_raw("op: -=");
            break;
        case shiftleq_op:
            s = string_new_raw("op: <<=");
            break;
        case shiftreq_op:
            s = string_new_raw("op: >>=");
            break;
        case andeq_op:
            s = string_new_raw("op: &=");
            break;
        case xoreq_op:
            s = string_new_raw("op: ^=");
            break;
        case oreq_op:
            s = string_new_raw("op: |=");
            break;
        case comma_op:
            s = string_new_raw("op: ,");
            break;
        case hash_op:
            s = string_new_raw("op: #");
            break;
        case dblhash_op:
            s = string_new_raw("op: ##");
            break;
        default:
            break;
        }
        break;
    case punct_e:
        switch (t->p.punct_p) {
        case lbracket_punct:
            s = string_new_raw("punct: [");
            break;
        case rbracket_punct:
            s = string_new_raw("punct: ]");
            break;
        case lparen_punct:
            s = string_new_raw("punct: (");
            break;
        case rparen_punct:
            s = string_new_raw("punct: )");
            break;
        case lbrace_punct:
            s = string_new_raw("punct: {");
            break;
        case rbrace_punct:
            s = string_new_raw("punct: }");
            break;
        case star_punct:
            s = string_new_raw("punct: *");
            break;
        case comma_punct:
            s = string_new_raw("punct: ,");
            break;
        case colon_punct:
            s = string_new_raw("punct: :");
            break;
        case eq_punct:
            s = string_new_raw("punct: =");
            break;
        case semicolon_punct:
            s = string_new_raw("punct: ;");
            break;
        case ellipsis_punct:
            s = string_new_raw("punct: ...");
            break;
        case hash_punct:
            s = string_new_raw("punct: #");
            break;
        default:
            break;
        }
        break;
    case multi_e:
        switch (t->p.multi_p) {
        case lbracket_multi:
            s = string_new_raw("multi: [");
            break;
        case rbracket_multi:
            s = string_new_raw("multi: ]");
            break;
        case lparen_multi:
            s = string_new_raw("multi: (");
            break;
        case rparen_multi:
            s = string_new_raw("multi: )");
            break;
        case star_multi:
            s = string_new_raw("multi: *");
            break;
        case comma_multi:
            s = string_new_raw("multi: ,");
            break;
        case eq_multi:
            s = string_new_raw("multi: =");
            break;
        case colon_multi:
            s = string_new_raw("multi: :");
            break;
        }
        break;
    case error_e:
        s = string_new_len(t->p.error_p.inner, t->end - t->start);
        break;
    case whitespace_e:
        switch (t->p.whitespace_p) {
        case space_ws:
            s = string_new_raw("whitespace: sp");
            break;
        case nl_ws:
            s = string_new_raw("whitespace: nl");
            break;
        case eof_ws:
            s = string_new_raw("whitespace: eof");
            break;
        }
    }
    return s;
}

#define FREE_CASE(name)                                                                            \
    case name##_e:                                                                                 \
        string_free(tok.p.name##_p);                                                               \
        break;
void pp_token_free(pp_token tok) {
    switch (tok.e) {
        FREE_CASE(header_name)
        FREE_CASE(ident)
        FREE_CASE(char_const)
        FREE_CASE(error)
    default:
        break;
    }
}
#undef FREE_CASE

bool pp_token_eq(pp_token *a, pp_token *b) {
    bool ret = false;

    if (a->e == b->e) {
        switch (a->e) {
        case keyword_e:
            ret = a->p.keyword_p == b->p.keyword_p;
            break;
        case header_name_e:
            ret = string_eq(&a->p.header_name_p, &b->p.header_name_p);
            break;
        case ident_e:
            ret = string_eq(&a->p.ident_p, &b->p.ident_p);
            break;
        case pp_number_e:
            ret = a->p.pp_number_p == b->p.pp_number_p;
            break;
        case char_const_e:
            ret = string_eq(&a->p.char_const_p, &b->p.char_const_p);
            break;
        case string_lit_e:
            ret = string_eq(&a->p.string_lit_p.str, &b->p.string_lit_p.str);
            break;
        case op_e:
            ret = (a->p.op_p) == (b->p.op_p);
            break;
        case punct_e:
            ret = (a->p.punct_p) == (b->p.punct_p);
            break;
        case multi_e:
            ret = (a->p.multi_p) == (b->p.multi_p);
            break;
        case error_e:
            ret = (a->start == b->start) && (a->end == b->end) &&
                  (string_eq(&a->p.error_p, &b->p.error_p));
            break;
        case whitespace_e:
            ret = (a->p.whitespace_p == b->p.whitespace_p);
            break;
        }
    }

    return ret;
}

pp_token pp_header_name(int start, int end, header_name h) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.header_name_p = h;
    t.e = header_name_e;
    return t;
}
pp_token pp_ident(int start, int end, ident i) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.ident_p = i;
    t.e = ident_e;
    return t;
}
pp_token pp_pp_number(int start, int end, pp_number p) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.pp_number_p = p;
    t.e = pp_number_e;
    return t;
}
pp_token pp_char_const(int start, int end, char_cons c) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.char_const_p = c;
    t.e = char_const_e;
    return t;
}
pp_token pp_string_lit(int start, int end, string_lit s, bool wide) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.string_lit_p.str = s;
    t.p.string_lit_p.wide = wide;
    t.e = string_lit_e;
    return t;
}
pp_token pp_op(int start, int end, op o) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.op_p = o;
    t.e = op_e;
    return t;
}
pp_token pp_punct(int start, int end, punct p) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.punct_p = p;
    t.e = punct_e;
    return t;
}
pp_token pp_multi(int start, int end, multi m) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.multi_p = m;
    t.e = multi_e;
    return t;
}
pp_token pp_error(int start, int end, char *msg) {
    pp_token t;
    error e = string_new_raw(msg);
    t.start = start;
    t.end = end;
    t.p.error_p = e;
    t.e = error_e;
    return t;
}
pp_token pp_whitespace(int start, int end, whitespace w) {
    pp_token t;
    t.start = start;
    t.end = end;
    t.p.whitespace_p = w;
    t.e = whitespace_e;
    return t;
}
void pp_try_keyword(pp_token *t) {
    if (t->e == ident_e) {
        if (string_eq_char_star(&t->p.ident_p, "auto")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = auto_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "break")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = break_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "case")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = case_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "char")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = char_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "const")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = const_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "continue")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = continue_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "default")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = default_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "do")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = do_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "double")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = double_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "else")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = else_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "enum")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = enum_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "extern")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = extern_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "float")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = float_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "for")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = for_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "goto")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = goto_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "if")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = if_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "int")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = int_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "long")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = long_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "register")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = register_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "return")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = return_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "short")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = short_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "signed")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = signed_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "sizeof")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = sizeof_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "static")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = static_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "struct")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = struct_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "switch")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = switch_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "typedef")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = typedef_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "union")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = union_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "unsigned")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = unsigned_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "void")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = void_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "volatile")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = volatile_kw;
        } else if (string_eq_char_star(&t->p.ident_p, "while")) {
            pp_token_free(*t);
            t->e = keyword_e;
            t->p.keyword_p = while_kw;
        }
    }
}

IMPL_GENERIC_HASH(pp_token)
IMPL_VECTOR(pp_token)
