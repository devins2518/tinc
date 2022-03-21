#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string string_new(char *str, int len) {
    string s;
    s.str = str;
    s.len = len;
    return s;
}

string string_new_raw(char *str) {
    string s;
    s.str = str;
    s.len = strlen(str);
    return s;
}

bool string_eq(const string *a, const string *b) {
    bool ret = true;
    int i;

    if (a->len != b->len) {
        ret = false;
    } else {
        for (i = 0; i <= a->len; i++) {
            if (a->str[i] != b->str[i]) {
                ret = false;
                break;
            }
        }
    }

    return ret;
}

bool string_eq_char(const string *a, const char *b) {
    bool ret = true;
    int i;

    for (i = 0; i <= a->len; i++) {
        if ((b[i] == '\0') || (a->str[i] != b[i])) {
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
    fread(src, len, 1, fd);
    fclose(fd);
    s.str = src;
    s.len = len;

    return s;
}

void string_rem_char(string *a, int index, int len) {
    memmove(&a->str[index], &a->str[index + len], a->len - index - len);
    a->len -= len;
    a->str[a->len] = '\0';
}
