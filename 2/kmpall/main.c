#include <stdlib.h> 
#include <stdio.h>

// https://www.youtube.com/watch?v=V5-7GzOfADQ
size_t *prepare_pattern(const char *pattern, size_t length, size_t *first_nonzero_index) {
    size_t *pattern_matrix = calloc(length, sizeof(size_t));  // easier to index
    size_t prefix_index = 0;

    size_t i = 1;
    for (; i < length && pattern[i] != pattern[prefix_index]; ++i) {}

    *first_nonzero_index = i;
    if (i == length) {
        return pattern_matrix;
    }

    for (; i < length; ++i) {
        if (pattern[i] == pattern[prefix_index]) {
            pattern_matrix[i] = pattern_matrix[i - 1] + 1;
            ++prefix_index;
        } else {
            prefix_index = 0;
            if (pattern[i] == pattern[prefix_index]) {
                pattern_matrix[i] = 1;
                ++prefix_index;
            }
        }
    }
    return pattern_matrix;
}


size_t print_all_string_occurrences(const char *src, size_t src_length, char *search_string, size_t search_length) {
    //                       |------ subpattern start
    //                       V
    // if search_string = "ababac", then first_subpattern_index = 2
    //                       ~~~
    //                              a b a b a c
    // and pattern_matrix will be: [0,0,1,2,3,0]
    size_t first_subpattern_occurrence = 0;
    size_t *pattern_matrix = prepare_pattern(search_string, search_length, &first_subpattern_occurrence);
    // find all suffixes that are ALSO prefixes (prefix and suffix can overlap):        ababab

    size_t prefix_index = 0;
    size_t i = 0;
    while (i < src_length) {
        if (prefix_index == search_length) {
            printf("%zu ", i - prefix_index);
            prefix_index = pattern_matrix[prefix_index - 1];
        }
        if (src[i] == search_string[prefix_index]) {
            ++prefix_index;
            ++i;
        } else {
            if (prefix_index) {
                prefix_index = pattern_matrix[prefix_index - 1];
            } else {
                ++i;
            }
        }
    }
    if (prefix_index == search_length) {
        printf("%zu ", i - prefix_index);
    }
}

#include <assert.h>
#include <string.h>

void test_pattern_matrix() {
    char *pattern = "abcabcaaba";
    size_t pattern_length = strlen(pattern);
    size_t first_subpattern_occurance = 0;
    size_t *pattern_matrix = prepare_pattern(pattern, pattern_length, &first_subpattern_occurance);

    assert(first_subpattern_occurance == 3);
    assert(pattern_matrix[0] == 0);
    assert(pattern_matrix[1] == 0);
    assert(pattern_matrix[2] == 0);
    assert(pattern_matrix[3] == 1);
    assert(pattern_matrix[4] == 2);
    assert(pattern_matrix[5] == 3);
    assert(pattern_matrix[6] == 4);
    assert(pattern_matrix[7] == 1);
    assert(pattern_matrix[8] == 2);
    assert(pattern_matrix[9] == 1);
    
    free(pattern_matrix); 
}


void test_search_single(char *src, char *search_string, size_t asserion) {
    assert(print_all_string_occurrences(src, strlen(src), search_string, strlen(search_string)) == asserion);
}

void test_search() {
    print_all_string_occurrences("ababc", strlen("ababc"), "abc", strlen("abc"));
    putc('\n', stdout);
    print_all_string_occurrences("abababc", strlen("abababc"), "ababc", strlen("ababc"));
    putc('\n', stdout);
    print_all_string_occurrences("AAAAAAAAAAAAAAAAAB", strlen("AAAAAAAAAAAAAAAAAB"), "AAAAB", strlen("AAAAB"));
    putc('\n', stdout);
    print_all_string_occurrences("ababababc", strlen("ababababc"), "ababab", strlen("ababab"));
    putc('\n', stdout);
//    test_search_single("ababc", "abc", 2);
//    test_search_single("abababc", "ababc", 2);
//    test_search_single("AAAAAAAAAAAAAAAAAB", "AAAAB", 13);
}
// 0 0 0 1 2 3 0
// a b c a b c d
// a b c a a b c a b c d
// 0 1 2 3 4 5 6 7 8 9 10


int main(int argc, char *argv[]) { 
    print_all_string_occurrences(argv[2], strlen(argv[2]), argv[1], strlen(argv[1]));
    // test_pattern_matrix();
    // test_search();
    return 0;
}