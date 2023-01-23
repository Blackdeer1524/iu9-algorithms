#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define at(array, N, row, col) ((array)[(N) * (row) + (col)])

#define free_4(first, second, third, fourth) do { \
    free(first); \
    free(second); \
    free(third); \
    free(fourth); \
} while(0)


int main() {    
    size_t n_rows, n_cols;
    if (scanf("%zu %zu", &n_rows, &n_cols) != 2) {
        return EXIT_FAILURE;
    }
    int *data_array =         (int *) malloc(sizeof(int) * n_rows * n_cols);
    int *row_maxima =         (int *) malloc(sizeof(int) * n_rows);
    int *row_maxima_indices = (int *) malloc(sizeof(int) * n_rows);
    int *col_minima =         (int *) malloc(sizeof(int) * n_cols);
    
    if (data_array == NULL || col_minima == NULL || row_maxima == NULL || row_maxima_indices == NULL) {
        free_4(data_array, col_minima, row_maxima, row_maxima_indices);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < n_cols; ++i) {
        col_minima[i] = INT_MAX;
    }

    for (size_t i = 0; i < n_rows; ++i) {
        row_maxima[i] = INT_MIN; 
        row_maxima_indices[i] = 0; 
    }
    for (size_t row_index = 0; row_index < n_rows; ++row_index) {
        for (size_t col_index = 0; col_index < n_cols; ++col_index) {
            if (!scanf("%d", &at(data_array, n_cols, row_index, col_index))) {
                free_4(data_array, col_minima, row_maxima, row_maxima_indices);
                return EXIT_FAILURE;
            }

            if (row_maxima[row_index] < at(data_array, n_cols, row_index, col_index)) {
                row_maxima[row_index] = at(data_array, n_cols, row_index, col_index);
                row_maxima_indices[row_index] = col_index;
            }
            if (col_minima[col_index] > at(data_array, n_cols, row_index, col_index)) {
                col_minima[col_index] = at(data_array, n_cols, row_index, col_index);
            }
        }
    }

    int exit_status = EXIT_SUCCESS;
    int found = 0;

    for (size_t i = 0; i < n_rows; ++i) {
        int current_row_max = row_maxima[i];
        int column_of_row_max = row_maxima_indices[i];
        if (col_minima[column_of_row_max] == current_row_max) {
            if (printf("%zu %d", i, column_of_row_max) < 0) {
                exit_status = EXIT_FAILURE;
            }
            found = 1;
            break;  
        }
    }
    if (!found) {
        puts("none");
    }

    free_4(data_array, col_minima, row_maxima, row_maxima_indices);
    return exit_status;
}