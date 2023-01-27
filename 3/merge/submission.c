// =====./lib/include/heap.h==========

#include <stdlib.h>
#include <stdbool.h>

typedef struct HeapItem {
    int item;               
    size_t source_index;   // Индекс k-ого массива из которого брали элемент
} HeapItem;

typedef struct MinHeap {
    HeapItem *data;
    size_t capacity;
    size_t length;
} MinHeap;


MinHeap build_heap(size_t capacity, bool *error); 

bool insert(MinHeap *heap, HeapItem item);

HeapItem get_minimum(MinHeap *heap, bool *error);

HeapItem pop_minimum(MinHeap *heap, bool *error);

void free_heap(MinHeap *heap);

// =====./lib/src/heap.c==========

#include <limits.h>

#define parent(i) (((i) - 1) >> 1)
#define left(i) (((i) << 1) + 1)
#define right(i) (((i) + 1) << 1)


MinHeap build_heap(size_t capacity, bool *error) {
    MinHeap heap = {
        .data = malloc(sizeof(HeapItem) * capacity),
        .capacity=capacity,
        .length=0
    };
    if (heap.data == NULL) {
        *error = true;
    } else {
        *error = false;
    }
    return heap;
}


static void heapify(MinHeap *heap, size_t parent_index) {
    int parent_value = heap->data[parent_index].item;

    size_t swap_index = parent_index;
    size_t l_index = left(parent_index);
    size_t r_index = right(parent_index);
    if (l_index < heap->length && parent_value > heap->data[l_index].item) {
        parent_value = heap->data[l_index].item;
        swap_index = l_index;
    }
    if (r_index < heap->length && parent_value > heap->data[r_index].item) {
        swap_index = r_index;
    }
    if (swap_index != parent_index) {
        HeapItem placeholder = heap->data[parent_index];
        heap->data[parent_index] = heap->data[swap_index];
        heap->data[swap_index] = placeholder;
        heapify(heap, swap_index);
    }
} 


bool insert(MinHeap *heap, HeapItem item) { 
    if (heap == NULL || !heap->capacity || heap->length == heap->capacity) {
        return true;
    }

    if (!heap->length) {
        heap->data[0] = item;
        heap->length = 1;
        return false;
    }
    
    heap->data[heap->length] = item;
    size_t i = heap->length++;
    do {
        i = parent(i);
        heapify(heap, i);
    } while (i > 0);

    return false;
}


HeapItem get_minimum(MinHeap *heap, bool *error) { 
    HeapItem res = {};
    if (heap == NULL || heap->length == 0) {
        *error = true;
        return res;
    }
    *error = false;    
    return heap->data[0];
}


HeapItem pop_minimum(MinHeap *heap, bool *error) {
    HeapItem res = {};
    if (heap == NULL || heap->length == 0) {
        *error = true;
        return res;
    }
    *error = false;    
    res = heap->data[0];
    heap->data[0] = heap->data[--heap->length];
    heapify(heap, 0);
    return res;
}


void free_heap(MinHeap *heap) {
    free(heap->data);
}


// ===main.c======================

#include <stdio.h>

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
