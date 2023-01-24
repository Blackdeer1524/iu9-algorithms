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
#define min(x, y) ((x) < (y) ? (x) : (y))

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
        parent->peak_count = 1;
        parent->leftmost_info.value = array[l];
        parent->leftmost_info.is_peak = true;
        parent->rightmost_info.value = array[l];
        parent->rightmost_info.is_peak = true;
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

    parent->l_child->parent = parent;
    parent->r_child->parent = parent;
    
    parent->leftmost_info = parent->l_child->leftmost_info;
    parent->rightmost_info = parent->r_child->rightmost_info;

    parent->peak_count = parent->l_child->peak_count + parent->r_child->peak_count; 

    bool left_peak_is_overwritten  = parent->l_child->rightmost_info.is_peak && parent->r_child->leftmost_info.value  > parent->l_child->rightmost_info.value;
    bool right_peak_is_overwritten = parent->r_child->leftmost_info.is_peak  && parent->l_child->rightmost_info.value > parent->r_child->leftmost_info.value;

    if (left_peak_is_overwritten || right_peak_is_overwritten) {
        --parent->peak_count;
        if (l == r - 1) {
            if (left_peak_is_overwritten) {
                parent->leftmost_info.is_peak = false;
            } else {
                parent->rightmost_info.is_peak = false;
            }
        } else if (l == r - 2 && left_peak_is_overwritten) {
            parent->leftmost_info.is_peak = false;
        } 
    }

    return parent;
}


Node *build_segment_tree(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return NULL;
    }
    return build_tree(array, size, 0, size - 1);
}


size_t get_peak_count(Node *root, size_t l, size_t r, bool *error) {
    if (root == NULL) {
        *error = true;
        return 0;
    }
    
    if (l <= root->l_bound && root->r_bound <= r) {         // <----------------------------------------
        return root->peak_count;                            //                                          |
    }                                                       //                                          |                                                 
                                                            //                                          | 
    if (root->l_child == NULL || root->r_child == NULL) {   // Если оба NULL, то должно было сработать это
        *error = true;
        return 0;
    }
    
    size_t total_peak_count = 0;
    if (l <= root->l_child->r_bound && root->r_child->l_bound <= r) {
        size_t left_peak_count = get_peak_count(root->l_child, l, root->l_child->r_bound, error);
        if (*error) {
            return 0;
        }
        size_t right_peak_count = get_peak_count(root->r_child, root->r_child->l_bound, r, error);
        if (*error) {
            return 0;
        }
        
        total_peak_count = left_peak_count + right_peak_count;
        bool left_peak_is_overwritten  = root->l_child->rightmost_info.is_peak && root->r_child->leftmost_info.value  > root->l_child->rightmost_info.value;
        bool right_peak_is_overwritten = root->r_child->leftmost_info.is_peak  && root->l_child->rightmost_info.value > root->r_child->leftmost_info.value;
        if (left_peak_is_overwritten || right_peak_is_overwritten) {
            --total_peak_count;
        }
    } else if (l <= root->l_child->r_bound) {
        total_peak_count = get_peak_count(root->l_child, l, min(r, root->l_child->r_bound), error);
    } else if (root->r_child->l_bound <= r) {
        total_peak_count = get_peak_count(root->r_child, max(l, root->r_child->l_bound), r, error);
    }
    
    return total_peak_count;
}


bool update(Node *root, size_t i, int new_value) {
    if (root == NULL) { 
        return true;
    }

    if (root->l_bound == i && root->l_bound == root->r_bound) {
        root->leftmost_info.value = new_value;
        root->rightmost_info.value = new_value;
        return false; 
    }

    if (root->l_child == NULL || root->r_child == NULL) {
        return true;
    }

    if (root->l_child->l_bound <= i && i <= root->l_child->r_bound) {
        if (update(root->l_child, i, new_value)) {
            return true;
        }
    } else if (root->r_child->l_bound <= i && i <= root->r_child->r_bound) {
        if (update(root->r_child, i, new_value)) {
            return true;
        }
    }
    
    root->leftmost_info = root->l_child->leftmost_info;
    root->rightmost_info = root->r_child->rightmost_info;

    root->peak_count = root->l_child->peak_count + root->r_child->peak_count; 

    bool left_peak_is_overwritten  = root->l_child->rightmost_info.is_peak && root->r_child->leftmost_info.value  > root->l_child->rightmost_info.value;
    bool right_peak_is_overwritten = root->r_child->leftmost_info.is_peak  && root->l_child->rightmost_info.value > root->r_child->leftmost_info.value;

    if (left_peak_is_overwritten || right_peak_is_overwritten) {
        --root->peak_count;
        if (root->l_bound == root->r_bound - 1) {
            if (left_peak_is_overwritten) {
                root->leftmost_info.is_peak = false;
            } else {
                root->rightmost_info.is_peak = false;
            }
        } else if (root->l_bound == root->r_bound - 2 && left_peak_is_overwritten) {
            root->leftmost_info.is_peak = false;
        } 
    }

    return false;
}
