#include "math_utils.h"


size_t gcd(size_t left, size_t right) {
    while (left && right) {
        if (left > right) {
            left %= right;
        } else {
            right %= left;
        }
    }
    return left + right;
} 


size_t *precompute_log2(size_t x) {
    size_t *precomputed_table = malloc(sizeof(size_t) * (x + 1));
    if (precomputed_table == NULL) {
        return NULL;
    }
    precomputed_table[0] = 0;
    if (x == 1) {
        return precomputed_table;
    }
    precomputed_table[1] = 0;
    size_t current_log2 = 1;
    for (size_t i = 2; i <= x; ++i) {
        while ((1u << (current_log2 + 1)) <= i) {
            ++current_log2;
        }
        precomputed_table[i] = current_log2;
    }
    return precomputed_table;
}
