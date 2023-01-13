#ifndef CSORT_H_
#define CSORT_H_

#include <stdlib.h>

int wcount(char *src, size_t len, size_t *count, size_t *trimmed_string_len);
int reduce_string(char *src, size_t len, char **dst);
int compute_index_table(char *reduced_src, size_t len, size_t word_count, size_t **dst);

#endif