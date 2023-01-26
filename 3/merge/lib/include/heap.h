#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int item;               
    size_t source_index;   // Индекс k-ого массива из которого брали элемент
} HeapItem;

typedef struct {
    HeapItem *data;
    size_t capacity;
    size_t length;
} Heap;


Heap build_heap(size_t capacity, bool *error); 

HeapItem get_minimum(Heap *heap, bool *error);

HeapItem pop_minimum(Heap *heap, bool *error);

bool insert(Heap *heap, HeapItem item);


#if UNIT_TEST
    #define parent(i) (((i) - 1) >> 1)
    #define left(i) (((i) << 1) + 1)
    #define right(i) (((i) + 1) << 1)
#else
#endif


#endif