#ifndef HASH_H
#define HASH_H

#define DECLARE_HASHMAP(k, v)                                                  \
    typedef struct {                                                           \
        k key;                                                                 \
        v val;                                                                 \
        int tomb;                                                              \
    } entry_##k##_##v;                                                         \
    typedef struct {                                                           \
        int cap;                                                               \
        int filled;                                                            \
        entry_##k##_##v *table;                                                \
    } hash_map_##k##_##v;                                                      \
    hash_map_##k##_##v hash_map_##k##_##v##_new();                             \
    void hash_map_##k##_##v##_free(hash_map_##k##_##v h);                      \
    void hash_map_##k##_##v##_insert(hash_map_##k##_##v *h, k key, v val);     \
    void hash_map_##k##_##v##_delete(hash_map_##k##_##v *h, k key);            \
    entry_##k##_##v *hash_map_##k##_##v##_lookup(hash_map_##k##_##v *h, k key);

#define ALIVE 0
#define DEAD 1

#define IMPL_HASHMAP(k, v, hf, cmp)                                            \
    hash_map_##k##_##v hash_map_##k##_##v##_new() {                            \
        hash_map_##k##_##v h;                                                  \
        entry_##k##_##v e;                                                     \
        e.tomb = DEAD;                                                         \
        h.cap = 16;                                                            \
        h.filled = 0;                                                          \
        h.table = malloc(h.cap * sizeof(entry_##k##_##v));                     \
        if (h.table == NULL) {                                                 \
            printf("Failed to allocate hashmap.");                             \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        /* Set table to tombstones */                                          \
        return h;                                                              \
    }                                                                          \
    void hash_map_##k##_##v##_free(hash_map_##k##_##v h) { free(h.table); }    \
    void hash_map_##k##_##v##_insert(hash_map_##k##_##v *h, k key, v val) {    \
        entry_##k##_##v *e;                                                    \
        /* Resize table to account for addition. */                            \
        if (++h->filled >= h->cap) {                                           \
            h->cap <<= 1;                                                      \
            h->table = realloc(h->table, sizeof(v) * h->cap);                  \
            if (h->table == NULL) {                                            \
                printf("Failed to allocate hashmap.");                         \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
        }                                                                      \
        e = hash_map_##k##_##v##_lookup(h, key);                               \
        e->key = key;                                                          \
        e->val = val;                                                          \
        e->tomb = ALIVE;                                                       \
    }                                                                          \
    void hash_map_##k##_##v##_delete(hash_map_##k##_##v *h, k key) {           \
        entry_##k##_##v *e = hash_map_##k##_##v##_lookup(h, key);              \
        e->tomb = DEAD;                                                        \
    }                                                                          \
    entry_##k##_##v *hash_map_##k##_##v##_lookup(hash_map_##k##_##v *h,        \
                                                 k key) {                      \
        int index;                                                             \
        index = hf(&key) % h->cap;                                             \
        while ((h->table[index].tomb != ALIVE) ||                              \
               (!cmp(&key, &h->table[index].key))) {                           \
            index++;                                                           \
        }                                                                      \
                                                                               \
        return &h->table[index];                                               \
    }

#endif
