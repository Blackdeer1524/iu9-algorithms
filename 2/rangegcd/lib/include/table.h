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
        .data=(table_item_t *) malloc(n_rows * n_cols * sizeof(table_item_t)),
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


extern inline Table table_build(size_t n_rows, size_t n_cols);
extern inline void table_free(Table *table);
extern inline size_t _get_index(Table *table, size_t row, size_t col);
extern inline table_item_t get_item(Table *table, size_t row, size_t col);
extern inline void set_item(Table *table, size_t row, size_t col, table_item_t item);

#endif
