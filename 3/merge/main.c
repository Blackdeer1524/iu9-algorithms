#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "heap.h"



void free_table(int **talbe, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        free(talbe[i]);
    }
    free(talbe);
}


int main() {
    size_t k;
    if (!scanf("%zu", &k)) {
        return EXIT_FAILURE;
    }
    
    size_t *sizes = malloc(sizeof(size_t) * k);
    if (sizes == NULL) {
        return EXIT_FAILURE;
    }

    int **table = malloc(sizeof(int *) * k);
    if (table == NULL) {
        free(sizes);
        return EXIT_FAILURE;
    }

    size_t result_array_length = 0;
    for (size_t i = 0; i < k; ++i) { 
        if (!scanf("%zu", sizes + i) || !sizes[i]) {
            free(sizes);
            free_table(table, i);
            return EXIT_FAILURE;
        }
        result_array_length += sizes[i];
        table[i] = malloc(sizeof(int) * sizes[i]);
        if (table[i] == NULL) {
            free(sizes);
            free_table(table, i);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0; j < sizes[i]; ++j) {
            if (!scanf("%d", &table[i][j])) {
                free(sizes);
                free_table(table, k);
                return EXIT_FAILURE;
            }
        }
    }
    
    bool error = false;
    MinHeap min_heap = build_heap(k, &error);
    if (error) {
        free_heap(&min_heap);
        free(sizes);
        free_table(table, k);
        return EXIT_FAILURE;
    }

    size_t *indecies_of_insertable_items_per_array = calloc(k, sizeof(size_t));
    for (size_t i = 0; i < k; ++i) {
        HeapItem val = {.item=table[i][0], .source_index=i};
        ++indecies_of_insertable_items_per_array[i];
        if (insert(&min_heap, val)) {
            free_heap(&min_heap);
            free(indecies_of_insertable_items_per_array);
            free(sizes);
            free_table(table, k);
            return EXIT_FAILURE;
        }
    }

    int *result = malloc(sizeof(int) * result_array_length);
    for (size_t i = 0; i < result_array_length; ++i) { 
        HeapItem cur_min = pop_minimum(&min_heap, &error);
        if (error) {
            break;
        }
        if (indecies_of_insertable_items_per_array[cur_min.source_index] < sizes[cur_min.source_index]) {
            HeapItem item = {
                .item=table[cur_min.source_index][indecies_of_insertable_items_per_array[cur_min.source_index]++],
                .source_index=cur_min.source_index};
            if (insert(&min_heap, item)) {
                break;
            }
        }
        result[i] = cur_min.item;
    }
    int status = EXIT_SUCCESS;
    if (error) {
        status = EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_array_length; ++i) {
        if (printf("%d ", result[i]) < 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free_heap(&min_heap);
    free(indecies_of_insertable_items_per_array);
    free(result);
    free(sizes);
    free_table(table, k);
    return status;
}