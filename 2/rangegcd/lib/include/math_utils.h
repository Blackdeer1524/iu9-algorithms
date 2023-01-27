#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include <stdlib.h>

#define abs(x) (((x) > 0) ? (x) : -(x))

size_t gcd(size_t left, size_t right);

size_t int_log2(size_t x);

#endif