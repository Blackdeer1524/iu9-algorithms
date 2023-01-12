#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>

#define parent(i) (((i) - 1) >> 1)
#define left(i) (((i) << 1) + 1)
#define right(i) ((((i) + 1) << 1))
#define get_item_ptr(void_base_ptr, width, i) (((char *) (void_base_ptr)) + (i) * (width))

void max_heapify(void *base,
                 size_t length,
                 size_t width,
                 size_t cur_index,
                 int (*compare)(const void *a, const void *b));

void build_max_heap(void *base,
                    size_t nel,
                    size_t width,
                    int (*compare)(const void *a, const void *b));

void hsort(void *base,
           size_t nel,
           size_t width,
           int (*compare)(const void *a, const void *b));

#endif