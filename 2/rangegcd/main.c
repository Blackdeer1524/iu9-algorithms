#include <stdlib.h>
#include <stdio.h>
#include "table.h"


extern inline Table table_build(size_t n_rows, size_t n_cols);
extern inline void table_free(Table *table);
extern inline size_t _get_index(Table *table, size_t row, size_t col);
extern inline table_item_t get_item(Table *table, size_t row, size_t col);
extern inline void set_item(Table *table, size_t row, size_t col, table_item_t item);


int main() {
    // size_t n;
    // if (scanf("%zu", &n) != 1) {
    //     return EXIT_FAILURE;
    // }

    // int *array = malloc(sizeof(int) * n);
    // for (size_t i = 0; i < n; ++i) {
    //     if (scanf("%d", array + i) != 1) {
    //         free(array);
    //         return EXIT_FAILURE;
    //     }
    //     if (array[i] < 0) {
    //         array[i] = -array[i];
    //     }
    // }
    
    
    size_t n = 10;
    int array[] = {-3, 1, 5, 10, 13, 26, -52, 0, 10, 0};
    for (size_t i = 0; i < n; ++i) { 
        if (array[i] < 0) {
            array[i] = -array[i];
        }
    }

    


    return EXIT_SUCCESS;
}