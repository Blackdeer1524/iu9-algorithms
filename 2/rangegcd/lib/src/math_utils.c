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


size_t int_log2(size_t x) {
    size_t res = 0;
    while (x >>= 1) {
        ++res;
    }
    return res;
}
