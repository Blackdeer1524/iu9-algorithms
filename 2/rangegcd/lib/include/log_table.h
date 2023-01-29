#ifndef LOG_TABLE_H_
#define LOG_TABLE_H_

#include <stdbool.h>
#include <stdlib.h>
#include "math_utils.h"

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
    size_t *precomputed_logs;
} LogTable;


inline void table_free(LogTable *log_table) {
    for (size_t i = 0; i < log_table->n_rows; ++i) {
        free(log_table->data[i]);
    }
    free(log_table->precomputed_logs);
    free(log_table->data);
}


LogTable *table_build(size_t n_cols);


inline table_item_t get_item(LogTable *log_table, size_t row, size_t col) {
    _check_index(log_table, row, col);
    return log_table->data[row][col];
}


inline void set_item(LogTable *log_table, size_t row, size_t col, table_item_t item) {
    _check_index(log_table, row, col);
    log_table->data[row][col] = item;
}

#endif
