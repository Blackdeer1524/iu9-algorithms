#include "gcd_matrix.h"
#include "math_utils.h"


LogTable *get_gcd_table(table_item_t *array, size_t length) {
    if (!length) {
        return NULL;
    }

    LogTable *gcd_tree = table_build(length);
    if (gcd_tree == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        set_item(gcd_tree, 0, i, abs(array[i]));
    }

    size_t row_width = length;
    for (size_t current_depth = 0; current_depth < gcd_tree->n_rows - 1; ++current_depth, row_width = (row_width + 1) >> 1) {
        bool row_width_is_odd = row_width & 1;
        for (size_t i = 0; i < row_width - row_width_is_odd; i += 2) {
            table_item_t l_child = get_item(gcd_tree, current_depth, i);
            table_item_t r_child = get_item(gcd_tree, current_depth, i + 1);
            set_item(gcd_tree, current_depth + 1, i >> 1, gcd(l_child, r_child));
        }
        if (row_width_is_odd) {
            set_item(gcd_tree, current_depth + 1, (row_width - 1) >> 1, get_item(gcd_tree, current_depth, row_width - 1));
        }
    }

    return gcd_tree;
}


size_t interval_gcd(LogTable *table, size_t l, size_t r, bool *error) {
    if (l > r) {
        *error = true;
        return 0;
    }
    size_t interval_size = r - l + 1;
    size_t result_depth = table->precomputed_logs[interval_size];
    size_t result_depth_bucket_size = 1 << result_depth;

    size_t res = 0;
    if (l % result_depth_bucket_size != 0) {
        size_t n_skipped_buckets = l / result_depth_bucket_size;
        size_t new_r = result_depth_bucket_size * (n_skipped_buckets + 1);
        res = gcd(res, interval_gcd(table, l, new_r - 1, error));  // Если один из операндов gcd - 0, то возвращается максимум из операндов.
        if (*error) {
            return 0;
        }
        if (res == 1) {
            return 1;
        }
        l = new_r;
    }
    if ((r + 1) % result_depth_bucket_size != 0) {
        size_t n_skipped_buckets = r / result_depth_bucket_size;
        size_t new_l = result_depth_bucket_size * n_skipped_buckets - 1;
        res = gcd(res, interval_gcd(table, new_l + 1, r, error));  // Если один из операндов gcd - 0, то возвращается максимум из операндов.
        if (*error) {
            return 0;
        }
        if (res == 1) {
            return 1;
        }
        r = new_l;
    }
    for (size_t i = l; i <= r; i += result_depth_bucket_size) {
        res = gcd(res, get_item(table, result_depth, i / result_depth_bucket_size));
        if (res == 1) {
            return 1;
        }
    }
    return res;
}