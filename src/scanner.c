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

bool scanner_is_digit(char c) { return (c >= '0' && c <= '9'); }

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
    /* TODO */
    while (s->index <= s->src->len) {
        string pp_str;
        char c = s->src->inner[s->index++];
        switch (s->state) {
        case start_state: {
            if (c == '"') {
                s->state = string_lit_state;
                break;
            } else if (c == 'L') {
                s->state = wide_string_lit_state;
                break;
            } else if (c == 'u' || c == 'U') {
                /* unsigned int */
                exit(EXIT_FAILURE);
            } else if (c == 'l' || c == 'L') {
                /* long int */
                exit(EXIT_FAILURE);
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
                s->state = pp_directive_state;
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
                t = pp_multi(lparen_multi);
                goto exit;
            } else if (c == ')') {
                t = pp_multi(rparen_multi);
                goto exit;
            } else if (c == '{') {
                t = pp_punct(lbrace_punct);
                goto exit;
            } else if (c == '}') {
                t = pp_punct(rbrace_punct);
                goto exit;
            } else if (c == '[') {
                t = pp_multi(lbracket_multi);
                goto exit;
            } else if (c == ']') {
                t = pp_multi(rbracket_multi);
                goto exit;
            } else if (c == ',') {
                t = pp_multi(comma_multi);
                goto exit;
            } else if (c == '~') {
                t = pp_op(approx_op);
                goto exit;
            } else if (c == ' ') {
                s->curr++;
                t = pp_whitespace(space_ws);
                break;
            } else if (c == '\n') {
                s->curr++;
                s->line++;
                t = pp_whitespace(nl_ws);
                goto exit;
            } else if (c == '\0') {
                t = pp_whitespace(eof_ws);
                goto exit;
            } else if (c == '|') {
                s->state = or_state;
                break;
            } else if (c == ';') {
                t = pp_punct(semicolon_punct);
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
                t = pp_ident(
                    string_new(&s->src->inner[s->curr], --s->index - s->curr));
                goto exit;
            }
            break;
        }
        case number_state: {
            if ((!scanner_is_digit(c) && !scanner_is_nondigit(c)) && c != '.' &&
                c != '+' && c != '-') {
                t = pp_pp_number(
                    string_new(&s->src->inner[s->curr], --s->index - s->curr));
                goto exit;
            }
            break;
        }
        case string_lit_state:
        case wide_string_lit_state:
            if (c == '\n') /* TODO error handling */
                ;
            else if (c == '"') {
                t = pp_string_lit(
                    string_new(&s->src->inner[s->curr], s->index - s->curr),
                    s->state == wide_string_lit_state);
                goto exit;
            }
            break;
        case star_state:
            if (c == '=') {
                t = pp_op(stareq_op);
            } else {
                s->index--;
                t = pp_multi(star_multi);
            }
            goto exit;
        case eq_state:
            if (c == '=') {
                t = pp_op(eqeq_op);
            } else {
                s->index--;
                t = pp_multi(eq_multi);
            }
            goto exit;
        case pp_directive_state:
            s->curr++;
            while (scanner_is_nondigit(s->src->inner[s->index]) ||
                   scanner_is_digit(s->src->inner[s->index])) {
                s->index++;
            }
            pp_str = string_new(&s->src->inner[s->curr], s->index - s->curr);
            if (string_eq_char_star(&pp_str, "if")) {
                printf("preprocessing if\n");
            } else if (string_eq_char_star(&pp_str, "ifdef")) {
                printf("preprocessing ifdef\n");
            } else if (string_eq_char_star(&pp_str, "ifndef")) {
                printf("preprocessing ifndef\n");
            } else if (string_eq_char_star(&pp_str, "include")) {
                printf("preprocessing include\n");
            } else if (string_eq_char_star(&pp_str, "define")) {
                printf("preprocessing define\n");
            } else if (string_eq_char_star(&pp_str, "undef")) {
                printf("preprocessing undef\n");
            } else if (string_eq_char_star(&pp_str, "line")) {
                printf("preprocessing line\n");
            } else if (string_eq_char_star(&pp_str, "error")) {
                printf("preprocessing error\n");
            } else if (string_eq_char_star(&pp_str, "pragma")) {
                printf("preprocessing pragma\n");
            }
            if (c == '\n') {
                s->state = start_state;
            }
            printf("unimplemented");
            exit(EXIT_FAILURE);
            break;
        case period_state:
            if (c == '.' && s->src->inner[s->index] == '.') {
                s->index++;
                t = pp_punct(ellipsis_punct);
            } else {
                s->index--;
                t = pp_op(period_op);
            }
            goto exit;
        case plus_state:
            if (c == '=') {
                t = pp_op(pluseq_op);
            } else if (c == '+') {
                t = pp_op(dblplus_op);
            } else {
                s->index--;
                t = pp_op(plus_op);
            }
            goto exit;
        case minus_state:
            if (c == '=') {
                t = pp_op(minuseq_op);
            } else if (c == '>') {
                t = pp_op(arrow_op);
            } else if (c == '-') {
                t = pp_op(dblminus_op);
            } else {
                s->index--;
                t = pp_op(minus_op);
            }
            goto exit;
        case lt_state:
            if (c == '=') {
                t = pp_op(lteq_op);
                goto exit;
            } else if (c == '<') {
                s->state = shiftl_state;
            } else {
                s->index--;
                t = pp_op(lt_op);
                goto exit;
            }
            break;
        case gt_state:
            if (c == '=') {
                t = pp_op(gteq_op);
                goto exit;
            } else if (c == '<') {
                s->state = shiftr_state;
            } else {
                s->index--;
                t = pp_op(gt_op);
                goto exit;
            }
            break;
        case and_state:
            if (c == '=') {
                t = pp_op(andeq_op);
            } else if (c == '&') {
                t = pp_op(dbland_op);
            } else {
                s->index--;
                t = pp_op(logand_op);
            }
            goto exit;
        case div_state:
            if (c == '=') {
                t = pp_op(diveq_op);
                goto exit;
            } else if (c == '*') {
                s->state = comment_state;
            } else {
                s->index--;
                t = pp_op(div_op);
                goto exit;
            }
            break;
        case percent_state:
            if (c == '=') {
                t = pp_op(percenteq_op);
            } else {
                s->index--;
                t = pp_op(percent_op);
            }
            goto exit;
        case bang_state:
            if (c == '=') {
                t = pp_op(bangeq_op);
            } else {
                s->index--;
                t = pp_op(bang_op);
            }
            goto exit;
        case xor_state:
            if (c == '=') {
                t = pp_op(xoreq_op);
            } else {
                s->index--;
                t = pp_op(logxor_op);
            }
            goto exit;
        case or_state:
            if (c == '=') {
                t = pp_op(oreq_op);
            } else if (c == '|') {
                t = pp_op(dblor_op);
            } else {
                s->index--;
                t = pp_op(logor_op);
            }
            goto exit;
        case shiftl_state:
            if (c == '=') {
                t = pp_op(shiftleq_op);
            } else {
                s->index--;
                t = pp_op(shiftl_op);
            }
            goto exit;
        case shiftr_state:
            if (c == '=') {
                t = pp_op(shiftreq_op);
            } else {
                s->index--;
                t = pp_op(shiftr_op);
            }
            goto exit;
        case comment_state:
            if (c == '*' && s->src->inner[s->index] == '/') {
                s->index++;
                s->curr = s->index;
                s->state = start_state;
            }
            break;
        }
    }

exit:
    s->curr = s->index;
    s->state = start_state;
    return t;
}
