#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <stdio.h>


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


#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

size_t *prepare_good_suffix_rule(const char *pattern, size_t length) { 
    size_t *jump_table = malloc(sizeof(size_t) * length);
        for (size_t i = 0; i < length; ++i) {
        jump_table[i] = i;
    }

    if (length == 1) {
        return jump_table;
    }

    size_t *backward_kmp_preprocess = calloc(length + 1, sizeof(size_t));

    size_t right_index = length - 1;

    size_t pattern_pivot_index = right_index;
    size_t i = length - 2;

    size_t cum_sum = 0;
    while (i) {
        if (pattern[i] == pattern[pattern_pivot_index]) {
            cum_sum += 1;
            backward_kmp_preprocess[i] += cum_sum;

            size_t jump_table_index = right_index - (backward_kmp_preprocess[i] - 1);
            pattern_pivot_index -= 1;
            i -= 1;

            if (pattern[i] != pattern[jump_table_index - 1]) {
                jump_table[jump_table_index] = min(pattern_pivot_index - i, jump_table[jump_table_index]);
                if (pattern_pivot_index < right_index) {
                    pattern_pivot_index = right_index - backward_kmp_preprocess[pattern_pivot_index + 1];
                } else {
                    i -= 1;
                }
                cum_sum = right_index - pattern_pivot_index; 
            }                             
        } else {
            if (pattern_pivot_index < right_index) {
                pattern_pivot_index = right_index - backward_kmp_preprocess[pattern_pivot_index + 1];
            } else {
                i -= 1;
            }
            cum_sum = right_index - pattern_pivot_index;
        }
    }
        
    while (!i) {
        if (pattern[i] == pattern[pattern_pivot_index]) {
            cum_sum += 1;
            backward_kmp_preprocess[i] += cum_sum;

            size_t jump_table_index = right_index - (backward_kmp_preprocess[i] - 1);
            pattern_pivot_index -= 1;
            i -= 1;

            jump_table[jump_table_index] = min(pattern_pivot_index - i, jump_table[jump_table_index]);
        }
        if (pattern_pivot_index < right_index) {
            pattern_pivot_index = right_index - backward_kmp_preprocess[pattern_pivot_index + 1];
        } else {
            i -= 1;
        }
        cum_sum = right_index - pattern_pivot_index;
    }

    free(backward_kmp_preprocess);
    return jump_table;
}


typedef struct{
    size_t *table;
    size_t n_rows;
    size_t n_cols;
} Table;


int table_new(Table **dst, size_t n_rows, size_t n_cols) {
    *dst = malloc(sizeof(Table));
    if (*dst == NULL) {
        return 1;
    }
    (*dst)->table=calloc(sizeof(size_t), n_rows * n_cols);
    (*dst)->n_rows=n_rows;
    (*dst)->n_cols=n_cols;
    return 0;
}


void table_free(Table *table) {
    free(table->table);
    free(table);
}


size_t *table_at(const Table *table, size_t row, size_t col) {
    return table->table + row * table->n_cols + col;
}

int safe_table_at(const Table *table, size_t row, size_t col, size_t *res) {
    if (row > table->n_rows || col > table->n_cols) {
        return 1;
    }

    *res = *table_at(table, row, col);
    return 0;
}


int safe_table_set(Table *table, size_t row, size_t col, size_t data) {
    if (row > table->n_rows || col > table->n_cols) {
        return 1;
    }

    *table_at(table, row, col) = data;
    return 0;
}


#define panicing_table_at(table_ptr, row, col, dst_ptr) {\
    size_t res = safe_table_at((table_ptr), (row), (col), (dst_ptr));\
    if (res) {\
        printf("%s:%d Couldn't get item from table[%zu][%zu]\n", __func__, __LINE__, (size_t)(row), (size_t)(col));\
        exit(1);\
    }\
}

#define panicing_table_set(table_ptr, row, col, item) {\
    size_t res = safe_table_set((table_ptr), (row), (col), (item));\
    if (res) {\
        printf("%s:%d Couldn't set item to table[%zu][%zu]\n", __func__, __LINE__, (size_t)(row), (size_t)(col));\
        exit(1);\
    }\
}

