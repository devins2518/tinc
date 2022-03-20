#include "token.h"

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
pp_token pp_error(int start, int end, const char *msg) {
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
