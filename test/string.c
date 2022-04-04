#include "../src/string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    string a, b, c;

    a = string_new_raw("test");
    b = string_new_raw("hello");
    c = string_new("testhello", 9);
    assert(a.inner[a.len] == '\0');
    string_append_string(&a, &b);
    assert(a.inner[a.len] == '\0');
    assert(string_eq_char_star(&a, "testhello"));
    assert(string_eq(&a, &c));
    assert(a.len == 9);
    string_append_char_star(&a, "123");
    assert(a.inner[a.len] == '\0');
    assert(string_eq_char_star(&a, "testhello123"));
    assert(a.len == 12);
    string_rem_char(&a, a.len, 0);
    assert(string_eq_char_star(&a, "testhello123"));
    assert(a.len == 12);
    string_rem_char(&a, 0, 1);
    assert(string_eq_char_star(&a, "esthello123"));
    assert(a.len == 11);
    string_rem_char(&a, a.len - 1, 1);
    assert(string_eq_char_star(&a, "esthello12"));
    assert(a.len == 10);
    string_rem_char(&a, 4, 3);
    assert(string_eq_char_star(&a, "estho12"));
    assert(a.len == 7);
    string_add_char_star(&a, "3", a.len);
    assert(string_eq_char_star(&a, "estho123"));
    assert(a.len == 8);
    string_add_char_star(&a, "t", 0);
    assert(string_eq_char_star(&a, "testho123"));
    assert(a.len == 9);
    string_add_string(&a, &b, 0);
    assert(string_eq_char_star(&a, "hellotestho123"));
    assert(a.len == 14);

    free(a.inner);
    free(b.inner);
    free(c.inner);
    return 0;
}
