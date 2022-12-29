#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

size_t get_max_overlap(char *left, size_t left_len, char *right, size_t right_len) {
    size_t left_offset = 0;
    if (left_len > right_len) {
        left_offset = left_len - right_len;
    }

    for (size_t i = left_offset; i < left_len; ++i) {
        if (!strncmp(left + i, right, left_len - i)) {
            return left_len - i;
        }
    }

    return 0;
}


typedef struct {
    size_t *data;
    size_t n_rows;
    size_t n_cols;
} Table;

void table_new(Table **uninit_table_ptr, size_t n_rows, size_t n_cols) {
    assert(uninit_table_ptr != NULL);

    Table *table_struct = (Table *) malloc(sizeof(Table));

    table_struct->data   = (size_t *) calloc(sizeof(size_t), n_rows * n_cols); 
    table_struct->n_rows = n_rows;
    table_struct->n_cols = n_cols;
    *uninit_table_ptr = table_struct;
}


void free_table(Table *table) {
    free(table->data);
    free(table);
}


void table_set(Table *table, size_t data, size_t row, size_t col) {
    assert(row < table->n_rows && col < table->n_cols);

    table->data[row * table->n_cols + col] = data;
}


size_t table_get(Table *table, size_t row, size_t col) {
    assert(row < table->n_rows && col < table->n_cols);

    return table->data[row * table->n_cols + col];
}


void print_table(Table *table) { 
    for (size_t i = 0; i < table->n_rows; ++i) {
        for (size_t j = 0; j < table->n_cols; ++j) {
            printf("%zu ", table_get(table, i, j));
        }
        puts("\n");
    }
}


size_t shortest_superstring_length(char **collection, size_t N) {
    Table *overlap;
    
    table_new(&overlap, N, N);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (i != j) {
                table_set(overlap, 
                          get_max_overlap(collection[i], strlen(collection[i]), 
                                          collection[j], strlen(collection[j])), i, j);
            }
        }
    }

    print_table(overlap);

    Table *dp;
    table_new(&dp, 1 << N, N);

    for (size_t mask = 1; mask < 1 << N; ++mask) {
        if (!(mask & (mask - 1))) {
            continue;
        }
        
        for (size_t chosen_index = 0; chosen_index < N; ++chosen_index) {
            if (!((mask >> chosen_index) & 1)) {
                continue;
            }

            size_t prev_mask = mask ^ (1 << chosen_index);
            for (size_t potential_prev_choice = 0; potential_prev_choice < N; ++potential_prev_choice) {
                if (!((prev_mask >> potential_prev_choice) & 1)) {
                    continue;
                }

                size_t total_overlap = table_get(overlap, potential_prev_choice, chosen_index) + 
                                       table_get(dp, prev_mask, potential_prev_choice);
                if (total_overlap > table_get(dp, mask, chosen_index)) {
                    table_set(dp, total_overlap, mask, chosen_index);
                }
            }
        }
    }

    size_t max_overlap = 0;
    size_t total_len = 0;
    size_t all_chosen_mask = (1 << N) - 1;
    for (size_t i = 0; i < N; ++i) {
        max_overlap = max(max_overlap, table_get(dp, all_chosen_mask, i));
        total_len += strlen(collection[i]);
    }
    puts("=============");
    print_table(dp);

    free_table(overlap);
    free(dp);
    return total_len - max_overlap;
}


#define generate_test(left_literal, right_literal, expected_res) { \
    size_t overlap = get_max_overlap(left_literal, strlen(left_literal), \
                                     right_literal, strlen(right_literal)); \
    if (overlap != expected_res) { \
        printf("Expected "#expected_res" but got %zu: "#left_literal"|"#right_literal, overlap); \
        exit(1); \
    } \
}

void test_get_max_overlap() {
    generate_test("1231241312tyurikjnd", "123123123", 0)
    generate_test("1231241312tyurikjnd", "123123123vefvfwedew123123", 0)

    generate_test("123123123", "1231241312tyurikjnd", 3)
    generate_test("123123123", "123123123vefvfwedew123123", 9)

    generate_test("123123123vefvfwedew123123", "1231241312tyurikjnd", 3)
    generate_test("123123123vefvfwedew123123", "123123123", 6)

    generate_test("123", "223", 0)
    generate_test("123123", "123123123", 6)
    generate_test("", "123123123", 0)
}


int main() {
    // test_get_max_overlap();

    char *test[] = {
        "1231241312tyurikjnd",
        "123123123",
        "123123123vefvfwedew123123",
    };

    printf("%zu\n", shortest_superstring_length(test, sizeof(test) / sizeof(test[0])));
    return 0;
}