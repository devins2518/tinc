#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

#define IMPL_VECTOR(name)                                                      \
    vector_##name vector_##name##_new() {                                      \
        vector_##name v;                                                       \
        v.len = 0;                                                             \
        v.cap = 16;                                                            \
        v.inner = malloc(v.cap * sizeof(name));                                \
        if (v.inner == NULL) {                                                 \
            printf("Allocation failed, cap * sizeof: %lu",                     \
                   v.cap * sizeof(name));                                      \
            abort();                                                           \
        }                                                                      \
        return v;                                                              \
    }                                                                          \
    bool vector_##name##_add(vector_##name *v, name n) {                       \
        if (v->len > v->cap) {                                                 \
            v->cap <<= 2;                                                      \
            v->inner = realloc(v->inner, (v->cap) * sizeof(name));             \
            if (v->inner == NULL)                                              \
                return false;                                                  \
        }                                                                      \
        v->inner[v->len++] = n;                                                \
        return true;                                                           \
    }                                                                          \
    void vector_##name##_print(const vector_##name *v) {}                      \
    void vector_##name##_free(vector_##name v) { free(v.inner); }              \
    name *vector_##name##_get_inner(vector_##name *v) { return v->inner; }

IMPL_VECTOR(pp_token)
