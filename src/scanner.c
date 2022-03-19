#include "scanner.h"
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

scanner *scanner_new(char *src) {
    scanner *s = malloc(sizeof(scanner));
    s->src = src;
    s->src_len = strlen(src);
    s->curr = 0;
    s->index = 0;
    s->line = 0;
    s->tokens = vector_pp_token_new();
    return s;
}

void scanner_free(scanner *s) { free(s); }

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

bool scanner_is_s_char(scanner *s, pp_token *t) {
    bool ret = true;
    switch (s->src[s->index]) {
    case '\n':
        t->error = error_new(
            s->curr, s->index,
            "The newline character (\\n) cannot be part of a string literal.");
    case '"':
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

void scanner_scan_string_lit(scanner *s, pp_token *t) {
    string str;
    while (scanner_is_s_char(s, t)) {
        s->index++;
    }
    str = string_new(&s->src[s->curr], s->index - s->curr);
    t->string_lit = str;
}

void scanner_scan_constant(scanner *s, pp_token *t) {
    printf("unimplemented");
    abort();
}

pp_token *scan_file(string *str) {
    scanner *s;

    s = scanner_new(str->str);
    assert(s != NULL);

    /* TODO */
    while (s->index <= s->src_len) {
        pp_token t;
        switch (s->src[s->index++]) {
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
            if (s->src[s->index] == '"') {
                s->index++;
                scanner_scan_string_lit(s, &t);
                scanner_add_token(s, t);
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
            while (scanner_in_ident(s->src[s->index++])) {}
            t.ident = string_new(&s->src[s->curr], s->index - s->curr);
            scanner_add_token(s, t);
            break;
        }
        case ' ':
            t.whitespace = space;
            scanner_add_token(s, t);
            break;
        case '\n':
            s->line++;
            t.whitespace = newline;
            scanner_add_token(s, t);
            break;
        case '[':
            t.multi = lbracket_multi;
            scanner_add_token(s, t);
            break;
        case ']':
            t.multi = rbracket_multi;
            scanner_add_token(s, t);
            break;
        case '(':
            t.multi = lparen_multi;
            scanner_add_token(s, t);
            break;
        case ')':
            t.multi = rparen_multi;
            scanner_add_token(s, t);
            break;
        case '*':
            t.multi = star_multi;
            scanner_add_token(s, t);
            break;
        case ',':
            t.multi = comma_multi;
            scanner_add_token(s, t);
            break;
        case '=':
            t.multi = eq_multi;
            scanner_add_token(s, t);
            break;
        case '#':
            if (s->src[s->index] == '#') {
                s->index++;
                t.op = dblhash_op;
            } else {
                t.multi = hash_multi;
            }
            scanner_add_token(s, t);
            break;
        case ':':
            t.multi = colon_multi;
            scanner_add_token(s, t);
            break;
        case '.':
            t.op = period_op;
            scanner_add_token(s, t);
            break;
        case '+':
            if (s->src[s->index] == '+') {
                s->index++;
                t.op = dblplus_op;
            } else if (s->src[s->index] == '=') {
                s->index++;
                t.op = pluseq_op;
            } else {
                t.op = plus_op;
            }
            scanner_add_token(s, t);
            break;
        case '-':
            if (s->src[s->index] == '-') {
                s->index++;
                t.op = dblminus_op;
            } else if (s->src[s->index] == '=') {
                s->index++;
                t.op = minuseq_op;
            } else if (s->src[s->index] == '>') {
                s->index++;
                t.op = arrow_op;
            } else {
                t.op = minus_op;
            }
            scanner_add_token(s, t);
            break;
        case '<':
            if (s->src[s->index] == '<') {
                s->index++;
                if (s->src[s->index] == '=') {
                    s->index++;
                    t.op = shiftleq_op;
                } else {
                    t.op = shiftl_op;
                }
            } else if (s->src[s->index] == '=') {
                s->index++;
                t.op = lteq_op;
            } else {
                t.op = lt_op;
            }
            scanner_add_token(s, t);
            break;
        case '>':
            if (s->src[s->index] == '>') {
                s->index++;
                if (s->src[s->index] == '=') {
                    s->index++;
                    t.op = shiftreq_op;
                } else {
                    t.op = shiftr_op;
                }
            } else if (s->src[s->index] == '=') {
                s->index++;
                t.op = gteq_op;
            } else {
                t.op = gt_op;
            }
            scanner_add_token(s, t);
            break;
        case '&':
            if (s->src[s->index] == '&') {
                s->index++;
                t.op = dbland_op;
            } else if (s->src[s->index] == '=') {
                s->index++;
                t.op = andeq_op;
            } else {
                t.op = logand_op;
            }
            scanner_add_token(s, t);
            break;
        case '/':
            if (s->src[s->index] == '=') {
                s->index++;
                t.op = diveq_op;
            } else {
                t.op = div_op;
            }
            scanner_add_token(s, t);
            break;
        case '%':
            if (s->src[s->index] == '=') {
                s->index++;
                t.op = percenteq_op;
            } else {
                t.op = percent_op;
            }
            scanner_add_token(s, t);
            break;
        case '!':
            if (s->src[s->index] == '=') {
                s->index++;
                t.op = bangeq_op;
            } else {
                t.op = bang_op;
            }
            scanner_add_token(s, t);
            break;
        case '^':
            if (s->src[s->index] == '=') {
                s->index++;
                t.op = xoreq_op;
            } else {
                t.op = logxor_op;
            }
            scanner_add_token(s, t);
            break;
        case '|':
            if (s->src[s->index] == '|') {
                s->index++;
                t.op = dblor_op;
            }
            if (s->src[s->index] == '=') {
                s->index++;
                t.op = oreq_op;
            } else {
                t.op = logor_op;
            }
            scanner_add_token(s, t);
            break;
        case '{':
            t.punct = lbrace_punct;
            scanner_add_token(s, t);
            break;
        case '}':
            t.punct = rbrace_punct;
            scanner_add_token(s, t);
            break;
        case ';':
            t.punct = semicolon_punct;
            scanner_add_token(s, t);
            break;
        case '~':
            t.op = approx_op;
            scanner_add_token(s, t);
            break;
        case '?':
            t.op = ternaryq_op;
            scanner_add_token(s, t);
            break;
        case '"': {
            scanner_scan_string_lit(s, &t);
            scanner_add_token(s, t);
            break;
        }

        default:
            break;
        }
    }

    return vector_pp_token_get_inner(&s->tokens);
}
