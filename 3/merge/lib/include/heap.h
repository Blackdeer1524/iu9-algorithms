#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>
#include <stdbool.h>

#if UNIT_TEST
    #define unit_static 
#else
    #define unit_static static
#endif


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

HeapItem get_max(Heap *heap);


#endif