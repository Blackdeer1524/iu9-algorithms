#include "log_table.h"

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
