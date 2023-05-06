#ifndef LL_H
#define LL_H

#define DECLARE_LINKED_LIST(t)                                                                     \
    typedef struct ll_##t##_node {                                                                 \
        struct ll_##t##_node *next;                                                                \
        struct ll_##t##_node *prev;                                                                \
        t data;                                                                                    \
    } ll_##t##_node;                                                                               \
    typedef struct {                                                                               \
        ll_##t##_node *start;                                                                      \
        ll_##t##_node *end;                                                                        \
    } ll_##t;                                                                                      \
    ll_##t *ll_##t##_new(void);                                                                    \
    void ll_##t##_add_end(ll_##t *ll, t d);                                                        \
    void ll_##t##_add_start(ll_##t *ll, t d);

#define IMPL_LINKED_LIST(t)                                                                        \
    ll_##t##_node *ll_##t##_node_new(t data) {                                                     \
        ll_##t##_node *node = malloc(sizeof(ll_##t##_node));                                       \
        if (node == NULL) {                                                                        \
            printf("Allocation failed");                                                           \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
        node->data = data;                                                                         \
        node->next = NULL;                                                                         \
        node->prev = NULL;                                                                         \
        return node;                                                                               \
    }                                                                                              \
    ll_##t *ll_##t##_new(void) {                                                                   \
        ll_##t *ll = malloc(sizeof(ll_##t));                                                       \
        if (ll == NULL) {                                                                          \
            printf("Allocation failed");                                                           \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
        return ll;                                                                                 \
    }                                                                                              \
    void ll_##t##_add_end(ll_##t *ll, t d) {                                                       \
        ll_##t##_node *last = ll_##t##_node_new(d);                                                \
        ll->end->prev = last;                                                                      \
        ll->end = last;                                                                            \
    }                                                                                              \
    void ll_##t##_add_start(ll_##t *ll, t d) {                                                     \
        ll_##t##_node *start = ll_##t##_node_new(d);                                               \
        ll->start->next = start;                                                                   \
        ll->start = start;                                                                         \
    }

#endif
