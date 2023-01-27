#ifndef GCD_MATRIX_H_
#define GCD_MATRIX_H_

#include <stdlib.h>
#include "log_table.h"

LogTable get_gcd_table(table_item_t *array, size_t length, bool *error);

size_t interval_gcd(LogTable *table, size_t l, size_t r, bool *error);

#endif