#ifndef VECTOR_H
#define VECTOR_H

#include "token.h"

#define DEFINE_VECTOR(name)                                                    \
    typedef struct {                                                           \
        int len;                                                               \
        int cap;                                                               \
        name *inner;                                                           \
    } vector_##name;                                                           \
    vector_##name vector_##name##_new();                                       \
    bool vector_##name##_add(vector_##name *v, name n);                        \
    name *vector_##name##_get_inner(vector_##name *v);                         \
    void vector_##name##_free(vector_##name v);

DEFINE_VECTOR(pp_token)

#endif
