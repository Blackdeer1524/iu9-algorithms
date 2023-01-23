#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

typedef int32_t bitset_t;

#define add(set, character) (set |= 1 << (character - 'a'))

#define unite(l_set, r_set) ((l_set) ^ (r_set))

typedef struct Node{
    bitset_t value;

    struct Node *parent;
    struct Node *l_child;
    struct Node *r_child;

    size_t l_bound;
    size_t r_bound;
} Node;


Node *build_segment_tree(char *src);

void free_segment_tree(Node *root);

bool is_hyperdrome(Node *root, size_t l, size_t r, bool *error);

bool update(Node *root, size_t i, char *new_postfix);


#endif
