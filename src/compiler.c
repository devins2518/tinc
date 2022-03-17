#include "compiler.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_to_logical_newline(string *src) {
    int i;
    for (i = 0; i < src->len; i++) {
        /* Replace EOL characters with new line characters. */
        if (src->str[i] == '\r' && src->str[i + 1] == '\n') {
            string_rem_char(src, i, 1);
        }
        /* Translate trigraph sequences. */
        else if (src->str[i] == '?' && src->str[i + 1] == '?') {
            switch (src->str[i + 2]) {
            case '=':
                src->str[i] = '#';
                string_rem_char(src, i + 1, 2);
                break;
            case '(':
                src->str[i] = '[';
                string_rem_char(src, i + 1, 2);
                break;
            case ')':
                src->str[i] = ']';
                string_rem_char(src, i + 1, 2);
                break;
            case '/':
                src->str[i] = '\\';
                string_rem_char(src, i + 1, 2);
                break;
            case '\'':
                src->str[i] = '^';
                string_rem_char(src, i + 1, 2);
                break;
            case '<':
                src->str[i] = '{';
                string_rem_char(src, i + 1, 2);
                break;
            case '>':
                src->str[i] = '}';
                string_rem_char(src, i + 1, 2);
                break;
            case '!':
                src->str[i] = '|';
                string_rem_char(src, i + 1, 2);
                break;
            case '-':
                src->str[i] = '~';
                string_rem_char(src, i + 1, 2);
                break;
            default:
                break;
            }
        }
    }
}

void compile_file(char *path) {
    string src = read_file(path);
    convert_to_logical_newline(&src);
    printf("%s\n", src.str);
}
