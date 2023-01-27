#include "log_table.h"

inline void table_free(LogTable *log_table);

LogTable table_build(size_t n_cols, bool *error) {
    size_t n_rows = int_log2(n_cols - 1) + 1;

    LogTable talbe = {
        .n_rows=n_rows,
        .n_cols=n_cols,
        .data=NULL
    };

    table_item_t **data = calloc(n_rows, sizeof(table_item_t *));
    if (data == NULL) {
        *error = true;
        return talbe;
    }

    talbe.data = data;
    for (size_t i = 0; i < n_rows; ++i) {
        talbe.data[i] = malloc(sizeof(table_item_t) * n_cols);
        if (data[i] == NULL) {
            table_free(&talbe);
            break;
        }
        n_cols = (n_cols + 1) >> 1;
    }
    
    *error = false;
    talbe.data = data;
    return talbe;
}
