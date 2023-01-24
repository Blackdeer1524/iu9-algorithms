#include "segment_tree.h"


#define abs(x) ((x) > 0 ? (x) : (-x))

int gcd(int left, int right) {
    if (left < 0 || right < 0) {
        return -1;
    } 

    while (left != 0 && right != 0) {
        if (left > right) {
            left %= right;
        } else {
            right %= left;
        }
    }
    return left + right;
}


void free_segment_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    free_segment_tree(root->l_child);
    free_segment_tree(root->r_child);
    free(root);
}


static Node *build_tree(int *array, size_t size, size_t l, size_t r) {
    if (array == NULL || !(l <= r && r < size)) {
        return NULL;
    } 
    Node *parent = malloc(sizeof(Node));
    parent->parent = NULL;
    parent->l_child = NULL;
    parent->r_child = NULL;
    parent->l_bound=l;
    parent->r_bound=r;

    if (l == r) {
        parent->value=abs(array[l]);
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
    parent->value = gcd(parent->l_child->value, parent->r_child->value);
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


int interval_gcd(Node *root, size_t l, size_t r) {
    if (root == NULL || l > r) {
        return -1;
    }

    if (l == root->l_bound && root->r_bound == r) {
        return root->value;
    }

    if (root->l_child == NULL || root->r_child == NULL) {        
        return -1;
    }

    if (l <= root->l_child->r_bound && root->r_child->l_bound <= r) {
        int left_gcd, right_gcd;
        if ((left_gcd = interval_gcd(root->l_child, l, root->l_child->r_bound)) == -1) {
            return -1;
        }
        if ((right_gcd = interval_gcd(root->r_child, root->r_child->l_bound, r)) == -1) {
            return -1;
        } 
        return gcd(left_gcd, right_gcd);
    } else if (l <= root->l_child->r_bound) {
        return interval_gcd(root->l_child, l, r);
    } else if (root->r_child->l_bound <= r) {
        return interval_gcd(root->r_child, l, r);
    }
    return -1;
}


bool update(Node *root, size_t i, int new_value) {
    if (root == NULL) { 
        return true;
    }
    if (root->l_bound == i && root->l_bound == root->r_bound) {
        root->value = abs(new_value);
        return false; 
    }

    if (root->l_child == NULL || root->r_child == NULL) {
        return true;
    }

    bool error = true;
    if (i <= root->l_child->r_bound) {
        error = update(root->l_child, i, new_value); 
    } else if (root->r_child->l_bound <= i) {
        error = update(root->r_child, i, new_value);
    }
    root->value = gcd(root->l_child->value, root->r_child->value);
    return error;
}
