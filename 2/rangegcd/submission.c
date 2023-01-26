#include <stdlib.h>
#include <stdio.h>

// #define DEBUG_

// =====lib/include/table.h============

#ifndef TABLE_H_
#define TABLE_H_

#include <stdlib.h>
#include <stdbool.h>

#ifdef DEBUG_
    #include <stdio.h>
    #include <errno.h>
    #include <string.h>
    #include <assert.h>

    #define clean_errno() (errno == 0 ? "None" : strerror(errno))
    #define log_error(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
    #define assertf(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
#else
    #define assertf(...)
#endif


typedef int table_item_t;

typedef struct {
    table_item_t *data;
    size_t n_rows, n_cols;
} Table;


inline Table table_build(size_t n_rows, size_t n_cols) {
    Table talbe = {
        .n_rows=n_rows,
        .n_cols=n_cols,
        .data=(table_item_t *) calloc(n_rows * n_cols, sizeof(table_item_t)),
    };
    return talbe;
}

inline void table_free(Table *table) {
    free(table->data);
}

inline size_t _get_index(Table *table, size_t row, size_t col) {
    assertf(row < table->n_rows && col < table->n_cols, 
            "requested index: [%zu][%zu]; table size: (%zu x %zu)", 
            row, col, table->n_rows, table->n_cols);
    return row * table->n_cols + col;
} 


inline table_item_t get_item(Table *table, size_t row, size_t col) {
    size_t index = _get_index(table, row, col);
    return table->data[index];
}


inline void set_item(Table *table, size_t row, size_t col, table_item_t item) {
    size_t index = _get_index(table, row, col);
    table->data[index] = item;
}

#endif


// =====lib/include/gcd_matrix.h============

#ifndef GCD_MATRIX_H_
#define GCD_MATRIX_H_

#include <stdlib.h>

size_t gcd(size_t left, size_t right);

size_t int_log2(size_t x);

Table get_gcd_table(table_item_t *array, size_t length, bool *error);

size_t interval_gcd(Table *table, size_t l, size_t r, bool *error);

#endif

// =====lib/src/gcd_matrix.c============

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

    int depth = (int) int_log2(length) + 1;
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


size_t interval_gcd(Table *table, size_t l, size_t r, bool *error) {
    if (l > r) {
        *error = true;
        return 0;
    }
    size_t interval_size = r - l + 1;
    size_t result_depth = int_log2(interval_size);
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

//===========================================

extern inline Table table_build(size_t n_rows, size_t n_cols);
extern inline void table_free(Table *table);
extern inline size_t _get_index(Table *table, size_t row, size_t col);
extern inline table_item_t get_item(Table *table, size_t row, size_t col);
extern inline void set_item(Table *table, size_t row, size_t col, table_item_t item);

int main() {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }

    int *array = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        if (scanf("%d", array + i) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    size_t m;
    if (scanf("%zu", &m) != 1) {
        free(array);
        return EXIT_FAILURE;
    }
    
    bool error = false;
    Table tree = get_gcd_table(array, n, &error);
    if (error) {
        free(array);
        table_free(&tree);
        return EXIT_FAILURE;
    }

    size_t *results = (size_t*) malloc(m * sizeof(size_t));

    int status = EXIT_SUCCESS;
    for (size_t i = 0; i < m; ++i) {
        size_t l, r;
        if (scanf("%zu %zu", &l, &r) != 2) {
            status = EXIT_FAILURE;
            break;
        }
        results[i] = interval_gcd(&tree, l, r, &error);
        if (error) { 
            status = EXIT_FAILURE;
            break;
        }    
    }
    
    if (status != EXIT_FAILURE) {
        for (size_t i = 0; i < m; ++i) {
            if (printf("%zu\n", results[i]) < 0) { 
                status = EXIT_FAILURE;
                break;
            }
        }
    }

    free(results);
    free(array);
    table_free(&tree);
    return status;
}
