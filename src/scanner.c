#include "token.h"
#include "utils.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    enum {
        start_state,
        ident_state,
        string_lit_state,
        wide_string_lit_state,
        number_state,
        star_state,
        eq_state,
        pp_directive_state,
        period_state,
        plus_state,
        minus_state,
        lt_state,
        gt_state,
        and_state,
        div_state,
        percent_state,
        bang_state,
        xor_state,
        or_state,
        shiftl_state,
        shiftr_state,
        comment_state
    } state;
    char *src;
    int src_len;
    int curr;  /* start of the in progress scan */
    int index; /* current index of the scan */
    int line;
    vector_pp_token tokens;
} scanner;

scanner scanner_new(char *src) {
    scanner s;
    s.state = start_state;
    s.src = src;
    s.src_len = strlen(src);
    s.curr = 0;
    s.index = 0;
    s.line = 0;
    s.tokens = vector_pp_token_new();
    return s;
}

void scanner_add_token(scanner *s, pp_token t) {
    if (vector_pp_token_add(&s->tokens, t)) {
        s->curr = s->index;
    } else {
        printf("failed to add token");
        exit(EXIT_FAILURE);
    }
}

bool scanner_in_ident(char c) {
    bool b;
    switch (c) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '_':
        b = true;
        break;
    default:
        b = false;
        break;
    }
    return b;
}

bool scanner_is_digit(char c) { return (c >= '0' && c <= '9'); }

bool scanner_is_nondigit(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_');
}

