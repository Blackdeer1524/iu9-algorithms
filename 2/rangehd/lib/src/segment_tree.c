#include <limits.h>
#include <string.h>
#include "segment_tree.h"
#include <assert.h>

void free_segment_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    free_segment_tree(root->l_child);
    free_segment_tree(root->r_child);
    free(root);
}


static Node *build_tree(char *src, size_t size, size_t l, size_t r) {
    if (src == NULL || !(l <= r && r < size)) {
        return NULL;
    } 
    Node *parent = malloc(sizeof(Node));
    parent->parent = NULL;
    parent->l_child = NULL;
    parent->r_child = NULL;
    parent->l_bound=l;
    parent->r_bound=r;

    if (l == r) {
        parent->value = 0;
        add(parent->value, src[l]);
        return parent;
    } 

    size_t mid = r - (r - l) / 2;
    if ((parent->l_child = build_tree(src, size, l, mid - 1)) == NULL) {
        free_segment_tree(parent);
        return NULL;
    }
    if ((parent->r_child = build_tree(src, size, mid, r)) == NULL) {
        free_segment_tree(parent);
        return NULL;
    }
    parent->value = unite(parent->l_child->value, parent->r_child->value);
    parent->l_child->parent = parent;
    parent->r_child->parent = parent;
    return parent;
}


Node *build_segment_tree(char *src) {
    if (src == NULL) {
        return NULL;
    }
    size_t length = strlen(src); 
    return build_tree(src, length, 0, length - 1);
}


static bitset_t get_hyperdrome_data(Node *root, size_t l, size_t r, bool *error) {
    if (root == NULL) {
        *error = true;
        return 0;
    }
    
    if (root->r_bound < l || root->l_bound > r) {
        *error = true;
        return 0;
    } else if (l <= root->l_bound && root->r_bound <= r) { 
        return root->value;
    } 

    bool left_is_computable =  root->l_child != NULL && l <= root->l_child->r_bound;
    bool right_is_computable = root->r_child != NULL && r >= root->r_child->l_bound;

    if (left_is_computable && right_is_computable) {
        bitset_t left_set = get_hyperdrome_data(root->l_child, l, r, error);
        if (*error) {
            return 0;
        }
        bitset_t right_set = get_hyperdrome_data(root->r_child, l, r, error);
        if (*error) {
            return 0;
        }
        return unite(left_set, right_set);
    } else if (left_is_computable) {
        bitset_t left_set = get_hyperdrome_data(root->l_child, l, r, error);
        if (*error) {
            return 0;
        }
        return left_set;
    } else if (right_is_computable) {
        bitset_t right_set = get_hyperdrome_data(root->r_child, l, r, error);
        if (*error) {
            return 0;
        }
        return right_set;
    }
    *error = true;
    return 0;
}


bool is_hyperdrome(Node *root, size_t l, size_t r, bool *error) {
    bitset_t res = get_hyperdrome_data(root, l, r, error);
    
    if (!(*error) && (!res || !(res & (res - 1)))) {
        return true;
    }
    
    return false;
}


#define max(x, y) ((x) > (y) ? (x) : (y)) 
#define min(x, y) ((x) < (y) ? (x) : (y)) 


static bool update_subtree(Node *root, char *substr, size_t l, size_t r) {
    if (root == NULL) {
        return true;
    }
    
    if (root->l_child == NULL && root->r_child == NULL) { 
        if (l == r && root->l_bound == root->r_bound && l == root->l_bound) {
            root->value = 0;
            add(root->value, substr[0]);
            return false;
        }
        return true;
    } 
    assert(root->l_child != NULL && root->r_child != NULL);

    bool lr_error = false;
    if (root->l_child->r_bound >= l) {
        lr_error = update_subtree(root->l_child, 
                                  substr,
                                  l,
                                  min(r, root->l_child->r_bound));
        if (lr_error) {
            return lr_error;
        }
    }
    if (root->r_child->l_bound <= r) {
        lr_error = update_subtree(root->r_child, 
                                  substr + ((root->r_child->l_bound > l) ? (root->r_child->l_bound - l) : 0), 
                                  max(l, root->r_child->l_bound), 
                                  r);
    }
    root->value = unite(root->l_child->value, root->r_child->value);
    return lr_error;
}


bool update(Node *root, size_t i, char *substring) {
    return update_subtree(root, substring, i, i + strlen(substring) - 1);
}
