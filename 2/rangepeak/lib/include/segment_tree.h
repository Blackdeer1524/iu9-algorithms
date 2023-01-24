#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    bool is_peak;
} BorderInfo;


typedef struct Node{    
    size_t peak_count;
    size_t l_bound;
    size_t r_bound;

    BorderInfo leftmost_info;
    BorderInfo rightmost_info;

    struct Node *parent;
    struct Node *l_child;
    struct Node *r_child;
} Node;


Node *build_segment_tree(int *array, size_t size);

void free_segment_tree(Node *root);

size_t get_peak_count(Node *root, size_t l, size_t r, bool *error);

bool update(Node *root, size_t i, int new_value);


#endif
