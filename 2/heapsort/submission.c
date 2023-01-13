#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <ctype.h>

#define parent(i) (((i) - 1) >> 1)
#define left(i) (((i) << 1) + 1)
#define right(i) ((((i) + 1) << 1))
#define get_item_ptr(void_base_ptr, width, i) (((char *) (void_base_ptr)) + (i) * (width))


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
                                             (child_placeholder = get_item_ptr(base, width, left_child_index))) < 0) {
        least_value_item = child_placeholder;
        least_value_item_index = left_child_index;
    }

    if (right_child_index < length && compare(least_value_item, 
                                              (child_placeholder = get_item_ptr(base, width, right_child_index))) < 0) {
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



int char_count_cmp(const char **l, const char **r) {
    size_t l_len = 0;
    for (const char *l_string = *l; *l_string != '\0'; ++l_string) {
        if (*l_string == 'a') {
            ++l_len;
        }
    }

    size_t r_len = 0;
    for (const char *r_string = *r; *r_string != '\0'; ++r_string) {
        if (*r_string == 'a') {
            ++r_len;
        }
    }
    if (l_len > r_len) {
        return 1;
    } else if (l_len < r_len) {
        return -1;
    }
    return 0;
}


void free_table(char **arr, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        free(arr[i]);
    }
    free(arr);
} 


int main() {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return 1;
    }

    char **arr = malloc(sizeof(char *) * n);
    for (size_t i = 0; i < n; ++i) {
        arr[i] = malloc(1000 * sizeof(char));
        if (scanf("%s", arr[i]) != 1) {
            free_table(arr, i + 1);
            return 1;
        }
    }

    hsort(arr, n, sizeof arr[0], (int (*)(const void *, const void *)) char_count_cmp);

    for (size_t i = 0; i < n; ++i) {
        printf("%s\n", arr[i]);
    }

    free_table(arr, n);
    return 0;
}