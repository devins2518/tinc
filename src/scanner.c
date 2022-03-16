#include "scanner.h"
#include "token.h"
#include "utils.h"
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
    int len;
    int cap;
    scanning_token *tokens;
} scanner;

scanner *scanner_new(char *src) {
    scanner *s = malloc(sizeof(scanner));
    s->src = src;
    s->src_len = strlen(src);
    s->curr = 0;
    s->index = 0;
    s->line = 0;
    s->len = 0;
    s->cap = 16;
    s->tokens = malloc(s->cap * sizeof(scanning_token));
    return (s->tokens) ? s : NULL;
}

void scanner_free(scanner *s) { free(s); }

bool scanner_add_token(scanner *s, scanning_token t) {
    if (s->len > s->cap) {
        s->cap <<= 2;
        s->tokens = realloc(s->tokens, (s->cap) * sizeof(scanning_token));
        if (s->tokens == NULL)
            return false;
    }
    s->curr = s->index;
    s->tokens[s->len++] = t;
    return true;
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

bool scanner_is_kw(const string *s, scanning_token *t) {
    bool ret = false;
    if (string_eq_char(s, "auto")) {
        t->keyword = auto_kw;
        ret = true;
    } else if (string_eq_char(s, "break")) {
        t->keyword = break_kw;
        ret = true;
    } else if (string_eq_char(s, "case")) {
        t->keyword = case_kw;
        ret = true;
    } else if (string_eq_char(s, "char")) {
        t->keyword = char_kw;
        ret = true;
    } else if (string_eq_char(s, "const")) {
        t->keyword = const_kw;
        ret = true;
    } else if (string_eq_char(s, "continue")) {
        t->keyword = continue_kw;
        ret = true;
    } else if (string_eq_char(s, "default")) {
        t->keyword = default_kw;
        ret = true;
    } else if (string_eq_char(s, "do")) {
        t->keyword = do_kw;
        ret = true;
    } else if (string_eq_char(s, "double")) {
        t->keyword = double_kw;
        ret = true;
    } else if (string_eq_char(s, "else")) {
        t->keyword = else_kw;
        ret = true;
    } else if (string_eq_char(s, "enum")) {
        t->keyword = enum_kw;
        ret = true;
    } else if (string_eq_char(s, "extern")) {
        t->keyword = extern_kw;
        ret = true;
    } else if (string_eq_char(s, "float")) {
        t->keyword = float_kw;
        ret = true;
    } else if (string_eq_char(s, "for")) {
        t->keyword = for_kw;
        ret = true;
    } else if (string_eq_char(s, "goto")) {
        t->keyword = goto_kw;
        ret = true;
    } else if (string_eq_char(s, "if")) {
        t->keyword = if_kw;
        ret = true;
    } else if (string_eq_char(s, "int")) {
        t->keyword = int_kw;
        ret = true;
    } else if (string_eq_char(s, "long")) {
        t->keyword = long_kw;
        ret = true;
    } else if (string_eq_char(s, "register")) {
        t->keyword = register_kw;
        ret = true;
    } else if (string_eq_char(s, "return")) {
        t->keyword = return_kw;
        ret = true;
    } else if (string_eq_char(s, "short")) {
        t->keyword = short_kw;
        ret = true;
    } else if (string_eq_char(s, "signed")) {
        t->keyword = signed_kw;
        ret = true;
    } else if (string_eq_char(s, "sizeof")) {
        t->keyword = sizeof_kw;
        ret = true;
    } else if (string_eq_char(s, "static")) {
        t->keyword = static_kw;
        ret = true;
    } else if (string_eq_char(s, "struct")) {
        t->keyword = struct_kw;
        ret = true;
    } else if (string_eq_char(s, "switch")) {
        t->keyword = switch_kw;
        ret = true;
    } else if (string_eq_char(s, "typedef")) {
        t->keyword = typedef_kw;
        ret = true;
    } else if (string_eq_char(s, "union")) {
        t->keyword = union_kw;
        ret = true;
    } else if (string_eq_char(s, "unsigned")) {
        t->keyword = unsigned_kw;
        ret = true;
    } else if (string_eq_char(s, "void")) {
        t->keyword = void_kw;
        ret = true;
    } else if (string_eq_char(s, "volatile")) {
        t->keyword = volatile_kw;
        ret = true;
    } else if (string_eq_char(s, "while")) {
        t->keyword = while_kw;
        ret = true;
    }

    return ret;
}

bool scanner_is_s_char(scanner *s, scanning_token *t) {
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

void scanner_scan_string_lit(scanner *s, scanning_token *t) {
    string str;
    while (scanner_is_s_char(s, t)) {
        s->index++;
    }
    str = string_new(&s->src[s->curr], s->index - s->curr);
    t->string_lit = str;
}

scanning_token *scan_file(char *path, int *size) {
    FILE *fd;
    int len;
    char *src;
    scanner *s;

    /* Read file */
    fd = fopen(path, "rb");
    if (fd != NULL) {
        fseek(fd, 0, SEEK_END);
        len = ftell(fd);
        fseek(fd, 0, SEEK_SET);
        src = malloc(len + 1);
        fread(src, len, 1, fd);
        fclose(fd);

        /* Scan it */
        s = scanner_new(src);
        assert(s != NULL);

        /* TODO */
        while (s->index <= s->src_len) {
            scanning_token t;
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
                string str;
                while (scanner_in_ident(s->src[s->index++])) {}
                str = string_new(&s->src[s->curr], s->index - s->curr);
                if (!scanner_is_kw(&str, &t)) {
                    t.ident = str;
                }
                scanner_add_token(s, t);
                break;
            }
            case ' ':
                break;
            case '\n':
                s->line++;
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
            case ':':
                t.multi = colon_multi;
                scanner_add_token(s, t);
                break;
            case '=':
                t.multi = eq_multi;
                scanner_add_token(s, t);
                break;
            case '#':
                t.multi = hash_multi;
                scanner_add_token(s, t);
                break;
            case '.':
                t.multi = period_multi;
                scanner_add_token(s, t);
                break;
            case '+':
                t.multi = plus_multi;
                scanner_add_token(s, t);
                break;
            case '-':
                t.multi = minus_multi;
                scanner_add_token(s, t);
                break;
            case '<':
                t.multi = lt_multi;
                scanner_add_token(s, t);
                break;
            case '>':
                t.multi = gt_multi;
                scanner_add_token(s, t);
                break;
            case '&':
                t.multi = and_multi;
                scanner_add_token(s, t);
                break;
            case '/':
                t.multi = div_multi;
                scanner_add_token(s, t);
                break;
            case '%':
                t.multi = percent_multi;
                scanner_add_token(s, t);
                break;
            case '!':
                t.multi = bang_multi;
                scanner_add_token(s, t);
                break;
            case '^':
                t.multi = xor_multi;
                scanner_add_token(s, t);
                break;
            case '|':
                t.multi = or_multi;
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

        *size = s->len;
        return s->tokens;
    } else {
        printf("Failed to read file\n");
        exit(EXIT_FAILURE);
    }
}
