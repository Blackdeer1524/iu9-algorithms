#ifndef GCD_MATRIX_H_
#define GCD_MATRIX_H_

#include <stdlib.h>
#include "table.h"

size_t gcd(size_t left, size_t right);

size_t int_log2(size_t x);

Table get_gcd_table(table_item_t *array, size_t length, bool *error);

size_t interval_gcd(Table *table, size_t l, size_t r, bool *error);

#endif