#ifndef UTILS_H
#define UTILS_H

#define bool int
#define false 0
#define true 1

typedef struct {
    char *str;
    int len;
} string;

/* bool string_is_kw(const string *s, token *t); */
string string_new(char *str, int len);
bool string_eq(const string *a, const string *b);
bool string_eq_char(const string *a, const char *b);

string read_file(char *path);

#endif
