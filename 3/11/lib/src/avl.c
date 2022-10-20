#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "avl.h"

static int new_identifier_index = 0;

typedef struct node {
    char *identifier_name;
    int identifier_value;
    int height;
    node *left;
    node *right;
} node;


void print_tree(node *root, char *pref) {
    printf("<%s> (k:%s, i:%d, h:%d) ", pref, root->identifier_name, root->identifier_value, root->height);
    size_t pref_length = strlen(pref);
    if (root->left != NULL) {
        char *l_pref = malloc(sizeof (char) * (pref_length + 2));
        strncpy(l_pref, pref, pref_length);
        l_pref[pref_length] = 'L';
        l_pref[pref_length + 1] = '\0';
        print_tree(root->left, l_pref);
        free(l_pref);
    }
    if (root->right != NULL) {
        char *r_pref = malloc(sizeof (char) * (pref_length + 2));
        strncpy(r_pref, pref, pref_length);
        r_pref[pref_length] = 'R';
        r_pref[pref_length + 1] = '\0';
        print_tree(root->right, r_pref);
        free(r_pref);
    }
}


static int height(node* p) {
    return (p == NULL) ? -1 : p->height;
}


static int bfactor(node* p) {
    return height(p->right) - height(p->left);
}


static void fixheight(node* p) {
    int hl = height(p->left);
    int hr = height(p->right);
    if (hl == -1 && hr == -1) {
        p->height = 0;
    } else {
        p->height = (hl > hr ? hl : hr) + 1;
    }
}


struct node *create_node(char *identifier_name, int height) {
    struct node *leaf = malloc(sizeof (struct node));
    leaf->identifier_name = malloc(sizeof(char) * (strlen(identifier_name) + 1));
    strcpy(leaf->identifier_name, identifier_name);
    leaf->identifier_value = new_identifier_index++;
    leaf->left = NULL;
    leaf->right = NULL;
    leaf->height = height;
    return leaf;
}


int get(struct node *root, char *identifier_name) {
    if (root == NULL) {
        return -1;
    }

    int cmp = strcmp(root->identifier_name, identifier_name);
    if (cmp == 0) {
        return root->identifier_value;
    } else if (cmp < 0) {
        return get(root->right, identifier_name);
    } else {
        return get(root->left, identifier_name);
    }
}


subtree_t insert(struct node *root, char *identifier_name) {
    int cmp = strcmp(root->identifier_name, identifier_name);
    if (cmp == 0) {
        return NO_INSERT;
    } else if (cmp > 0) {
        // L
        if (root->left == NULL) {
            root->left = create_node(identifier_name, 0);
            fixheight(root);
            return LEFT_T;
        }
        subtree_t insertion_direction = insert(root->left, identifier_name);
        fixheight(root);
        int balancing_factor = bfactor(root);
        if (-2 < balancing_factor && balancing_factor < 2) {
            return LEFT_T;
        }

        switch (insertion_direction) {
            case LEFT_T: {  // LL
                // swaps root and middle
                node placeholder = *root;  // full copy
                node *l_subtree = root->left;
                node *lr_subtree = l_subtree->right;
                *root = *l_subtree;
                *l_subtree = placeholder;

                // root and r_subtree are swapped
                // root contains r_subtree data now
                // r_subtree contains root data now
                root->right = l_subtree;
                root->right->left = lr_subtree;

                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            case RIGHT_T: {  // LR
                node *l_node = root->left;
                node *lr_node = l_node->right;

                node *lrl_subtree;
                node *lrr_subtree;
                lrl_subtree = lr_node->left;
                lrr_subtree = lr_node->right;

                node placeholder = *root;
                *root = *lr_node;
                *lr_node = placeholder;

                root->right = lr_node;
                root->right->left = lrr_subtree;
                root->left = l_node;
                root->left->right = lrl_subtree;
                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            default:
                exit(1);
                break;
        }
        return LEFT_T;
    } else if (cmp < 0) {
        // R
        if (root->right == NULL) {
            root->right = create_node(identifier_name, 0);
            fixheight(root);
            return RIGHT_T;
        }
        subtree_t insertion_direction = insert(root->right, identifier_name);
        fixheight(root);
        int balancing_factor = bfactor(root);
        if (-2 < balancing_factor && balancing_factor < 2) {
            return RIGHT_T;
        }

        switch (insertion_direction) {
            case LEFT_T: {  // RL
                node *r_node = root->right;
                node *rl_node = r_node->left;

                node *rlr_subtree;
                node *rll_subtree;
                rlr_subtree = rl_node->right;
                rll_subtree = rl_node->left;

                node placeholder = *root;
                *root = *rl_node;
                *rl_node = placeholder;

                root->left = rl_node;
                root->left->right = rll_subtree;
                root->right = r_node;
                root->right->left = rlr_subtree;
                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            case RIGHT_T: {  // RR
                // swaps root and middle
                node placeholder = *root;  // full copy
                node *r_subtree = root->right;
                node *rl_subtree = r_subtree->left;
                *root = *r_subtree;
                *r_subtree = placeholder;

                // root and r_subtree are swapped
                // root contains r_subtree data now
                // r_subtree contains root data now
                root->left = r_subtree;
                root->left->right = rl_subtree;

                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            default:
                exit(1);
                break;
        }
        return RIGHT_T;
    }
}
