#include <stdlib.h>
#include <stdio.h>
#include "prefix.h"


int build_prefix_table(char *src, size_t length, size_t **table) {
    if (src == NULL || table == NULL) {
        return 1;
    }

    size_t *allocated_table = calloc(length, sizeof(size_t));
    if (allocated_table == NULL) {
        return 1;
    }

    size_t table_pivot = 0;
    for (size_t src_pivot = 1; src_pivot < length; ++src_pivot) {
        while (table_pivot > 0 && src[table_pivot] != src[src_pivot]) {
            table_pivot = allocated_table[table_pivot - 1];
        }
        if (src[table_pivot] == src[src_pivot]) {
            ++table_pivot;
        }
        allocated_table[src_pivot] = table_pivot;
    }
    
    *table = allocated_table;    
    return 0;
}


size_t gcd(size_t left, size_t right) {
    if (left <= 1 || right <= 1) {
        return 1;
    }
    
    while (left && right) {
        if (left > right) {
            left = left % right;
        } else { 
            right = right % left;
        } 
    }
    return left + right;
}


int find_prefixes(char *src, size_t len) {
    if (src == NULL) {
        return 1;
    }

    size_t *prefix_table;
    int res = build_prefix_table(src, len, &prefix_table);
    if (res) {
        return 1;
    }

    for (size_t i = 1; i < len; ++i) { 
        if (!prefix_table[i]) {
            continue;
        }

        size_t periodic_prefix_length = gcd(prefix_table[i], i + 1);
        for (size_t j = 0; j < i - periodic_prefix_length; ++j) {
            if (src[j] != src[j + periodic_prefix_length]) {
                goto failed_to_find;
            }
        }
        printf("%zu %zu\n", i + 1, (i + 1) / periodic_prefix_length);
        failed_to_find:
    }
    
    free(prefix_table);
    return 0;
}
