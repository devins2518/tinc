#include <gtest/gtest.h>
extern "C" {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#include "../src/string.h"
#pragma clang diagnostic pop
}
#include <stdio.h>
#include <stdlib.h>

TEST(STRING, TESTING) {
    string a, b, c;

    a = string_new_raw("test");
    b = string_new_raw("hello");
    c = string_new_len("testhello", 9);
    EXPECT_TRUE(a.inner[a.len] == '\0');
    string_append_string(&a, &b);
    EXPECT_TRUE(a.inner[a.len] == '\0');
    EXPECT_TRUE(string_eq_char_star(&a, "testhello"));
    EXPECT_TRUE(string_eq(&a, &c));
    EXPECT_TRUE(a.len == 9);
    string_append_char_star(&a, "123");
    EXPECT_TRUE(a.inner[a.len] == '\0');
    EXPECT_TRUE(string_eq_char_star(&a, "testhello123"));
    EXPECT_TRUE(a.len == 12);
    string_rem_char(&a, a.len, 0);
    EXPECT_TRUE(string_eq_char_star(&a, "testhello123"));
    EXPECT_TRUE(a.len == 12);
    string_rem_char(&a, 0, 1);
    EXPECT_TRUE(string_eq_char_star(&a, "esthello123"));
    EXPECT_TRUE(a.len == 11);
    string_rem_char(&a, a.len - 1, 1);
    EXPECT_TRUE(string_eq_char_star(&a, "esthello12"));
    EXPECT_TRUE(a.len == 10);
    string_rem_char(&a, 4, 3);
    EXPECT_TRUE(string_eq_char_star(&a, "estho12"));
    EXPECT_TRUE(a.len == 7);
    string_add_char_star(&a, "3", a.len);
    EXPECT_TRUE(string_eq_char_star(&a, "estho123"));
    EXPECT_TRUE(a.len == 8);
    string_add_char_star(&a, "t", 0);
    EXPECT_TRUE(string_eq_char_star(&a, "testho123"));
    EXPECT_TRUE(a.len == 9);
    string_add_string(&a, &b, 0);
    EXPECT_TRUE(string_eq_char_star(&a, "hellotestho123"));
    EXPECT_TRUE(a.len == 14);
    string_replace_string(&a, &b, 5, b.len);
    EXPECT_TRUE(string_eq_char_star(&a, "hellohelloo123"));
    EXPECT_TRUE(a.len == 14);
    string_replace_char_star(&a, "hi", 5, 2);
    EXPECT_TRUE(string_eq_char_star(&a, "hellohilloo123"));
    EXPECT_TRUE(a.len == 14);
    string_replace_string(&a, &b, 5, 3);
    EXPECT_TRUE(string_eq_char_star(&a, "hellohelloloo123"));
    EXPECT_TRUE(a.len == 16);
    string_replace_char_star(&a, "hi", 0, 5);
    EXPECT_TRUE(string_eq_char_star(&a, "hihelloloo123"));
    EXPECT_TRUE(a.len == 13);

    free(a.inner);
    free(b.inner);
    free(c.inner);
}
