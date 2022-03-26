#include "generic.h"
#include "token.h"
#include "utils.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *src;
    int src_len;
    int curr;  /* start of the in progress scan */
    int index; /* current index of the scan */
    int line;
    vector_pp_token tokens;
} scanner;

scanner scanner_new(char *src) {
    scanner s;
    s.src = src;
    s.src_len = strlen(src);
    s.curr = 0;
    s.index = 0;
    s.line = 0;
    s.tokens = vector_pp_token_new();
    return s;
}

bool scanner_add_token(scanner *s, pp_token t) {
    if (vector_pp_token_add(&s->tokens, t)) {
        s->curr = s->index;
        return true;
    } else {
        return false;
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

bool scanner_is_digit(scanner *s) {
    bool ret = false;
    switch (s->src[s->index]) {
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
        ret = true;
    default:
        break;
    }
    return ret;
}

bool scanner_is_nondigit(scanner *s) {
    bool ret = false;
    switch (s->src[s->index]) {
    case '_':
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
        ret = true;
    default:
        break;
    }
    return ret;
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

ident scanner_scan_ident(scanner *s) {
    while (scanner_is_nondigit(s) || scanner_is_digit(s)) {
        s->index++;
    }
    return string_new(&s->src[s->curr], s->index - s->curr);
}

pp_number scanner_scan_pp_number(scanner *s) {
    while (scanner_is_digit(s) || scanner_is_nondigit(s) ||
           s->src[s->index] == '.' || s->src[s->index] == '_' ||
           s->src[s->index] == '-' || s->src[s->index] == '+') {
        s->index++;
    }
    return string_new(&s->src[s->curr], s->index - s->curr);
}

string_lit scanner_scan_string_lit(scanner *s) {
    while (scanner_is_s_char(s)) {
        s->index++;
    }
    return string_new(&s->src[s->curr], s->index - s->curr);
}

header_name scanner_scan_header_name(scanner *s) {
    while (scanner_is_h_char(s->src[s->index])) {
        s->index++;
    }
    return string_new(&s->src[s->curr], s->index - s->curr);
}

vector_pp_token scan_file(string *str) {
    scanner s;

    s = scanner_new(str->str);

    /* TODO */
    while (s.index <= s.src_len) {
        pp_token t;
        switch (s.src[s.index++]) {
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
            if (s.src[s.index] == '"') {
                s.index++;
                t = pp_string_lit(scanner_scan_string_lit(&s));
                scanner_add_token(&s, t);
                break;
            }
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
        case '_': {
            t = pp_ident(scanner_scan_ident(&s));
            scanner_add_token(&s, t);
            break;
        }
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            t = pp_pp_number(scanner_scan_pp_number(&s));
            scanner_add_token(&s, t);
            break;
        }
        case ' ':
            t = pp_whitespace(space);
            scanner_add_token(&s, t);
            break;
        case '\n':
            s.line++;
            t = pp_whitespace(newline);
            scanner_add_token(&s, t);
            break;
        case '[':
            t = pp_multi(lbracket_multi);
            scanner_add_token(&s, t);
            break;
        case ']':
            t = pp_multi(rbracket_multi);
            scanner_add_token(&s, t);
            break;
        case '(':
            t = pp_multi(lparen_multi);
            scanner_add_token(&s, t);
            break;
        case ')':
            t = pp_multi(rparen_multi);
            scanner_add_token(&s, t);
            break;
        case '*':
            t = pp_multi(star_multi);
            scanner_add_token(&s, t);
            break;
        case ',':
            t = pp_multi(comma_multi);
            scanner_add_token(&s, t);
            break;
        case '=':
            t = pp_multi(eq_multi);
            scanner_add_token(&s, t);
            break;
        case '#':
            if ((s.index - 2) < 0 || s.src[s.index - 2] == '\n') {
                t = pp_punct(hash_punct);
            } else if (s.src[s.index] == '#') {
                s.index++;
                t = pp_op(dblhash_op);
            } else {
                int i;
                bool found_hash = false;
                for (i = s.index; i > s.src_len; i--) {
                    if (s.src[i] == '\n') {
                        if (s.src[i + 1] == '#')
                            found_hash = true;
                        break;
                    }
                }
                if (found_hash)
                    t = pp_op(hash_op);
                else
                    t = pp_error(s.curr, s.index,
                                 "# is to only be used in "
                                 "preprocessing directives.");
            }
            scanner_add_token(&s, t);
            break;
        case ':':
            t = pp_multi(colon_multi);
            scanner_add_token(&s, t);
            break;
        case '.':
            if (scanner_is_digit(&s)) {
                t = pp_pp_number(scanner_scan_pp_number(&s));
            } else {
                t = pp_op(period_op);
            }
            scanner_add_token(&s, t);
            break;
        case '+':
            if (s.src[s.index] == '+') {
                s.index++;
                t = pp_op(dblplus_op);
            } else if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(pluseq_op);
            } else {
                t = pp_op(plus_op);
            }
            scanner_add_token(&s, t);
            break;
        case '-':
            if (s.src[s.index] == '-') {
                s.index++;
                t = pp_op(dblminus_op);
            } else if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(minuseq_op);
            } else if (s.src[s.index] == '>') {
                s.index++;
                t = pp_op(arrow_op);
            } else {
                t = pp_op(minus_op);
            }
            scanner_add_token(&s, t);
            break;
        case '<':
            if (s.src[s.index] == '<') {
                s.index++;
                if (s.src[s.index] == '=') {
                    s.index++;
                    t = pp_op(shiftleq_op);
                } else {
                    t = pp_op(shiftl_op);
                }
            } else if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(lteq_op);
            } else if (scanner_is_h_char(s.src[s.index])) {
                s.index++;
                t = pp_header_name(scanner_scan_header_name(&s));
            } else {
                t = pp_op(lt_op);
            }
            scanner_add_token(&s, t);
            break;
        case '>':
            if (s.src[s.index] == '>') {
                s.index++;
                if (s.src[s.index] == '=') {
                    s.index++;
                    t = pp_op(shiftreq_op);
                } else {
                    t = pp_op(shiftr_op);
                }
            } else if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(gteq_op);
            } else {
                t = pp_op(gt_op);
            }
            scanner_add_token(&s, t);
            break;
        case '&':
            if (s.src[s.index] == '&') {
                s.index++;
                t = pp_op(dbland_op);
            } else if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(andeq_op);
            } else {
                t = pp_op(logand_op);
            }
            scanner_add_token(&s, t);
            break;
        case '/':
            if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(diveq_op);
            } else if (s.src[s.index] == '/') {
                while (s.src[s.index] != '\n') {
                    s.index++;
                }
                break;
            } else if (s.src[s.index] == '*') {
                s.index++;
                while ((s.src[s.index] != '*') && (s.src[s.index + 1] != '/')) {
                    s.index++;
                }
                s.index += 2;
                break;
            } else {
                t = pp_op(div_op);
            }
            scanner_add_token(&s, t);
            break;
        case '%':
            if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(percenteq_op);
            } else {
                t = pp_op(percent_op);
            }
            scanner_add_token(&s, t);
            break;
        case '!':
            if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(bangeq_op);
            } else {
                t = pp_op(bang_op);
            }
            scanner_add_token(&s, t);
            break;
        case '^':
            if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(xoreq_op);
            } else {
                t = pp_op(logxor_op);
            }
            scanner_add_token(&s, t);
            break;
        case '|':
            if (s.src[s.index] == '|') {
                s.index++;
                t = pp_op(dblor_op);
            }
            if (s.src[s.index] == '=') {
                s.index++;
                t = pp_op(oreq_op);
            } else {
                t = pp_op(logor_op);
            }
            scanner_add_token(&s, t);
            break;
        case '{':
            t = pp_punct(lbrace_punct);
            scanner_add_token(&s, t);
            break;
        case '}':
            t = pp_punct(rbrace_punct);
            scanner_add_token(&s, t);
            break;
        case ';':
            t = pp_punct(semicolon_punct);
            scanner_add_token(&s, t);
            break;
        case '~':
            t = pp_op(approx_op);
            scanner_add_token(&s, t);
            break;
        case '?':
            t = pp_op(ternaryq_op);
            scanner_add_token(&s, t);
            break;
        case '"': {
            t = pp_string_lit(scanner_scan_string_lit(&s));
            scanner_add_token(&s, t);
            break;
        }

        default:
            break;
        }
    }

    return s.tokens;
}
