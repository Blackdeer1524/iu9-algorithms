#include <limits.h>
#include "heap.h"

#define parent(i) (((i) - 1) >> 1)
#define left(i) (((i) << 1) + 1)
#define right(i) (((i) + 1) << 1)

Heap build_heap(size_t capacity, bool *error) {
    Heap heap = {
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


static void heapify(Heap *heap, size_t parent_index) {
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

bool insert(Heap *heap, HeapItem item) { 
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


HeapItem get_minimum(Heap *heap, bool *error) { 
    HeapItem res = {};
    if (heap == NULL || heap->length == 0) {
        *error = true;
        return res;
    }
    *error = false;    
    return heap->data[0];
}


HeapItem pop_minimum(Heap *heap, bool *error) {
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