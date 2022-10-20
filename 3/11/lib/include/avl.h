#ifndef IU_ALGOS_AVL_H
#define IU_ALGOS_AVL_H

struct node;

typedef struct node node;

typedef enum {
    NO_INSERT,
    LEFT_T,
    RIGHT_T
} subtree_t;

void print_tree(node *root, char *pref);

struct node *create_node(char *key, int height);

int get(struct node *root, char *identifier_name);

subtree_t insert(struct node *root, char *item);

#endif //IU_ALGOS_AVL_H
