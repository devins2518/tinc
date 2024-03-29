#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

IMPL_VECTOR(char)
IMPL_TYPEDEF_VECTOR(char, string)

string char_to_string(const char *c) {
    return string_new_len(c, 1);
}

string string_new_len(const char *str, int len) {
    string s;
    char *inner;
    s = string_new_reserve(len);
    inner = string_get_inner(&s);
    strncat(inner, str, len);
    s.len = len;
    return s;
}

string string_new_raw(const char *str) {
    int len = strlen(str);
    return string_new_len(str, len);
}

void string_append_string(string *a, const string *b) {
    string_reserve(a, a->len + b->len);
    strncat(a->inner, b->inner, b->len);
    a->len += b->len;
}

void string_append_char_star(string *a, const char *b) {
    int len = strlen(b);
    string_reserve(a, a->len + len);
    strncat(a->inner, b, len);
    a->len += len;
}

bool string_eq(const string *a, const string *b) {
    if (a->len != b->len) {
        return false;
    } else {
        return strncmp(a->inner, b->inner, a->len) == 0;
    }
}

bool string_eq_char_star(const string *a, const char *b) {
    if (a->len != strlen(b)) {
        return false;
    } else {
        return strncmp(a->inner, b, a->len) == 0;
    }
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

void string_add_string(string *a, const string *b, int index) {
    vector_char_reserve(a, a->len + b->len);
    memcpy(&a->inner[index + b->len], &a->inner[index], a->len - index);
    memcpy(&a->inner[index], b->inner, b->len);
    a->len += b->len;
    a->inner[a->len] = '\0';
}

void string_add_char_star(string *a, const char *b, int index) {
    int len = strlen(b);
    vector_char_reserve(a, a->len + len);
    memcpy(&a->inner[index + len], &a->inner[index], a->len - index);
    memcpy(&a->inner[index], b, len);
    a->len += len;
    a->inner[a->len] = '\0';
}

void string_replace_string(string *a, const string *b, int index, int len) {
    string_rem_char(a, index, len);
    string_add_string(a, b, index);
}

void string_replace_char_star(string *a, const char *b, int index, int len) {
    string_rem_char(a, index, len);
    string_add_char_star(a, b, index);
}

unsigned int string_hash(const string *str) {
    unsigned int hash = 5381;
    int c;
    char *index = str->inner;

    while ((c = *index++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