bool scanner_is_s_char(scanner *s) {
    bool ret = true;
    switch (s->src[s->index]) {
    case '"':
    case '\n':
        ret = false;
        break;
    case '\\':
        switch (s->src[++s->index]) {
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

vector_pp_token scan_file(string *str) {
    scanner s;

    s = scanner_new(str->inner);

    /* TODO */
    while (s.index <= s.src_len) {
        int index; /* For keeping track in preprocessing. */
        char c = s.src[s.index++];
        switch (s.state) {
        case start_state: {
            if (c == '"') {
                s.state = string_lit_state;
                break;
            } else if (c == 'L') {
                s.state = wide_string_lit_state;
                break;
            } else if (c == 'u' || c == 'U') {
                /* unsigned int */
                exit(EXIT_FAILURE);
            } else if (c == 'l' || c == 'L') {
                /* long int */
                exit(EXIT_FAILURE);
            } else if (scanner_is_digit(c)) {
                s.state = number_state;
                break;
            } else if (c == '*') {
                s.state = star_state;
                break;
            } else if (c == '=') {
                s.state = eq_state;
                break;
            } else if (c == '#') {
                s.state = pp_directive_state;
                break;
            } else if (c == '.') {
                s.state = period_state;
                break;
            } else if (c == '+') {
                s.state = plus_state;
                break;
            } else if (c == '-') {
                s.state = minus_state;
                break;
            } else if (c == '<') {
                s.state = lt_state;
                break;
            } else if (c == '>') {
                s.state = gt_state;
                break;
            } else if (c == '&') {
                s.state = and_state;
                break;
            } else if (c == '/') {
                s.state = div_state;
                break;
            } else if (c == '%') {
                s.state = percent_state;
                break;
            } else if (c == '!') {
                s.state = bang_state;
                break;
            } else if (c == '^') {
                s.state = xor_state;
                break;
            } else if (c == '(') {
                scanner_add_token(&s, pp_multi(lparen_multi));
                break;
            } else if (c == ')') {
                scanner_add_token(&s, pp_multi(rparen_multi));
                break;
            } else if (c == '{') {
                scanner_add_token(&s, pp_punct(lbrace_punct));
                break;
            } else if (c == '}') {
                scanner_add_token(&s, pp_punct(rbrace_punct));
                break;
            } else if (c == '[') {
                scanner_add_token(&s, pp_multi(lbracket_multi));
                break;
            } else if (c == ']') {
                scanner_add_token(&s, pp_multi(rbracket_multi));
                break;
            } else if (c == ',') {
                scanner_add_token(&s, pp_multi(comma_multi));
                break;
            } else if (c == '~') {
                scanner_add_token(&s, pp_op(approx_op));
                break;
            } else if (c == ' ') {
                s.curr++;
                break;
            } else if (c == '\n') {
                s.curr++;
                s.line++;
                break;
            } else if (c == '|') {
                s.state = or_state;
                break;
            } else if (c == ';') {
                scanner_add_token(&s, pp_punct(semicolon_punct));
                break;
            } else if (scanner_is_digit(c)) {
                s.state = number_state;
                break;
            } else if (scanner_is_nondigit(c)) {
                s.state = ident_state;
                break;
            }
            break;
        }
        case ident_state: {
            if (!scanner_is_nondigit(c) && !scanner_is_digit(c)) {
                scanner_add_token(&s, pp_ident(string_new(&s.src[s.curr],
                                                          --s.index - s.curr)));
                s.state = start_state;
            }
            break;
        }
        case number_state: {
            if ((!scanner_is_digit(c) && !scanner_is_nondigit(c)) && c != '.' &&
                c != '+' && c != '-') {
                scanner_add_token(&s, pp_pp_number(string_new(
                                          &s.src[s.curr], --s.index - s.curr)));
                s.state = start_state;
            }
            break;
        }
        case string_lit_state:
        case wide_string_lit_state:
            if (c == '\n') /* TODO error handling */
                ;
            else if (c == '"') {
                string_lit str = string_new(&s.src[s.curr], s.index - s.curr);
                scanner_add_token(
                    &s, pp_string_lit(str, s.state == wide_string_lit_state));
                s.state = start_state;
            }
            break;
        case star_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(stareq_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_multi(star_multi));
            }
            s.state = start_state;
            break;
        case eq_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(eqeq_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_multi(eq_multi));
            }
            s.state = start_state;
            break;
        case pp_directive_state:
            printf("unimplemented");
            exit(EXIT_FAILURE);
            break;
        case period_state:
            if (c == '.' && s.src[s.index] == '.') {
                s.index++;
                scanner_add_token(&s, pp_punct(ellipsis_punct));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(period_op));
            }
            s.state = start_state;
            break;
        case plus_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(pluseq_op));
            } else if (c == '+') {
                scanner_add_token(&s, pp_op(dblplus_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(plus_op));
            }
            s.state = start_state;
            break;
        case minus_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(minuseq_op));
            } else if (c == '>') {
                scanner_add_token(&s, pp_op(arrow_op));
            } else if (c == '-') {
                scanner_add_token(&s, pp_op(dblminus_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(minus_op));
            }
            s.state = start_state;
            break;
        case lt_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(lteq_op));
            } else if (c == '<') {
                s.state = shiftl_state;
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(lt_op));
            }
            break;
        case gt_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(gteq_op));
            } else if (c == '<') {
                s.state = shiftr_state;
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(gt_op));
            }
            break;
        case and_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(andeq_op));
            } else if (c == '&') {
                scanner_add_token(&s, pp_op(dbland_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(logand_op));
            }
            s.state = start_state;
            break;
        case div_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(diveq_op));
                s.state = start_state;
            } else if (c == '*') {
                s.state = comment_state;
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(div_op));
                s.state = start_state;
            }
            break;
        case percent_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(percenteq_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(percent_op));
            }
            s.state = start_state;
            break;
        case bang_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(bangeq_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(bang_op));
            }
            s.state = start_state;
            break;
        case xor_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(xoreq_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(logxor_op));
            }
            s.state = start_state;
            break;
        case or_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(oreq_op));
            } else if (c == '|') {
                scanner_add_token(&s, pp_op(dblor_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(logor_op));
            }
            s.state = start_state;
            break;
        case shiftl_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(shiftleq_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(shiftl_op));
            }
            s.state = start_state;
            break;
        case shiftr_state:
            if (c == '=') {
                scanner_add_token(&s, pp_op(shiftreq_op));
            } else {
                s.index--;
                scanner_add_token(&s, pp_op(shiftr_op));
            }
            s.state = start_state;
            break;
        case comment_state:
            if (c == '*' && s.src[s.index] == '/') {
                s.index++;
                s.curr = s.index;
                s.state = start_state;
            }
            break;
        }
    }

    return s.tokens;
}
