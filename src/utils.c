#include "utils.h"

string string_new(const char *str, int len) {
    string s;
    s.str = str;
    s.len = len;
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
