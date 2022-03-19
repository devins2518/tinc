#include "compiler.h"
#include "scanner.h"
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
                if (src->str[i + 1] == '\n') {
                    string_rem_char(src, i, 2);
                }
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
        /* Join physical new lines into logical new lines. */
        else if (src->str[i] == '\\' && src->str[i + 1] == '\n') {
            string_rem_char(src, i, 2);
        }
    }
}

void compile_file(char *path) {
    string src = read_file(path);
    /* Translation phases 1-2 */
    convert_to_logical_newline(&src);
    /* Translation phases 3-4 */
    scan_file(&src);
    free(src.str);
    printf("%s\n", src.str);
}
