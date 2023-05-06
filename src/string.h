#ifndef STRING_H
#define STRING_H

#include "utils.h"
#include "vector.h"

DECLARE_VECTOR(char)
TYPEDEF_VECTOR(char, string)
string char_to_string(const char *c);

/* bool string_is_kw(const string *s, token *t); */
string string_new_len(const char *str, int len);
string string_new_raw(const char *str);
void string_append_string(string *a, const string *b);
void string_append_char_star(string *a, const char *b);
bool string_eq(const string *a, const string *b);
bool string_eq_char_star(const string *a, const char *b);
void string_rem_char(string *a, int index, int len);
void string_add_string(string *a, const string *b, int index);
void string_add_char_star(string *a, const char *b, int index);
void string_replace_string(string *a, const string *b, int index, int len);
void string_replace_char_star(string *a, const char *b, int index, int len);

/* djb2 */
unsigned int string_hash(const string *str);

string read_file(char *path);

#endif
