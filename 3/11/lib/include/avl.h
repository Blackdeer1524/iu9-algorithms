#ifndef IU_ALGOS_AVL_H
#define IU_ALGOS_AVL_H

struct node;

typedef struct node node;

typedef enum {
    LEFT_T,
    RIGHT_T
} subtree_t;

void print_tree(node *root, char *pref);

struct node *create_node(int key, int height);

subtree_t insert(struct node *root, int item);


#endif //IU_ALGOS_AVL_H
