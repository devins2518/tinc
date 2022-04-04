#ifndef STRING_H
#define STRING_H

#include "utils.h"
#include "vector.h"

DECLARE_VECTOR(char)
typedef vector_char string;
string char_to_string(char *c);

/* bool string_is_kw(const string *s, token *t); */
string string_new(char *str, int len);
string string_new_raw(char *str);
void string_append_string(string *a, const string *b);
void string_append_char_star(string *a, const char *b);
bool string_eq(const string *a, const string *b);
bool string_eq_char_star(const string *a, const char *b);
void string_rem_char(string *a, int index, int len);
void string_add_string(string *a, const string *b, int index);
void string_add_char_star(string *a, const char *b, int index);

/* djb2 */
unsigned int string_hash(string *str);

string read_file(char *path);

#endif
