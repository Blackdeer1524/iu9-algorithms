#include "log_table.h"

inline void table_free(LogTable *log_table);

LogTable *table_build(size_t n_cols) {
    LogTable *table = malloc(sizeof(LogTable));
    if (table == NULL) {
        return NULL;
    }
    table->precomputed_logs = precompute_log2(n_cols);
    if (table->precomputed_logs == NULL) {
        free(table);
        return NULL;
    }
    size_t n_rows = table->precomputed_logs[n_cols] + 1;
    table->data = calloc(n_rows, sizeof(table_item_t *));
    if (table->data == NULL) {
        free(table->precomputed_logs);
        free(table);
        return NULL;
    }
    table->n_cols = n_cols;
    table->n_rows = n_rows;

    for (size_t i = 0; i < n_rows; ++i) {
        table->data[i] = malloc(sizeof(table_item_t) * n_cols);
        if (table->data[i] == NULL) {
            table_free(table);
            free(table);
            return NULL;
        }
        n_cols = (n_cols + 1) >> 1;
    }
    
    return table;
}