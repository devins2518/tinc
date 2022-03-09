#include "scanner.h"
#include "token.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *src;
    int src_len;
    int start;
    int index;
    int line;
    int len;
    int cap;
    token *tokens;
} scanner;

scanner *scanner_new(char *src) {
    scanner *s = malloc(sizeof(scanner));
    s->src = src;
    s->src_len = strlen(src);
    s->start = 0;
    s->index = 0;
    s->line = 0;
    s->len = 0;
    s->cap = 16;
    s->tokens = malloc(s->cap * sizeof(token));
    return (s->tokens) ? s : NULL;
}

void scanner_free(scanner *s) { free(s); }

bool scanner_add_token(scanner *s, token t) {
    if (s->len > s->cap) {
        s->cap <<= 2;
        s->tokens = realloc(s->tokens, (s->cap) * sizeof(token));
        if (s->tokens == NULL)
            return false;
    }
    s->tokens[s->len++] = t;
    return true;
}

token *scan_file(char *path, int *size) {
    // Read file
    FILE *fd;
    int len;
    char *src;
    scanner *s;
    fd = fopen(path, "rb");
    if (fd != NULL) {
        fseek(fd, 0, SEEK_END);
        len = ftell(fd);
        fseek(fd, 0, SEEK_SET);
        src = malloc(len + 1);
        fread(src, len, 1, fd);
        fclose(fd);

        // Scan it
        s = scanner_new(src);
        assert(s != NULL);

        /* TODO */
        while (s->index <= s->src_len) {
            token t;
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
                break;
            case ' ': {
                t.ident.name = &s->src[s->start];
                t.ident.size = s->index - s->start;
                scanner_add_token(s, t);
                s->start = s->index;
                break;
            }
            case '\n':
                s->line++;
                break;
            default:
                break;
            }
            s->start++;
        }

        *size = s->len;
        return s->tokens;
    } else {
        printf("Failed to read file\n");
        exit(EXIT_FAILURE);
    }
}
