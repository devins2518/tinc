#include "../src/hash.h"
#include "../src/utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

bool cmp(int *a, int *b) { return *a == *b; }
DECLARE_GENERIC_HASH(int)
IMPL_GENERIC_HASH(int)
DECLARE_HASHMAP(int, int)
IMPL_HASHMAP(int, int, int_hash, cmp)

int main() {
    int zero = 0;
    int one = 1;
    int i;
    hash_map_int_int hm = hash_map_int_int_new();

    hash_map_int_int_insert(&hm, zero, one);
    assert(hash_map_int_int_lookup(&hm, &zero)->val == 1);
    assert(hash_map_int_int_lookup(&hm, &one) == NULL);
    hash_map_int_int_delete(&hm, &zero);
    assert(hash_map_int_int_lookup(&hm, &zero) == NULL);

    hash_map_int_int_free(hm);
    hm = hash_map_int_int_new();
    for (i = 0; i < 20; i++)
        hash_map_int_int_insert(&hm, i, i);

    for (i = 0; i < 20; i++) {
        entry_int_int *e;
        e = hash_map_int_int_lookup(&hm, &i);
        /* fprintf(stderr, "i: %d, key: %d, val: %d\n", i, e->key, e->val); */
        assert(e->key == i);
        assert(e->val == i);
    }

    hash_map_int_int_free(hm);
    return 0;
}
