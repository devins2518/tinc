#include "token.h"
#include <stdlib.h>

string print_pp_token(pp_token *t) {
    string s;
    switch (t->e) {
    case header_name_e:
        s = t->p.header_name_p;
        break;
    case ident_e:
        s = t->p.ident_p;
        break;
    case pp_number_e:
        s = t->p.pp_number_p;
        break;
    case char_const_e:
        s = t->p.char_cons_p;
        break;
    case string_lit_e:
        s = t->p.string_lit_p;
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
            s = string_new_raw("punct: [");
            break;
        case rbracket_multi:
            s = string_new_raw("punct: ]");
            break;
        case lparen_multi:
            s = string_new_raw("punct: (");
            break;
        case rparen_multi:
            s = string_new_raw("punct: )");
            break;
        case hash_multi:
            s = string_new_raw("punct: #");
            break;
        case star_multi:
            s = string_new_raw("punct: *");
            break;
        case comma_multi:
            s = string_new_raw("punct: ,");
            break;
        case eq_multi:
            s = string_new_raw("punct: =");
            break;
        case colon_multi:
            s = string_new_raw("punct: :");
            break;
        }
        break;
    case error_e:
        s = string_new(t->p.error_p.msg,
                       t->p.error_p.span_end - t->p.error_p.span_start);
        break;
    case whitespace_e:
        switch (t->p.whitespace_p) {
        case newline:
            s = string_new_raw("whitespace \\n");
            break;
        case space:
            s = string_new_raw("whitespace <space>");
            break;
        }
        break;
    }
    return s;
}

pp_token pp_header_name(header_name h) {
    pp_token t;
    t.p.header_name_p = h;
    t.e = header_name_e;
    return t;
}
pp_token pp_ident(ident i) {
    pp_token t;
    t.p.ident_p = i;
    t.e = ident_e;
    return t;
}
pp_token pp_pp_number(pp_number p) {
    pp_token t;
    t.p.pp_number_p = p;
    t.e = pp_number_e;
    return t;
}
pp_token pp_char_cons(char_cons c) {
    pp_token t;
    t.p.char_cons_p = c;
    t.e = char_const_e;
    return t;
}
pp_token pp_string_lit(string_lit s) {
    pp_token t;
    t.p.string_lit_p = s;
    t.e = string_lit_e;
    return t;
}
pp_token pp_op(op o) {
    pp_token t;
    t.p.op_p = o;
    t.e = op_e;
    return t;
}
pp_token pp_punct(punct p) {
    pp_token t;
    t.p.punct_p = p;
    t.e = punct_e;
    return t;
}
pp_token pp_multi(multi m) {
    pp_token t;
    t.p.multi_p = m;
    t.e = multi_e;
    return t;
}
pp_token pp_error(int start, int end, char *msg) {
    pp_token t;
    error e;
    e.span_start = start;
    e.span_end = end;
    e.msg = msg;
    t.p.error_p = e;
    t.e = error_e;
    return t;
}
pp_token pp_whitespace(whitespace w) {
    pp_token t;
    t.p.whitespace_p = w;
    t.e = whitespace_e;
    return t;
}
