#include "../src/string.h"
#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>

Test(STRING, TESTING) {
    string a, b, c;

    a = string_new_raw("test");
    b = string_new_raw("hello");
    c = string_new_len("testhello", 9);
    cr_assert(a.inner[a.len] == '\0');
    string_append_string(&a, &b);
    cr_assert(a.inner[a.len] == '\0');
    cr_assert(string_eq_char_star(&a, "testhello"));
    cr_assert(string_eq(&a, &c));
    cr_assert(a.len == 9);
    string_append_char_star(&a, "123");
    cr_assert(a.inner[a.len] == '\0');
    cr_assert(string_eq_char_star(&a, "testhello123"));
    cr_assert(a.len == 12);
    string_rem_char(&a, a.len, 0);
    cr_assert(string_eq_char_star(&a, "testhello123"));
    cr_assert(a.len == 12);
    string_rem_char(&a, 0, 1);
    cr_assert(string_eq_char_star(&a, "esthello123"));
    cr_assert(a.len == 11);
    string_rem_char(&a, a.len - 1, 1);
    cr_assert(string_eq_char_star(&a, "esthello12"));
    cr_assert(a.len == 10);
    string_rem_char(&a, 4, 3);
    cr_assert(string_eq_char_star(&a, "estho12"));
    cr_assert(a.len == 7);
    string_add_char_star(&a, "3", a.len);
    cr_assert(string_eq_char_star(&a, "estho123"));
    cr_assert(a.len == 8);
    string_add_char_star(&a, "t", 0);
    cr_assert(string_eq_char_star(&a, "testho123"));
    cr_assert(a.len == 9);
    string_add_string(&a, &b, 0);
    cr_assert(string_eq_char_star(&a, "hellotestho123"));
    cr_assert(a.len == 14);
    string_replace_string(&a, &b, 5, b.len);
    cr_assert(string_eq_char_star(&a, "hellohelloo123"));
    cr_assert(a.len == 14);
    string_replace_char_star(&a, "hi", 5, 2);
    cr_assert(string_eq_char_star(&a, "hellohilloo123"));
    cr_assert(a.len == 14);
    string_replace_string(&a, &b, 5, 3);
    cr_assert(string_eq_char_star(&a, "hellohelloloo123"));
    cr_assert(a.len == 16);
    string_replace_char_star(&a, "hi", 0, 5);
    cr_assert(string_eq_char_star(&a, "hihelloloo123"));
    cr_assert(a.len == 13);

    free(a.inner);
    free(b.inner);
    free(c.inner);
}
