#include "../src/string.h"
#include "../src/utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

string int_print(int *x) {
    string s;
    char c[512] = {0};
    sprintf(c, "%d", *x);
    s = string_new_raw(c);
    return s;
}
DECLARE_VECTOR(int)
IMPL_VECTOR(int)

int main() {
    int i;
    int *p;
    vector_int v = vector_int_new();

    for (i = 0; i < 0xFFFF; i++) {
        vector_int_add(&v, i);
    }
    p = vector_int_get_inner(&v);
    for (i = 0; i < 0xFFFF; i++) {
        assert(p[i] == i);
    }

    vector_int_free(v);

    v = vector_int_new_reserve(0xFFFF);

    for (i = 0; i < 0xFFFF; i++) {
        vector_int_add(&v, i);
    }
    p = vector_int_get_inner(&v);
    for (i = 0; i < 0xFFFF; i++) {
        assert(p[i] == i);
    }

    vector_int_free(v);

    return 0;
}
