#include "preprocessor.h"
#include "scanner.h"
#include "token.h"
#include "utils.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

scanner scanner_new(string *src) {
    scanner s;
    s.state = start_state;
    s.src = src;
    s.curr = 0;
    s.index = 0;
    s.line = 0;
    return s;
}

bool scanner_is_digit(char c) {
    return (c >= '0' && c <= '9');
}

bool scanner_is_nondigit(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_');
}

bool scanner_is_s_char(scanner *s) {
    bool ret = true;
    switch (s->src->inner[s->index]) {
    case '"':
    case '\n':
        ret = false;
        break;
    case '\\':
        switch (s->src->inner[++s->index]) {
        case '\'':
        case '"':
        case '?':
        case '\\':
        case 'a':
        case 'b':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case 'v':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case 'x':
            break;
        default:
            ret = false;
            break;
        }
    default:
        break;
    }
    return ret;
}

bool scanner_is_h_char(char c) {
    bool ret = true;
    switch (c) {
    case '\n':
    case '>':
        ret = false;
    default:
        break;
    }
    return ret;
}

pp_token scanner_next(scanner *s) {
    pp_token t;
    s->curr = s->index;
    /* TODO */
    while (true) {
        if (s->index < s->src->len) {
            char c = s->src->inner[s->index];
            switch (s->state) {
            case start_state: {
                if (c == '"') {
                    s->state = string_lit_state;
                    break;
                } else if (c == 'L') {
                    s->state = wide_string_lit_state;
                    break;
                } else if (scanner_is_digit(c)) {
                    s->state = number_state;
                    break;
                } else if (c == '*') {
                    s->state = star_state;
                    break;
                } else if (c == '=') {
                    s->state = eq_state;
                    break;
                } else if (c == '#') {
                    s->state = hash_state;
                    break;
                } else if (c == '.') {
                    s->state = period_state;
                    break;
                } else if (c == '+') {
                    s->state = plus_state;
                    break;
                } else if (c == '-') {
                    s->state = minus_state;
                    break;
                } else if (c == '<') {
                    s->state = lt_state;
                    break;
                } else if (c == '>') {
                    s->state = gt_state;
                    break;
                } else if (c == '&') {
                    s->state = and_state;
                    break;
                } else if (c == '/') {
                    s->state = div_state;
                    break;
                } else if (c == '%') {
                    s->state = percent_state;
                    break;
                } else if (c == '!') {
                    s->state = bang_state;
                    break;
                } else if (c == '^') {
                    s->state = xor_state;
                    break;
                } else if (c == '(') {
                    s->index++;
                    t = pp_multi(s->curr, s->index, lparen_multi);
                    goto exit;
                } else if (c == ')') {
                    s->index++;
                    t = pp_multi(s->curr, s->index, rparen_multi);
                    goto exit;
                } else if (c == '{') {
                    s->index++;
                    t = pp_punct(s->curr, s->index, lbrace_punct);
                    goto exit;
                } else if (c == '}') {
                    s->index++;
                    t = pp_punct(s->curr, s->index, rbrace_punct);
                    goto exit;
                } else if (c == '[') {
                    s->index++;
                    t = pp_multi(s->curr, s->index, lbracket_multi);
                    goto exit;
                } else if (c == ']') {
                    s->index++;
                    t = pp_multi(s->curr, s->index, rbracket_multi);
                    goto exit;
                } else if (c == ',') {
                    s->index++;
                    t = pp_multi(s->curr, s->index, comma_multi);
                    goto exit;
                } else if (c == '~') {
                    s->index++;
                    t = pp_op(s->curr, s->index, approx_op);
                    goto exit;
                } else if (c == ' ') {
                    s->index++;
                    t = pp_whitespace(s->curr, s->index, space_ws);
                    goto exit;
                } else if (c == '\n') {
                    s->index++;
                    s->line++;
                    t = pp_whitespace(s->curr, s->index, nl_ws);
                    goto exit;
                } else if (c == '|') {
                    s->state = or_state;
                    break;
                } else if (c == ';') {
                    s->index++;
                    t = pp_punct(s->curr, s->index, semicolon_punct);
                    goto exit;
                } else if (scanner_is_digit(c)) {
                    s->state = number_state;
                    break;
                } else if (scanner_is_nondigit(c)) {
                    s->state = ident_state;
                    break;
                }
                break;
            }
            case ident_state: {
                if (!scanner_is_nondigit(c) && !scanner_is_digit(c)) {
                    t = pp_ident(s->curr, s->index,
                                 string_new_len(&s->src->inner[s->curr], s->index - s->curr));
                    pp_try_keyword(&t);
                    goto exit;
                }
                break;
            }
            case number_state: {
                if ((!scanner_is_digit(c) && !scanner_is_nondigit(c)) && c != '.' && c != '+' &&
                    c != '-') {
                    t = pp_pp_number(s->curr, s->index,
                                     string_new_len(&s->src->inner[s->curr], s->index - s->curr));
                    goto exit;
                }
                break;
            }
            case wide_string_lit_state:
                if (c != '"') {
                    s->state = start_state;
                    break;
                }
            case string_lit_state:
                if (c == '\n') {
                    t = pp_error(s->curr, s->index,
                                 "Newlines are not allowed within string literals.");
                    goto exit;
                } else if (c == '"') {
                    t = pp_string_lit(s->curr, s->index,
                                      string_new_len(&s->src->inner[s->curr], ++s->index - s->curr),
                                      s->state == wide_string_lit_state);
                    goto exit;
                }
                break;
            case star_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, stareq_op);
                } else {
                    t = pp_multi(s->curr, s->index, star_multi);
                }
                goto exit;
            case eq_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, eqeq_op);
                } else {
                    t = pp_multi(s->curr, s->index, eq_multi);
                }
                goto exit;
            case hash_state:
                if (c == '#') {
                    s->index++;
                    t = pp_op(s->curr, s->index, dblhash_op);
                } else {
                    if ((s->index - 1) == 0 || s->src->inner[s->index - 2] == '\n') {
                        t = pp_punct(s->curr, s->index, hash_punct);
                    } else {
                        t = pp_op(s->curr, s->index, hash_op);
                    }
                }
                goto exit;
            case period_state:
                if (c == '.' && s->src->inner[s->index] == '.') {
                    s->index += 2;
                    t = pp_punct(s->curr, s->index, ellipsis_punct);
                } else {
                    t = pp_op(s->curr, s->index, period_op);
                }
                goto exit;
            case plus_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, pluseq_op);
                } else if (c == '+') {
                    s->index++;
                    t = pp_op(s->curr, s->index, dblplus_op);
                } else {
                    t = pp_op(s->curr, s->index, plus_op);
                }
                goto exit;
            case minus_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, minuseq_op);
                } else if (c == '>') {
                    s->index++;
                    t = pp_op(s->curr, s->index, arrow_op);
                } else if (c == '-') {
                    s->index++;
                    t = pp_op(s->curr, s->index, dblminus_op);
                } else {
                    t = pp_op(s->curr, s->index, minus_op);
                }
                goto exit;
            case lt_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, lteq_op);
                    goto exit;
                } else if (c == '<') {
                    s->state = shiftl_state;
                } else {
                    s->index++;
                    t = pp_op(s->curr, s->index, lt_op);
                    goto exit;
                }
                break;
            case gt_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, gteq_op);
                    goto exit;
                } else if (c == '<') {
                    s->state = shiftr_state;
                } else {
                    t = pp_op(s->curr, s->index, gt_op);
                    goto exit;
                }
                break;
            case and_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, andeq_op);
                } else if (c == '&') {
                    s->index++;
                    t = pp_op(s->curr, s->index, dbland_op);
                } else {
                    t = pp_op(s->curr, s->index, logand_op);
                }
                goto exit;
            case div_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, diveq_op);
                    goto exit;
                } else if (c == '*') {
                    s->state = comment_state;
                } else {
                    t = pp_op(s->curr, s->index, div_op);
                    goto exit;
                }
                break;
            case percent_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, percenteq_op);
                } else {
                    t = pp_op(s->curr, s->index, percent_op);
                }
                goto exit;
            case bang_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, bangeq_op);
                } else {
                    t = pp_op(s->curr, s->index, bang_op);
                }
                goto exit;
            case xor_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, xoreq_op);
                } else {
                    t = pp_op(s->curr, s->index, logxor_op);
                }
                goto exit;
            case or_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, oreq_op);
                } else if (c == '|') {
                    s->index++;
                    t = pp_op(s->curr, s->index, dblor_op);
                } else {
                    t = pp_op(s->curr, s->index, logor_op);
                }
                goto exit;
            case shiftl_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, shiftleq_op);
                } else {
                    t = pp_op(s->curr, s->index, shiftl_op);
                }
                goto exit;
            case shiftr_state:
                if (c == '=') {
                    s->index++;
                    t = pp_op(s->curr, s->index, shiftreq_op);
                } else {
                    t = pp_op(s->curr, s->index, shiftr_op);
                }
                goto exit;
            case comment_state:
                if (c == '*' && s->src->inner[s->index + 1] == '/') {
                    s->index++;
                    s->curr = s->index + 1;
                    s->state = start_state;
                }
                break;
            }
            s->index++;
        } else {
            t = pp_whitespace(s->curr, s->index, eof_ws);
            goto exit;
        }
    }

exit:
    s->curr = s->index;
    s->state = start_state;
    return t;
}

pp_token scanner_skip_ws(scanner *s) {
    pp_token t = scanner_next(s);
    while (t.e == whitespace_e)
        t = scanner_next(s);
    return t;
}
