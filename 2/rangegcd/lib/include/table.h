#ifndef TABLE_H_
#define TABLE_H_

#include <stdlib.h>
#include <stdbool.h>

#define DEBUG_

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


typedef struct {
    size_t N;
    size_t *data;
    size_t total_size;
} Table;


inline Table talbe_build(size_t N) {
    size_t total_size = N * (N + 1) / 2;
    Table talbe = {
        .N=N,
        .data=malloc(total_size * sizeof(size_t)),
        .total_size=total_size
    };
    return talbe;
}


inline size_t _get_index(Table *table, size_t row, size_t col) {
    assertf(row < table->N && col < table->N, 
            "requested index: [%zu][%zu]; table size: %zu", 
            row, col, table->N);
    return table->total_size - (table->N - row) * (table->N - row + 1) / 2 + col; 
} 


inline size_t get_item(Table *table, size_t row, size_t col) {
    assertf(row < table->N && col < table->N, 
            "requested index: [%zu][%zu]; table size: %zu", 
            row, col, table->N);
    size_t index = _get_index(table, row, col);
    return table->data[index];
}


inline void set_item(Table *table, size_t row, size_t col, size_t item) {
    assertf(row < table->N && col < table->N, 
            "[index error]: requested index: [%zu][%zu]; table size: %zu", 
            row, col, table->N);
    size_t index = _get_index(table, row, col);
    table->data[index] = item;
}


#endif
