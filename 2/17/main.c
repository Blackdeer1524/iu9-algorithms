#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TABLE_ITEM_T int


typedef struct{
    TABLE_ITEM_T *table;
    size_t n_rows;
    size_t n_cols;
} Table;


int table_new(Table **dst, size_t n_rows, size_t n_cols) {
    *dst = malloc(sizeof(Table));
    if (*dst == NULL) {
        return 1;
    }
    (*dst)->table=malloc(sizeof(TABLE_ITEM_T) * n_rows * n_cols);
    (*dst)->n_rows=n_rows;
    (*dst)->n_cols=n_cols;
    return 0;
}

TABLE_ITEM_T *table_at(const Table *table, size_t row, size_t col) {
    return table->table + row * table->n_cols + col;
}

int safe_table_at(const Table *table, size_t row, size_t col, TABLE_ITEM_T *res) {
    if (row > table->n_rows || col > table->n_cols) {
        return 1;
    }

    *res = *table_at(table, row, col);
    return 0;
}


int safe_table_set(Table *table, size_t row, size_t col, TABLE_ITEM_T data) {
    if (row > table->n_rows || col > table->n_cols) {
        return 1;
    }

    *table_at(table, row, col) = data;
    return 0;
}


#define panicing_table_at(table_ptr, row, col, dst_ptr) {\
    int res = safe_table_at((table_ptr), (row), (col), (dst_ptr));\
    if (res) {\
        printf("%s:%d Couldn't get item from table[%zu][%zu]\n", __func__, __LINE__, (size_t)(row), (size_t)(col));\
        exit(1);\
    }\
}

#define panicing_table_set(table_ptr, row, col, item) {\
    int res = safe_table_set((table_ptr), (row), (col), (item));\
    if (res) {\
        printf("%s:%d Couldn't set item to table[%zu][%zu]\n", __func__, __LINE__, (size_t)(row), (size_t)(col));\
        exit(1);\
    }\
}

#define panicing_table_get_max_item_index_on_prefix(table_ptr, end, dst_ptr) {\
    if (!(end)) {\
        *dst_ptr = (end);\
    }\
    int res = safe_table_at((table_ptr), (end), 0, (dst_ptr));\
    if (res) {\
        printf("%s:%d Couldn't get index of max item on [0, %zu] interval\n", __func__, __LINE__, (size_t)(end));\
        exit(1);\
    }\
}


#define panicing_table_set_max_item_index_on_prefix(table_ptr, end, index) {\
    if (end) {\
        int res = safe_table_set((table_ptr), (end), 0, (index));\
        if (res) {\
            printf("%s:%d Couldn't set index of max item on [0, %zu] interval\n", __func__, __LINE__, (size_t)(end));\
            exit(1);\
        }\
    }\
}


void fill_table(const TABLE_ITEM_T *array, size_t length, Table *table, size_t start, size_t end) {
    panicing_table_set(table, start, start, array[start]);
    TABLE_ITEM_T prev_max_on_prefix = array[start];
    
    for (TABLE_ITEM_T i = start + 1; i < end; ++i) {
        panicing_table_set(table, i, i, array[i]);

        TABLE_ITEM_T index_of_max_on_current_prefix;
        if (prev_max_on_prefix <= array[i]) {
            panicing_table_set_max_item_index_on_prefix(table, i, i);
            index_of_max_on_current_prefix = i;
        } else {
            panicing_table_get_max_item_index_on_prefix(table, i - 1, &index_of_max_on_current_prefix);
            panicing_table_set_max_item_index_on_prefix(table, i,      index_of_max_on_current_prefix);
        }

        TABLE_ITEM_T max_on_current_prefix = array[index_of_max_on_current_prefix];
        prev_max_on_prefix = max_on_current_prefix;

        for (size_t j = 0; j <= index_of_max_on_current_prefix; ++j) {
            panicing_table_set(table, j, i, max_on_current_prefix);
        }

        for (size_t filling_row_index = index_of_max_on_current_prefix + 1; filling_row_index < i; ++filling_row_index) {
            TABLE_ITEM_T prev_max_of_filling_row;
            panicing_table_at(table, filling_row_index, i - 1, &prev_max_of_filling_row);

            if (prev_max_of_filling_row < array[i]) {
                panicing_table_set(table, filling_row_index, i, array[i]);
            } else {
                panicing_table_set(table, filling_row_index, i, prev_max_of_filling_row);
            }
        }
    }
}


#define ARRAY_SIZE 8

int main() {
    TABLE_ITEM_T array[ARRAY_SIZE] = {-1, 3, 2, -10, 10, 5, 3, 0};
    TABLE_ITEM_T table_data[ARRAY_SIZE * ARRAY_SIZE] = {};
    
    Table table = {
        .table = table_data,
        .n_cols = ARRAY_SIZE,
        .n_rows = ARRAY_SIZE,
    };
    
    fill_table(array, ARRAY_SIZE, &table, 0, ARRAY_SIZE);

    return 0;
}