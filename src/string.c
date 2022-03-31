#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IMPL_VECTOR(char)

string char_print(char *c) { return string_new(c, 1); }

string string_new(char *str, int len) {
    string s;
    char *inner;
    s = vector_char_new_reserve(len + 1);
    inner = vector_char_get_inner(&s);
    strncat(inner, str, len);
    s.len = len;
    return s;
}

string string_new_raw(char *str) {
    int len = strlen(str);
    return string_new(str, len + 1);
}

void string_append_string(string *a, const string *b) {
    vector_char_reserve(a, a->len + b->len + 1);
    strncat(a->inner + b->len, b->inner, b->len);
    a->len += b->len;
}

void string_append_char_star(string *a, const char *b) {
    int len = strlen(b);
    vector_char_reserve(a, a->len + len + 2);
    strncat(a->inner + len, b, len);
    a->len += len;
}

bool string_eq(const string *a, const string *b) {
    bool ret = true;
    int i;

    if (a->len != b->len) {
        ret = false;
    } else {
        for (i = 0; i <= a->len; i++) {
            if (a->inner[i] != b->inner[i]) {
                ret = false;
                break;
            }
        }
    }

    return ret;
}

bool string_eq_char_star(const string *a, const char *b) {
    bool ret = true;
    int i;

    for (i = 0; i <= a->len; i++) {
        if ((b[i] == '\0' && i != a->len) || (a->inner[i] != b[i])) {
            ret = false;
            break;
        }
    }

    return ret;
}

string read_file(char *path) {
    FILE *fd;
    int len;
    char *src;
    string s;
    fd = fopen(path, "rb");
    if (fd == NULL) {
        printf("Could not open path %s\n", path);
        exit(EXIT_FAILURE);
    }
    fseek(fd, 0, SEEK_END);
    len = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    src = malloc(len + 1);
    if (src == NULL) {
        printf("Failed to allocate for file %s", path);
        exit(EXIT_FAILURE);
    }
    fread(src, len, 1, fd);
    fclose(fd);
    s.inner = src;
    s.len = len;

    return s;
}

void string_rem_char(string *a, int index, int len) {
    memmove(&a->inner[index], &a->inner[index + len], a->len - index - len);
    a->len -= len;
    a->inner[a->len] = '\0';
}

unsigned int string_hash(string *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str->inner++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
