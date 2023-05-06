#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "../src/hash.h"
}

bool cmp(const int *a, const int *b) {
    return *a == *b;
}
unsigned int int_hash(const int *x) {
    unsigned hash = *x;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;
    return hash;
}
DECLARE_HASHMAP(int, int)
IMPL_HASHMAP(int, int, int_hash, cmp)

TEST(HASH, ASSERT_CONTENTS_AND_VALUES) {
    int zero = 0;
    int one = 1;
    hash_map_int_int hm = hash_map_int_int_new();

    hash_map_int_int_insert(&hm, zero, one);
    EXPECT_TRUE(hash_map_int_int_lookup(&hm, &zero)->val == 1);
    EXPECT_TRUE(hash_map_int_int_lookup(&hm, &one) == NULL);
    hash_map_int_int_delete(&hm, &zero);
    EXPECT_TRUE(hash_map_int_int_lookup(&hm, &zero) == NULL);

    hash_map_int_int_free(hm);
    hm = hash_map_int_int_new();
    for (int i = 0; i < 0xFFFF; i++) {
        hash_map_int_int_insert(&hm, i, i);
    }

    for (int i = 0; i < 0xFFFF; i++) {
        entry_int_int *e;
        e = hash_map_int_int_lookup(&hm, &i);
        EXPECT_TRUE(e->key == i);
        EXPECT_TRUE(e->val == i);
    }

    hash_map_int_int_free(hm);
}
