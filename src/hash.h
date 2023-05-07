#ifndef HASH_H
#define HASH_H

#include <stdlib.h>

#define DECLARE_HASHMAP(k, v)                                                                      \
    typedef struct {                                                                               \
        k key;                                                                                     \
        v val;                                                                                     \
        int tomb;                                                                                  \
    } entry_##k##_##v;                                                                             \
    typedef struct {                                                                               \
        uint64_t cap;                                                                              \
        uint64_t filled;                                                                           \
        entry_##k##_##v *table;                                                                    \
    } hash_map_##k##_##v;                                                                          \
    hash_map_##k##_##v hash_map_##k##_##v##_new(void);                                             \
    void hash_map_##k##_##v##_free(hash_map_##k##_##v h);                                          \
    void hash_map_##k##_##v##_insert(hash_map_##k##_##v *h, k key, v val);                         \
    void hash_map_##k##_##v##_delete(hash_map_##k##_##v *h, k *key);                               \
    entry_##k##_##v *hash_map_##k##_##v##_lookup(hash_map_##k##_##v *h, const k *key);

#define DECLARE_GENERIC_HASH(t) unsigned long t##_hash(t *val);

#define ALIVE 1
#define DEAD 0

#define IMPL_HASHMAP(k, v, hf, cmp)                                                                \
    hash_map_##k##_##v hash_map_##k##_##v##_new(void) {                                            \
        hash_map_##k##_##v h;                                                                      \
        h.cap = 16;                                                                                \
        h.filled = 0;                                                                              \
        h.table = (entry_##k##_##v *)calloc(h.cap, sizeof(*h.table));                              \
        if (h.table == NULL) {                                                                     \
            printf("Failed to allocate hashmap.");                                                 \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
        return h;                                                                                  \
    }                                                                                              \
    void hash_map_##k##_##v##_free(hash_map_##k##_##v h) {                                         \
        free(h.table);                                                                             \
    }                                                                                              \
    void hash_map_##k##_##v##_insert(hash_map_##k##_##v *h, k key, v val) {                        \
        entry_##k##_##v *e;                                                                        \
        uint64_t i;                                                                                \
        /* Resize table to account for addition. */                                                \
        if (++h->filled > h->cap) {                                                                \
            e = (entry_##k##_##v *)calloc(h->cap << 1, sizeof(*e));                                \
            if (e == NULL) {                                                                       \
                printf("Failed to allocate hashmap.");                                             \
                exit(EXIT_FAILURE);                                                                \
            }                                                                                      \
            for (i = 0; i < h->cap; i++) {                                                         \
                int index = hf(&h->table[i].key) % (h->cap << 1);                                  \
                while (e[index].tomb == ALIVE) {                                                   \
                    index = (index + 1) % (h->cap << 1);                                           \
                }                                                                                  \
                e[index] = h->table[i];                                                            \
            }                                                                                      \
            free(h->table);                                                                        \
            h->table = e;                                                                          \
            h->cap <<= 1;                                                                          \
        }                                                                                          \
        i = hf(&key) % h->cap;                                                                     \
        while (h->table[i].tomb == ALIVE && !cmp(&key, &h->table[i].key)) {                        \
            i = (i + 1) % h->cap;                                                                  \
        }                                                                                          \
        e = &h->table[i];                                                                          \
        e->key = key;                                                                              \
        e->val = val;                                                                              \
        e->tomb = ALIVE;                                                                           \
    }                                                                                              \
    void hash_map_##k##_##v##_delete(hash_map_##k##_##v *h, k *key) {                              \
        entry_##k##_##v *e = hash_map_##k##_##v##_lookup(h, key);                                  \
        if (e != NULL)                                                                             \
            e->tomb = DEAD;                                                                        \
        h->filled--;                                                                               \
    }                                                                                              \
    entry_##k##_##v *hash_map_##k##_##v##_lookup(hash_map_##k##_##v *h, const k *key) {            \
        int init_index = hf(key) % h->cap;                                                         \
        int index = init_index;                                                                    \
        entry_##k##_##v *e = NULL;                                                                 \
        while (h->table[index].tomb == ALIVE) {                                                    \
            if (cmp(key, &h->table[index].key)) {                                                  \
                e = &h->table[index];                                                              \
                break;                                                                             \
            } else {                                                                               \
                index = (index + 1) % h->cap;                                                      \
                if (index == init_index) {                                                         \
                    break;                                                                         \
                }                                                                                  \
            }                                                                                      \
        }                                                                                          \
                                                                                                   \
        return e;                                                                                  \
    }

#define IMPL_GENERIC_HASH(t)                                                                       \
    unsigned long t##_hash(t *val) {                                                               \
        unsigned long hash = 5381;                                                                 \
        int size = sizeof(t);                                                                      \
        char *str = (char *)val;                                                                   \
        int i = 0;                                                                                 \
                                                                                                   \
        while (i++ < size)                                                                         \
            hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + i */                              \
                                                                                                   \
        return hash;                                                                               \
    }

#endif
