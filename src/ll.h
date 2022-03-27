#ifndef LL_H
#define LL_H

#define DECLARE_LINKED_LIST(t)                                                 \
    typedef struct ll_##t {                                                    \
        struct ll_##t *next;                                                   \
        struct ll_##t *prev;                                                   \
        t data;                                                                \
    } ll_##t;                                                                  \
    ll_##t *ll_##t##_new();                                                    \
    void ll_##t##_append(ll_##t *ll, t d);

#define IMPL_LINKED_LIST(t)                                                    \
    ll_##t *ll_##t##_new(t data) {                                             \
        ll_##t *ll = malloc(sizeof(ll_##t));                                   \
        if (ll == NULL) {                                                      \
            printf("Allocation failed.");                                      \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        ll.next = NULL;                                                        \
        ll.prev = NULL;                                                        \
        ll.data = data;                                                        \
        return ll;                                                             \
    }                                                                          \
    void ll_##t##_append(ll_##t *ll, t d) {                                    \
        ll_##t ll = ll;                                                        \
        while (ll->next != NULL) {                                             \
            ll = ll->next;                                                     \
        }                                                                      \
        ll->next = ll_##t##_new(d);                                            \
    }

#endif
