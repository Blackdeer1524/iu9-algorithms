#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

size_t *get_forward_kmp_table(const char *pattern, size_t length) { 
    // a b a b c a b a b a b c
    // 0 0 1 2 0 1 2 3 4 3 4 5
    size_t *table = calloc(sizeof(size_t), length);

    size_t pattern_pivot_index = 0;
    size_t i = 1;

    while (i < length) {
        if (pattern[i] == pattern[pattern_pivot_index]) {
            ++pattern_pivot_index;
            table[i] = pattern_pivot_index;
            ++i;
        } else {
            if (pattern_pivot_index) {
                pattern_pivot_index = table[pattern_pivot_index - 1];
            } else {
                ++i;
            }
        }
    }
    return table;
}


typedef enum {
    YES = 1,
    NO = 0,
} is_prefix_t;


is_prefix_t is_prefix(const char *checking, size_t checking_len, const char *prefixes_container, size_t prefixes_container_len) {
    size_t *forward_kmp = get_forward_kmp_table(prefixes_container, prefixes_container_len);

    size_t prefix_index = 0;
    size_t i = 0;
    while (i < checking_len) {
        if (checking[i] == prefixes_container[prefix_index]) {
            ++i;
            ++prefix_index;
        } else {
            if (prefix_index) {
                prefix_index = forward_kmp[prefix_index - 1];
            } else {
                free(forward_kmp);
                return NO;
            }
        }
    }    

    free(forward_kmp);
    return YES;
}


int main(int argc, char *argv[]) {
    char *S = argv[1];
    char *T = argv[2];

    is_prefix_t res = is_prefix(T, strlen(T), S, strlen(S));
    if (res == YES) {
        printf("yes");
    } else {
        printf("no");
    }
    return 0;
    // test_pattern_matrix();
    // test_search();
}