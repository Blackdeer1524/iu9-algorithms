#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct HeapItem {
    int item;               
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

#if UNIT_TEST
    #define parent(i) (((i) - 1) >> 1)
    #define left(i) (((i) << 1) + 1)
    #define right(i) (((i) + 1) << 1)
#else
#endif


#endif