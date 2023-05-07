#include "../src/string.h"
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>

CTEST(STRING, TESTING) {
    string a, b, c;

    a = string_new_raw("test");
    b = string_new_raw("hello");
    c = string_new_len("testhello", 9);
    ASSERT_TRUE(a.inner[a.len] == '\0');
    string_append_string(&a, &b);
    ASSERT_TRUE(a.inner[a.len] == '\0');
    ASSERT_TRUE(string_eq_char_star(&a, "testhello"));
    ASSERT_TRUE(string_eq(&a, &c));
    ASSERT_TRUE(a.len == 9);
    string_append_char_star(&a, "123");
    ASSERT_TRUE(a.inner[a.len] == '\0');
    ASSERT_TRUE(string_eq_char_star(&a, "testhello123"));
    ASSERT_TRUE(a.len == 12);
    string_rem_char(&a, a.len, 0);
    ASSERT_TRUE(string_eq_char_star(&a, "testhello123"));
    ASSERT_TRUE(a.len == 12);
    string_rem_char(&a, 0, 1);
    ASSERT_TRUE(string_eq_char_star(&a, "esthello123"));
    ASSERT_TRUE(a.len == 11);
    string_rem_char(&a, a.len - 1, 1);
    ASSERT_TRUE(string_eq_char_star(&a, "esthello12"));
    ASSERT_TRUE(a.len == 10);
    string_rem_char(&a, 4, 3);
    ASSERT_TRUE(string_eq_char_star(&a, "estho12"));
    ASSERT_TRUE(a.len == 7);
    string_add_char_star(&a, "3", a.len);
    ASSERT_TRUE(string_eq_char_star(&a, "estho123"));
    ASSERT_TRUE(a.len == 8);
    string_add_char_star(&a, "t", 0);
    ASSERT_TRUE(string_eq_char_star(&a, "testho123"));
    ASSERT_TRUE(a.len == 9);
    string_add_string(&a, &b, 0);
    ASSERT_TRUE(string_eq_char_star(&a, "hellotestho123"));
    ASSERT_TRUE(a.len == 14);
    string_replace_string(&a, &b, 5, b.len);
    ASSERT_TRUE(string_eq_char_star(&a, "hellohelloo123"));
    ASSERT_TRUE(a.len == 14);
    string_replace_char_star(&a, "hi", 5, 2);
    ASSERT_TRUE(string_eq_char_star(&a, "hellohilloo123"));
    ASSERT_TRUE(a.len == 14);
    string_replace_string(&a, &b, 5, 3);
    ASSERT_TRUE(string_eq_char_star(&a, "hellohelloloo123"));
    ASSERT_TRUE(a.len == 16);
    string_replace_char_star(&a, "hi", 0, 5);
    ASSERT_TRUE(string_eq_char_star(&a, "hihelloloo123"));
    ASSERT_TRUE(a.len == 13);

    free(a.inner);
    free(b.inner);
    free(c.inner);
}
