#include <stdlib.h>
#include <stdio.h>
#include "gcd_matrix.h"

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

    LogTable *tree = get_gcd_table(array, n);
    if (tree == NULL) {
        free(array);
        return EXIT_FAILURE;
    }

    bool error = false;
    int status = EXIT_SUCCESS;
    for (size_t i = 0; i < m; ++i) {
        size_t l, r;
        if (scanf("%zu %zu", &l, &r) != 2) {
            status = EXIT_FAILURE;
            break;
        }
        int res = interval_gcd(tree, l, r, &error);
        if (error || printf("%d\n", res) < 0) { 
            status = EXIT_FAILURE;
            break;
        }
    }

    free(array);
    table_free(tree);
    free(tree);
    return status;
    return 0;
}
