#include <stdlib.h>
#include <ctype.h>

#include "csort_utils.h"


int wcount(char *src, size_t len, size_t *count, size_t *trimmed_string_len) {
    if (src == NULL) {
        return 1;
    } 

    if (!len) {
        *trimmed_string_len=0;
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
    *trimmed_string_len = new_str_len + word_count - 1;  
    *count = word_count;
    return 0;
}

int reduce_string(char *src, size_t len, char **dst) {
    if (src == NULL || dst == NULL) { 
        return 1;
    }

    size_t wc, res_len;
    int error_code = wcount(src, len, &wc, &res_len);
    if (error_code) {
        return error_code;
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
