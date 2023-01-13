#ifndef PREFIX_H_
#define PREFIX_H_

#include <stdlib.h>

int build_prefix_table(char *src, size_t length, size_t **dst);
size_t gcd(size_t left, size_t right);
int find_prefixes(char *src, size_t len);

#endif