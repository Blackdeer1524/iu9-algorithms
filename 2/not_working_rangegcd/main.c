#include <stdio.h>
#include <string.h>

#include "segment_tree.h"


int main() {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }

    int *array = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        if (scanf("%d", array + i) != 1) {
            return EXIT_FAILURE;
        }
    }

    size_t m;
    if (scanf("%zu", &m) != 1) {
        free(array);
        return EXIT_FAILURE;
    }

    Node *tree = build_segment_tree(array, n);

    int status = EXIT_SUCCESS;
    for (size_t i = 0; i < m; ++i) {
        size_t l, r;
        if (scanf("%zu %zu", &l, &r) != 2) {
            status = EXIT_FAILURE;
            break;
        }
        int res = interval_gcd(tree, l, r);
        if (printf("%d\n", res) < 0) { 
            status = EXIT_FAILURE;
            break;
        }
    }

    free(array);
    free_segment_tree(tree);
    return status;
}