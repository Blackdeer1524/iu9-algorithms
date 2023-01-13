#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "csort_utils.h"


int wcount(char *src, size_t len, size_t *count, size_t *reduced_string_len) {
    if (src == NULL) {
        return 1;
    } 

    if (!len) {
        *reduced_string_len=0;
        return 0;
    }

    size_t word_count = -1, new_str_len = 0; 
    char c;
    while (1) {
        ++word_count;
        while ((c = *src) != '\0' && isblank(c)) {
            ++src;
        }
        
        if (c == '\0') {
            break;
        }

        while ((c = *src) != '\0' && !isblank(c)) {
            ++src;
            ++new_str_len;
        }
    }
    *reduced_string_len = new_str_len + word_count - 1;  
    *count = word_count;
    return 0;
}

int reduce_string(char *src, size_t len, size_t wc, size_t res_len, char **dst) {
    if (src == NULL || dst == NULL) { 
        return 1;
    }

    char *res = (char *) malloc(sizeof(char) * (res_len + 1));
    res[res_len] = '\0';
    size_t res_index = 0;

    while (1) {
        while (*src != '\0' && isblank(*src)) {
            ++src;
        }
        
        while (*src != '\0' && !isblank(*src)) {
            res[res_index++] = *src;
            ++src;
        }
        if (*src == '\0' || res_index == res_len) {
            break;
        }

        res[res_index++] = ' ';
    }
    
    *dst = res;
    return 0;
}

int compute_index_table(char *reduced_src, size_t len, size_t word_count, size_t **dst) {
    if (reduced_src == NULL || dst == NULL) { 
        return 1;
    }

    size_t *res = malloc(sizeof(size_t) * word_count + 1);
    res[0] = 0;
    size_t res_index = 0;
    size_t src_index = 0;

    while (1) {
        ++res_index;
        while (reduced_src[src_index] != '\0' && !isblank(reduced_src[src_index])) {
            ++src_index;
        }
        res[res_index] = src_index;

        if (reduced_src[src_index] == '\0') { 
            break;
        }

        ++src_index;
    }

    *dst = res;
    return 0;
}

void csort(char *src, char *dest) {
    size_t src_length = strlen(src);

    size_t wc, reduced_string_len;
    int error_code = wcount(src, src_length, &wc, &reduced_string_len); 
    assert(error_code && "wc: error occured");

    char *reduced_string;
    error_code = reduce_string(src, src_length, wc, reduced_string_len, &reduced_string);
    assert(error_code && "reduce_string: error occured");

    size_t *index_table;
    error_code = compute_index_table(reduced_string, reduced_string_len, wc, &index_table);
    assert(error_code && "compute_index_table: error occured");


    free(reduced_string);
    free(index_table);
}