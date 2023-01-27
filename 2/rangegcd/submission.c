#include <stdlib.h>
#include <stdio.h>

// #define DEBUG_

// =====lib/include/math_utils.h============

#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include <stdlib.h>

#define abs(x) (((x) > 0) ? (x) : -(x))

size_t gcd(size_t left, size_t right);

size_t int_log2(size_t x);

#endif

// =====lib/src/math_utils.c============

// #include "math_utils.h"

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


// =====lib/include/log_table.h============

#ifndef LOG_TABLE_H_
#define LOG_TABLE_H_

#include <stdbool.h>
#include <stdlib.h>
// #include "math_utils.h"

#ifdef DEBUG_
    #include <stdio.h>
    #include <errno.h>
    #include <string.h>
    #include <assert.h>

    #define clean_errno() (errno == 0 ? "None" : strerror(errno))
    #define log_error(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
    #define assertf(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }

    #define _check_index(log_table_ptr, row, col) do { \
        assertf(row < log_table->n_rows, \
        "requested row index: %zu; Max possible index: %zu", \
        row, log_table->n_rows); \
        \
        size_t row_bucket_size = 1 << row; \
        size_t n_buckets_in_row = log_table->n_cols / row_bucket_size + (log_table->n_cols % row_bucket_size != 0); \
        \
        assertf(col < n_buckets_in_row, \
                "requested index: [%zu][%zu]; Max allowed index for this row: (%zu x %zu)", \
                row, col, row, n_buckets_in_row - 1); \
    } while(0)

#else
    #define _check_index(log_table_ptr, row, col)
#endif


typedef int table_item_t;

typedef struct {
    table_item_t **data;
    size_t n_rows, n_cols;
} LogTable;


inline void table_free(LogTable *log_table) {
    for (size_t i = 0; i < log_table->n_rows; ++i) {
        free(log_table->data[i]);
    }
    free(log_table->data);
}


LogTable table_build(size_t n_cols, bool *error);


inline table_item_t get_item(LogTable *log_table, size_t row, size_t col) {
    _check_index(log_table, row, col);
    return log_table->data[row][col];
}


inline void set_item(LogTable *log_table, size_t row, size_t col, table_item_t item) {
    _check_index(log_table, row, col);
    log_table->data[row][col] = item;
}

#endif


// =====lib/src/log_table.c============

// #include "log_table.h"

inline void table_free(LogTable *log_table);

LogTable table_build(size_t n_cols, bool *error) {
    size_t n_rows = int_log2(n_cols) + 1;

    LogTable talbe = {
        .n_rows=n_rows,
        .n_cols=n_cols,
        .data=NULL
    };

    talbe.data = calloc(n_rows, sizeof(table_item_t *));
    if (talbe.data == NULL) {
        *error = true;
        return talbe;
    }

    for (size_t i = 0; i < n_rows; ++i) {
        talbe.data[i] = malloc(sizeof(table_item_t) * n_cols);
        if (talbe.data[i] == NULL) {
            table_free(&talbe);
            break;
        }
        n_cols = (n_cols + 1) >> 1;
    }
    
    *error = false;
    return talbe;
}


// =====lib/include/gcd_matrix.h============

#ifndef GCD_MATRIX_H_
#define GCD_MATRIX_H_

#include <stdlib.h>
// #include "log_table.h"

LogTable get_gcd_table(table_item_t *array, size_t length, bool *error);

size_t interval_gcd(LogTable *table, size_t l, size_t r, bool *error);

#endif

// =====lib/src/gcd_matrix.c============

// #include "gcd_matrix.h"
// #include "math_utils.h"


LogTable get_gcd_table(table_item_t *array, size_t length, bool *error) {
    LogTable gcd_tree;
    if (!length) {
        *error = true;
        return gcd_tree;
    }

    gcd_tree = table_build(length, error);
    if (*error) {
        return gcd_tree;
    }

    for (size_t i = 0; i < length; ++i) {
        set_item(&gcd_tree, 0, i, abs(array[i]));
    }

    size_t row_width = length;
    for (size_t current_depth = 0; current_depth < gcd_tree.n_rows - 1; ++current_depth, row_width = (row_width + 1) >> 1) {
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


size_t interval_gcd(LogTable *table, size_t l, size_t r, bool *error) {
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

//====main.c=================================

#include <stdlib.h>
#include <stdio.h>
// #include "gcd_matrix.h"

extern inline void table_free(LogTable *table);
extern inline table_item_t get_item(LogTable *table, size_t row, size_t col);
extern inline void set_item(LogTable *table, size_t row, size_t col, table_item_t item);

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
    LogTable tree = get_gcd_table(array, n, &error);
    if (error) {
        free(array);
        table_free(&tree);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;
    for (size_t i = 0; i < m; ++i) {
        size_t l, r;
        if (scanf("%zu %zu", &l, &r) != 2) {
            status = EXIT_FAILURE;
            break;
        }
        int res = interval_gcd(&tree, l, r, &error);
        if (error || printf("%d\n", res) < 0) { 
            status = EXIT_FAILURE;
            break;
        }
    }

    free(array);
    table_free(&tree);
    return status;
    return 0;
}
