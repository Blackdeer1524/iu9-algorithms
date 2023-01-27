#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

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

    size_t *res = malloc(sizeof(size_t) * (word_count + 1));
    res[0] = -1;
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

    if (src_length == 0) {
        dest[src_length] = '\0';
        return;
    }

    size_t wc, reduced_string_len;
    int error_code = wcount(src, src_length, &wc, &reduced_string_len); 
    assert(!error_code && "wc: error occured");
    dest[reduced_string_len] = '\0';

    char *reduced_string;
    error_code = reduce_string(src, src_length, wc, reduced_string_len, &reduced_string);
    assert(!error_code && "reduce_string: error occured");

    size_t *index_table;
    error_code = compute_index_table(reduced_string, reduced_string_len, wc, &index_table);
    assert(!error_code && "compute_index_table: error occured");

    size_t *rearranged_items = malloc(sizeof(size_t) * wc);
    for (size_t i = 0; i < wc; ++i) { 
        rearranged_items[i] = -1;
    }

    for (size_t current_word_index = 0; current_word_index < wc; ++current_word_index) {
        size_t current_word_length = index_table[current_word_index + 1] - index_table[current_word_index] - 1;
        size_t shorter_words_count = 0;
        for (size_t cmp_index = 0; cmp_index < wc; ++cmp_index) { 
            if (index_table[cmp_index + 1] - index_table[cmp_index] - 1 < current_word_length) {
                ++shorter_words_count;
            } 
        }
        while (rearranged_items[shorter_words_count] != -1) {
            ++shorter_words_count;
        }
        rearranged_items[shorter_words_count] = current_word_index;
    }   

    for (size_t i = 0; i < wc - 1; ++i) { 
        size_t ordered_word_index = rearranged_items[i];
        size_t ordered_word_length = index_table[ordered_word_index + 1] - index_table[ordered_word_index] - 1;
        strncpy(dest, reduced_string + (1 + index_table[ordered_word_index]), ordered_word_length);
        dest += ordered_word_length;
        dest[0] = ' ';
        ++dest;
    }
    size_t ordered_word_index = rearranged_items[wc - 1];
    size_t ordered_word_length = index_table[ordered_word_index + 1] - index_table[ordered_word_index] - 1;
    strncpy(dest, reduced_string + (1 + index_table[ordered_word_index]), ordered_word_length);

    free(reduced_string);
    free(index_table);
    free(rearranged_items);
}


#define BUFFER_SIZE 1001

int main() {
    char buffer[BUFFER_SIZE] = {'\0'};
    
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        return EXIT_FAILURE;
    }
    size_t scanned_strlen = strlen(buffer); 
    if (scanned_strlen > 0 && buffer[scanned_strlen - 1] == '\n')
        buffer[--scanned_strlen] = '\0';

    char *dest = (char *) malloc(sizeof(char) * (scanned_strlen + 1));
    
    csort(buffer, dest);

    printf("%s", dest);

    free(dest);
    return EXIT_SUCCESS;
}
