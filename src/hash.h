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
    void hash_map_##k##_##v##_delete(hash_map_##k##_##v *h, k *key);           \
    entry_##k##_##v *hash_map_##k##_##v##_lookup(hash_map_##k##_##v *h, k *key);

#define DECLARE_GENERIC_HASH(t) unsigned int t##_hash(t *val);

#define ALIVE 0
#define DEAD 1

#define IMPL_HASHMAP(k, v, hf, cmp)                                            \
    hash_map_##k##_##v hash_map_##k##_##v##_new() {                            \
        int i;                                                                 \
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
        for (i = 0; i < h.cap; h.table[i++] = e)                               \
            ;                                                                  \
        return h;                                                              \
    }                                                                          \
    void hash_map_##k##_##v##_free(hash_map_##k##_##v h) { free(h.table); }    \
    void hash_map_##k##_##v##_insert(hash_map_##k##_##v *h, k key, v val) {    \
        int i;                                                                 \
        entry_##k##_##v *e;                                                    \
        /* Resize table to account for addition. */                            \
        if (++h->filled >= h->cap) {                                           \
            h->table = realloc(h->table, sizeof(v) * h->cap << 1);             \
            if (h->table == NULL) {                                            \
                printf("Failed to allocate hashmap.");                         \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
            for (i = h->cap; i < h->cap << 1; h->table[i++].tomb = DEAD)       \
                ;                                                              \
            h->cap <<= 1;                                                      \
        }                                                                      \
        i = hf(&key) % h->cap;                                                 \
        while ((h->table[i].tomb == ALIVE) ||                                  \
               (!cmp(&key, &h->table[i].key))) {                               \
            i++;                                                               \
        }                                                                      \
        e = &h->table[i];                                                      \
        e->key = key;                                                          \
        e->val = val;                                                          \
        e->tomb = ALIVE;                                                       \
    }                                                                          \
    void hash_map_##k##_##v##_delete(hash_map_##k##_##v *h, k *key) {          \
        entry_##k##_##v *e = hash_map_##k##_##v##_lookup(h, key);              \
        if (e != NULL)                                                         \
            e->tomb = DEAD;                                                    \
    }                                                                          \
    entry_##k##_##v *hash_map_##k##_##v##_lookup(hash_map_##k##_##v *h,        \
                                                 k *key) {                     \
        int init_index = hf(key) % h->cap;                                     \
        int index = init_index;                                                \
        entry_##k##_##v *e = NULL;                                             \
        while (h->table[index].tomb == ALIVE) {                                \
            if (cmp(key, &h->table[index].key)) {                              \
                e = &h->table[index];                                          \
                break;                                                         \
            } else {                                                           \
                index++;                                                       \
                if (index == init_index) {                                     \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        return e;                                                              \
    }

#define IMPL_GENERIC_HASH(t)                                                   \
    unsigned int t##_hash(t *val) {                                            \
        unsigned long hash = 5381;                                             \
        int size = sizeof(t);                                                  \
        char *str = (char *)val;                                               \
        int i = 0;                                                             \
                                                                               \
        while (i++ < size)                                                     \
            hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + i */          \
                                                                               \
        return hash;                                                           \
    }

#endif
