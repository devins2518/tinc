#ifndef VECTOR_H
#define VECTOR_H

#define DECLARE_VECTOR(name)                                                   \
    typedef struct {                                                           \
        int len;                                                               \
        int cap;                                                               \
        name *inner;                                                           \
    } vector_##name;                                                           \
    vector_##name vector_##name##_new();                                       \
    vector_##name vector_##name##_new_reserve(int len);                        \
    void vector_##name##_reserve(vector_##name *v, int len);                   \
    bool vector_##name##_add(vector_##name *v, name n);                        \
    name *vector_##name##_get_inner(vector_##name *v);                         \
    void vector_##name##_print(const vector_##name *v);                        \
    void vector_##name##_free(vector_##name v);

#define IMPL_VECTOR(name)                                                      \
    vector_##name vector_##name##_new() {                                      \
        vector_##name v;                                                       \
        v.len = 0;                                                             \
        v.cap = 16;                                                            \
        v.inner = calloc(v.cap, sizeof(name));                                 \
        if (v.inner == NULL) {                                                 \
            printf("Allocation failed, cap * sizeof: %lu",                     \
                   v.cap * sizeof(name));                                      \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        return v;                                                              \
    }                                                                          \
    /* Assumes caller will fill vector to `len`. */                            \
    vector_##name vector_##name##_new_reserve(int len) {                       \
        vector_##name v;                                                       \
        unsigned int cap = len;                                                \
        v.len = len;                                                           \
        cap--;                                                                 \
        cap |= cap >> 1;                                                       \
        cap |= cap >> 2;                                                       \
        cap |= cap >> 4;                                                       \
        cap |= cap >> 8;                                                       \
        cap |= cap >> 16;                                                      \
        cap++;                                                                 \
        v.cap = cap;                                                           \
        v.inner = calloc(v.cap, sizeof(name));                                 \
        if (v.inner == NULL) {                                                 \
            printf("Allocation failed, cap * sizeof: %lu",                     \
                   v.cap * sizeof(name));                                      \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        return v;                                                              \
    }                                                                          \
    void vector_##name##_reserve(vector_##name *v, int len) {                  \
        if (v->cap < len) {                                                    \
            len--;                                                             \
            len |= len >> 1;                                                   \
            len |= len >> 2;                                                   \
            len |= len >> 4;                                                   \
            len |= len >> 8;                                                   \
            len |= len >> 16;                                                  \
            len++;                                                             \
            v->cap = len;                                                      \
            v->inner = realloc(v->inner, (v->cap) * sizeof(name));             \
            if (v->inner == NULL) {                                            \
                printf("Allocation failed");                                   \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    /* Returns false if failure */                                             \
    bool vector_##name##_add(vector_##name *v, name n) {                       \
        if (v->len >= v->cap) {                                                \
            v->cap <<= 1;                                                      \
            v->inner = realloc(v->inner, (v->cap) * sizeof(name));             \
            if (v->inner == NULL)                                              \
                return false;                                                  \
        }                                                                      \
        v->inner[v->len++] = n;                                                \
        return true;                                                           \
    }                                                                          \
    void vector_##name##_print(const vector_##name *v) {                       \
        int i;                                                                 \
        printf("[\n");                                                         \
        for (i = 0; i < v->len; i++) {                                         \
            string s = name##_print(&v->inner[i]);                             \
            printf("\t%.*s,\n", s.len, s.inner);                               \
        }                                                                      \
        printf("]\n");                                                         \
    }                                                                          \
    void vector_##name##_free(vector_##name v) { free(v.inner); }              \
    name *vector_##name##_get_inner(vector_##name *v) { return v->inner; }

#endif
