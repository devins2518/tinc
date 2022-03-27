#ifndef STRING_H
#define STRING_H

#include "hash.h"
#include "utils.h"

typedef struct {
    char *str;
    int len;
} string;

/* bool string_is_kw(const string *s, token *t); */
string string_new(char *str, int len);
string string_new_raw(char *str);
string string_append_string(string *a, const string *b);
string string_append_char_star(string *a, const char *b);
bool string_eq(const string *a, const string *b);
bool string_eq_char_star(const string *a, const char *b);
void string_rem_char(string *a, int index, int len);

/* djb2 */
unsigned int string_hash(string *str);

string read_file(char *path);

#endif
