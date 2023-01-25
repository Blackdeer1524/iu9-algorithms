#include "gcd_matrix.h"


size_t gcd(size_t left, size_t right) {
    while (left && right) {
        if (left > right) {
            left %= right;
        } else {
            right %= left;
        }
    }
    return left + right;
} 


size_t int_log2(size_t x) {
    size_t res = 0;
    while (x >>= 1) {
        ++res;
    }
    return res;
}


#define abs(x) (((x) > 0) ? (x) : -(x))


Table get_gcd_table(table_item_t *array, size_t length, bool *error) {
    Table gcd_tree;
    if (!length) {
        *error = true;
        return gcd_tree;
    }

    int depth = (int) int_log2(length - 1) + 1;
    gcd_tree = table_build(depth, length);
    for (size_t i = 0; i < length; ++i) {
        set_item(&gcd_tree, 0, i, abs(array[i]));
    }

    size_t row_width = length;
    for (int current_depth = 0; current_depth < depth - 1; ++current_depth, row_width = (row_width + 1) >> 1) {
        bool row_width_is_odd = row_width & 1;
        for (size_t i = 0; i < row_width - row_width_is_odd; i += 2) {
            table_item_t l_child = get_item(&gcd_tree, current_depth, i);
            table_item_t r_child = get_item(&gcd_tree, current_depth, i + 1);
            set_item(&gcd_tree, current_depth + 1, i >> 1, gcd(l_child, r_child));
        }
        if (row_width_is_odd) {
            set_item(&gcd_tree, current_depth + 1, (row_width - 1) >> 1, get_item(&gcd_tree, current_depth, row_width - 1));
        }
    }

    *error = false;
    return gcd_tree;
}


// size_t get_gcd(Table *table, size_t l, size_t r, size_t tree_height) {
    
// }


// size_t query(Table *table, size_t l, size_t r, bool *error) {
    // if (l > r) {
    //     *error = true;
    //     return 0;
    // }
    // size_t interval_size = r - l + 1;
    // size_t q = int_log2(interval_size);
    // size_t result_depth = table->n_rows - q - 1;
    // size_t result_depth_bucket_size = 1 << q;
//     return 0;
// }