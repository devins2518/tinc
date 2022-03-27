#include "ast.h"
#include "compiler.h"
#include "preprocessor.h"
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

vector_pp_token pre_preprocessing(char *path) {
    preprocessor p = preprocessor_new();
    string src = read_file(path);
    vector_pp_token tokens;
    /* Translation phases 1-2 */
    convert_to_logical_newline(&src);
    /* Translation phase 3 */
    tokens = scan_file(&src);
    /* Translation phase 4
     * run_preprocessor(&p, &tokens); */
    return tokens;
}

void compile_file(char *path) {
    vector_pp_token tokens;
    tokens = pre_preprocessing(path);
    vector_pp_token_print(&tokens);
    generate_ast(&tokens);
}
