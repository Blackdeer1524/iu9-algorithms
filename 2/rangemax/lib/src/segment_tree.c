#include <limits.h>
#include "segment_tree.h"


void free_segment_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    free_segment_tree(root->l_child);
    free_segment_tree(root->r_child);
    free(root);
}

#define max(x, y) ((x) > (y) ? (x) : (y))


static Node *build_tree(int *array, size_t size, size_t l, size_t r) {
    if (array == NULL || !(l <= r || r < size)) {
        return NULL;
    } 
    Node *parent = malloc(sizeof(Node));
    parent->parent = NULL;
    parent->l_child = NULL;
    parent->r_child = NULL;
    parent->l_bound=l;
    parent->r_bound=r;

    if (l == r) {
        parent->value=array[l];
        return parent;
    } 

    size_t mid = r - (r - l) / 2;
    if ((parent->l_child = build_tree(array, size, l, mid - 1)) == NULL) {
        free_segment_tree(parent);
        return NULL;
    }
    if ((parent->r_child = build_tree(array, size, mid, r)) == NULL) {
        free_segment_tree(parent);
        return NULL;
    }
    parent->value = max(parent->l_child->value, parent->r_child->value);
    parent->l_child->parent = parent;
    parent->r_child->parent = parent;
    return parent;
}


Node *build_segment_tree(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return NULL;
    }
    return build_tree(array, size, 0, size - 1);
}


int get_max(Node *root, size_t l, size_t r, bool *error) {
    if (root == NULL) {
        *error = true;
        return INT_MIN;
    }
    
    if (root->r_bound < l || root->l_bound > r) {
        return INT_MIN;
    } else if (l <= root->l_bound && root->r_bound <= r) { 
        return root->value;
    } 

    int left_max = get_max(root->l_child, l, r, error);
    if (*error) {
        return INT_MIN;
    }
    int right_max = get_max(root->r_child, l, r, error);
    if (*error) {
        return INT_MIN;
    }

    return max(left_max, right_max);
}


bool update(Node *root, size_t i, int new_value) {
    if (root == NULL) { 
        return true;
    }
    if (root->l_bound == i && root->l_bound == root->r_bound) {
        root->value = new_value;
        return false; 
    }

    if (root->l_child != NULL) {
        if (root->l_child->r_bound >= i) {
            bool error = update(root->l_child, i, new_value); 
            if (root->r_child != NULL) {
                root->value = max(root->l_child->value, root->r_child->value);
            } else {
                root->value = root->l_child->value;
            }
            return error;
        }
    }

    if (root->r_child != NULL) {
        if (root->r_child->l_bound <= i) {
            bool error = update(root->r_child, i, new_value);
            if (root->l_child != NULL) {
                root->value = max(root->l_child->value, root->r_child->value);
            } else {
                root->value = root->r_child->value;
            }
            return error;
        }
    }
    return true;
}
