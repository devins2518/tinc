#ifndef VECTOR_H
#define VECTOR_H

unsigned long int power2(unsigned int a);
#define DECLARE_VECTOR(name)                                                                       \
    typedef struct vector_##name {                                                                 \
        unsigned int len;                                                                          \
        unsigned int cap;                                                                          \
        name *inner;                                                                               \
    } vector_##name;                                                                               \
    vector_##name vector_##name##_new(void);                                                       \
    vector_##name vector_##name##_new_reserve(unsigned int len);                                   \
    void vector_##name##_reserve(vector_##name *v, unsigned int len);                              \
    bool vector_##name##_add(vector_##name *v, name n);                                            \
    name *vector_##name##_get_inner(vector_##name *v);                                             \
    void vector_##name##_free(vector_##name v);

#define TYPEDEF_VECTOR(from, to)                                                                   \
    typedef struct vector_##from to;                                                               \
    to to##_new(void);                                                                             \
    to to##_new_reserve(unsigned int len);                                                         \
    void to##_reserve(to *v, unsigned int len);                                                    \
    bool to##_add(to *v, from f);                                                                  \
    from *to##_get_inner(to *v);                                                                   \
    void to##_free(to v);

#define IMPL_TYPEDEF_VECTOR(from, to)                                                              \
    to to##_new(void) {                                                                            \
        return vector_##from##_new();                                                              \
    }                                                                                              \
    to to##_new_reserve(unsigned int len) {                                                        \
        return vector_##from##_new_reserve(len);                                                   \
    }                                                                                              \
    void to##_reserve(to *v, unsigned int len) {                                                   \
        vector_##from##_reserve(v, len);                                                           \
    }                                                                                              \
    bool to##_add(to *v, from f) {                                                                 \
        return vector_##from##_add(v, f);                                                          \
    }                                                                                              \
    from *to##_get_inner(to *v) {                                                                  \
        return vector_##from##_get_inner(v);                                                       \
    }                                                                                              \
    void to##_free(to v) {                                                                         \
        vector_##from##_free(v);                                                                   \
    }

#define IMPL_VECTOR(name)                                                                          \
    vector_##name vector_##name##_new(void) {                                                      \
        vector_##name v;                                                                           \
        v.len = 0;                                                                                 \
        v.cap = 16;                                                                                \
        v.inner = (name *)calloc(v.cap, sizeof(name));                                             \
        if (v.inner == NULL) {                                                                     \
            printf("Allocation failed, cap * sizeof: %lu", v.cap * sizeof(name));                  \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
        return v;                                                                                  \
    }                                                                                              \
    /* Assumes caller will fill vector to `len`. */                                                \
    vector_##name vector_##name##_new_reserve(unsigned int len) {                                  \
        vector_##name v;                                                                           \
        v.len = 0;                                                                                 \
        v.cap = power2(len);                                                                       \
        v.inner = (name *)calloc(v.cap, sizeof(name));                                             \
        if (v.inner == NULL) {                                                                     \
            printf("Allocation failed, cap * sizeof: %lu", v.cap * sizeof(name));                  \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
        return v;                                                                                  \
    }                                                                                              \
    void vector_##name##_reserve(vector_##name *v, unsigned int len) {                             \
        if (v->cap < len) {                                                                        \
            v->cap = power2(len);                                                                  \
            v->inner = (name *)realloc(v->inner, (v->cap) * sizeof(name));                         \
            if (v->inner == NULL) {                                                                \
                printf("Allocation failed");                                                       \
                exit(EXIT_FAILURE);                                                                \
            }                                                                                      \
        }                                                                                          \
    }                                                                                              \
    /* Returns false if failure */                                                                 \
    bool vector_##name##_add(vector_##name *v, name n) {                                           \
        if (v->len >= v->cap) {                                                                    \
            v->cap <<= 1;                                                                          \
            v->inner = (name *)realloc(v->inner, (v->cap) * sizeof(name));                         \
            if (v->inner == NULL)                                                                  \
                return false;                                                                      \
        }                                                                                          \
        v->inner[v->len++] = n;                                                                    \
        return true;                                                                               \
    }                                                                                              \
    name *vector_##name##_get_inner(vector_##name *v) {                                            \
        return v->inner;                                                                           \
    }                                                                                              \
    void vector_##name##_free(vector_##name v) {                                                   \
        free(v.inner);                                                                             \
    }

#endif
