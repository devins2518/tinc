#include "../src/vector.h"
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>

DECLARE_VECTOR(int)
IMPL_VECTOR(int)

CTEST(VECTOR, TEST_VECTOR) {
    vector_int v = vector_int_new();

    for (int i = 0; i < 0xFFFF; i++) {
        vector_int_add(&v, i);
    }
    int *p = vector_int_get_inner(&v);
    for (int i = 0; i < 0xFFFF; i++) {
        ASSERT_TRUE(p[i] == i);
    }

    vector_int_free(v);

    v = vector_int_new_reserve(0xFFFF);

    for (int i = 0; i < 0xFFFF; i++) {
        vector_int_add(&v, i);
    }
    p = vector_int_get_inner(&v);
    for (int i = 0; i < 0xFFFF; i++) {
        ASSERT_TRUE(p[i] == i);
    }

    vector_int_free(v);
}
