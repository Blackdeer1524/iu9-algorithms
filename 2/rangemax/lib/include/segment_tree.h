#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int value;

    struct Node *parent;
    struct Node *l_child;
    struct Node *r_child;

    size_t l_bound;
    size_t r_bound;
} Node;


Node *build_segment_tree(int *array, size_t size);

void free_segment_tree(Node *root);

int get_max(Node *root, size_t l, size_t r, bool *error);

bool update(Node *root, size_t i, int new_value);


#endif
