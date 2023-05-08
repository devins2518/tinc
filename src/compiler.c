#include "compiler.h"
#include "parser.h"
#include "preprocessor.h"
#include "scanner.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_to_logical_newline(string *src) {
    unsigned int i;
    for (i = 0; i < src->len; i++) {
        /* Replace EOL characters with new line characters. */
        if (src->inner[i] == '\r' && src->inner[i + 1] == '\n') {
            string_rem_char(src, i, 1);
        }
        /* Translate trigraph sequences. */
        else if (src->inner[i] == '?' && src->inner[i + 1] == '?') {
            switch (src->inner[i + 2]) {
            case '=':
                src->inner[i] = '#';
                string_rem_char(src, i + 1, 2);
                break;
            case '(':
                src->inner[i] = '[';
                string_rem_char(src, i + 1, 2);
                break;
            case ')':
                src->inner[i] = ']';
                string_rem_char(src, i + 1, 2);
                break;
            case '/':
                src->inner[i] = '\\';
                string_rem_char(src, i + 1, 2);
                if (src->inner[i + 1] == '\n') {
                    string_rem_char(src, i, 2);
                }
                break;
            case '\'':
                src->inner[i] = '^';
                string_rem_char(src, i + 1, 2);
                break;
            case '<':
                src->inner[i] = '{';
                string_rem_char(src, i + 1, 2);
                break;
            case '>':
                src->inner[i] = '}';
                string_rem_char(src, i + 1, 2);
                break;
            case '!':
                src->inner[i] = '|';
                string_rem_char(src, i + 1, 2);
                break;
            case '-':
                src->inner[i] = '~';
                string_rem_char(src, i + 1, 2);
                break;
            default:
                break;
            }
        }
        /* Join physical new lines into logical new lines. */
        else if (src->inner[i] == '\\' && src->inner[i + 1] == '\n') {
            string_rem_char(src, i, 2);
        }
    }
}

vector_pp_token pre_preprocessing(char *path) {
    string src = read_file(path);
    vector_pp_token tokens;
    preprocessor pp = preprocessor_new(&src);
    /* Translation phases 1-2 */
    convert_to_logical_newline(&src);
    /* Translation phase 3-4 */
    tokens = preprocessor_run(&pp);
    string_free(src);
    preprocessor_free(pp);
    return tokens;
}

void compile_file(char *path) {
    vector_pp_token tokens;
    tokens = pre_preprocessing(path);
    /* vector_pp_token_print(&tokens); */
    generate_ast(&tokens);
    vector_pp_token_free(tokens);
}
