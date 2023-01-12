#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "heap.h"

void max_heapify(void *base,
                 size_t length,
                 size_t width,
                 size_t cur_index,
                 int (*compare)(const void *a, const void *b)) {
    size_t left_child_index = left(cur_index);
    size_t right_child_index = right(cur_index);

    void *parent = get_item_ptr(base, width, cur_index);
    void *least_value_item = parent;
    size_t least_value_item_index = cur_index;
    void *child_placeholder = NULL;
    if (left_child_index < length && compare(least_value_item, 
                                             (child_placeholder = get_item_ptr(base, width, left_child_index))) == -1) {
        least_value_item = child_placeholder;
        least_value_item_index = left_child_index;
    }

    if (right_child_index < length && compare(least_value_item, 
                                              (child_placeholder = get_item_ptr(base, width, right_child_index))) == -1) {
        least_value_item = child_placeholder;
        least_value_item_index = right_child_index;
    }

    if (cur_index != least_value_item_index) {
        void *placeholder = malloc(width);
        memcpy(placeholder, parent, width);
        memcpy(parent, least_value_item, width);
        memcpy(least_value_item, placeholder, width);
        free(placeholder);
        max_heapify(base, length, width, least_value_item_index, compare);
    }
}


void build_max_heap(void *base,
                    size_t nel,
                    size_t width,
                    int (*compare)(const void *a, const void *b)) {
    if (nel <= 1) {
        return;
    }

    for (size_t i = parent(nel - 1); i > 0; --i) {
        max_heapify(base, nel, width, i, compare);
    }
    max_heapify(base, nel, width, 0, compare);
}


void hsort(void *base,
           size_t nel,
           size_t width,
           int (*compare)(const void *a, const void *b)) {
    if (nel <= 1) {
        return;
    }

    build_max_heap(base, nel, width, compare);

    void *placeholder = malloc(width);
    void *first_item_ptr = get_item_ptr(base, width, 0);
    for (size_t r = nel - 1; r > 0; --r) {
        void *right_bound_item_ptr = get_item_ptr(base, width, r);
        memcpy(placeholder, first_item_ptr, width);
        memcpy(first_item_ptr, right_bound_item_ptr, width);
        memcpy(right_bound_item_ptr, placeholder, width);

        max_heapify(base, r, width, 0, compare);
    }

    free(placeholder);
}
