#ifndef STRING_H
#define STRING_H

#include "utils.h"

typedef struct {
    char *str;
    int len;
} string;

/* bool string_is_kw(const string *s, token *t); */
string string_new(char *str, int len);
string string_new_raw(char *str);
bool string_eq(const string *a, const string *b);
bool string_eq_char(const string *a, const char *b);
void string_rem_char(string *a, int index, int len);

string read_file(char *path);

#endif