#define LOWEST_CHAR_CODE 33
#define HIGHEST_CHAR_CODE 126
#define N_ALLOWED_CHARS (HIGHEST_CHAR_CODE - LOWEST_CHAR_CODE + 1)

Table *prepare_bad_character_rule(const char *pattern, size_t length) {
    Table *jump_table;
    assert(!table_new(&jump_table, N_ALLOWED_CHARS, length) && "Couldn't allocate jump table for prepare_bad_character_rule");

    static size_t last_valid_item_lookup[N_ALLOWED_CHARS];
    for (size_t i = 0; i < N_ALLOWED_CHARS; ++i) {
        last_valid_item_lookup[i] = 0;
    }

    for (size_t i = 0; i < jump_table->n_rows; ++i) {
        for (size_t j = 0; j < jump_table->n_cols; ++j) {
            panicing_table_set(jump_table, i, j, j + 1);
        }
    }

    for (size_t i = 1; i < length; ++i) { 
        size_t prev_char_index = pattern[i - 1] - LOWEST_CHAR_CODE;

        panicing_table_set(jump_table, prev_char_index, i, 1);
        if (last_valid_item_lookup[prev_char_index]) {
            for (size_t j = last_valid_item_lookup[prev_char_index]; j < i; ++j) {
                size_t prev_item;
                panicing_table_at(jump_table, prev_char_index, j - 1, &prev_item);
                panicing_table_set(jump_table, prev_char_index, j, prev_item + 1);
            }
        }
        last_valid_item_lookup[prev_char_index] = i + 1;
    }

    for (size_t i = 0; i < N_ALLOWED_CHARS; ++i) {
        size_t row_last_valid_item = last_valid_item_lookup[i];
        if (!row_last_valid_item) {
            continue;
        }

        for (size_t j = row_last_valid_item; j < length; ++j) {
            size_t prev_item;
            panicing_table_at(jump_table, i, j - 1, &prev_item);
            panicing_table_set(jump_table, i, j, prev_item + 1);
        }
    }
    return jump_table;
}


void boyer_moore_str_search(const char *src, size_t src_length, const char *pattern, size_t pattern_length) {
    if (!src_length || !pattern_length || src == NULL || pattern == NULL) {
        return;
    }

    size_t *good_suffix_jump_table = prepare_good_suffix_rule(pattern, pattern_length);
    Table *bad_char_jump_table = prepare_bad_character_rule(pattern, pattern_length);
    size_t *forward_kmp_table = get_forward_kmp_table(pattern, pattern_length);

    size_t offset = 0;
    size_t left_bound = 0;
    while (offset + pattern_length <= src_length) { 
        size_t i = pattern_length;
        do {
            --i;
            if (src[offset + i] != pattern[i]) {
                goto found_some_difference;
            }
        } while (i > left_bound);

        printf("%zu ", offset);
        offset += pattern_length - forward_kmp_table[pattern_length - 1];
        left_bound = forward_kmp_table[pattern_length - 1];
        continue;

        found_some_difference:;

        size_t good_suffix_shift = (i + 1 < pattern_length) ? good_suffix_jump_table[i + 1] : 0;
        size_t bad_char_shift;
        panicing_table_at(bad_char_jump_table, src[offset + i] - LOWEST_CHAR_CODE, i, &bad_char_shift);

        size_t max_offset = max(good_suffix_shift, bad_char_shift);
        offset += max(max_offset, 1);
        left_bound = 0;
        // offset -= forward_kmp_table[i];
    }

    free(good_suffix_jump_table);
    free(forward_kmp_table);
    table_free(bad_char_jump_table);  
}


int main(int argc, char *argv[]) {
    // char *src = argv[2];
    // char *pattern = argv[1];
        
    // char *src     = "ndd9Md9PdPdPndd9ZTadnxddrddxds3ddrddsddddMLddd9ddrddr6dyddr"; 
    // char *pattern = "ddrdd";
    char *src = "aaaaaaaaaaaaa";
                //  abcba
                    // abcba
    char *pattern = "aaaaa";

    int *a = malloc(123);

    boyer_moore_str_search(src, strlen(src), pattern, strlen(pattern));
    return 0;
}