#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "heap.h"

int int_cmp(const int *l, const int *r) {
    if (*l > *r) {
        return 1;
    } else if (*l < *r) {
        return -1;
    } else {
        return 0;
    }
}


int char_count_cmp(const void *l, const void *r) {
    size_t l_len = strlen(*((char **)l));
    size_t r_len = strlen(*((char **)r));
    if (l_len > r_len) {
        return 1;
    } else if (l_len < r_len) {
        return -1;
    }
    return 0;
}



int main() {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return 1;
    }

    char **arr = malloc(sizeof(char *) * n);
    for (size_t i = 0; i < n; ++i) {
        arr[i] = malloc(1000 * sizeof(char));
        if (scanf("%s", arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    hsort(arr, n, sizeof arr[0], char_count_cmp);

    for (size_t i = 0; i < n; ++i) {
        printf("%s\n", arr[i]);
    }

    free(arr);
    return 0;
}