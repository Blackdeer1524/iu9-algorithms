// ====./lib/include/heap.h==========

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

// ====./lib/src/heap.h==========

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

// ====main.c====================

#include <stdio.h>


typedef struct SchedulingInfo {
    size_t start;
    size_t end;
} SchedulingInfo;


#define min(x, y) (((x) < (y)) ? (x) : (y))


int main() {
    size_t clusters_count, tasks_count;
    if (scanf("%zu %zu", &clusters_count, &tasks_count) != 2) {
        puts("couldn't read task count and cluster count");
        return EXIT_FAILURE;
    }
    SchedulingInfo *tasks_scheduling_info = malloc(tasks_count * sizeof(SchedulingInfo));
    if (tasks_scheduling_info == NULL) { 
        puts("couldn't allocate space for tasks_scheduling_info");
        return EXIT_FAILURE;
    }    

    for (size_t i = 0; i < tasks_count; ++i) {
        // Уже отсортированны
        if (scanf("%zu %zu", &tasks_scheduling_info[i].start, &tasks_scheduling_info[i].end) != 2) {
            puts("couldn't read task scheduling info");
            free(tasks_scheduling_info);
            return EXIT_FAILURE;
        }
        tasks_scheduling_info[i].end += tasks_scheduling_info[i].start;
    }

    if (tasks_count <= clusters_count) {
        size_t min_time = -1;
        for (size_t i = 0; i < tasks_count; ++i) {
            min_time = min(min_time, tasks_scheduling_info[i].end);
        }
        printf("%zu", min_time);
        return EXIT_SUCCESS;
    }

    bool error = false;
    MinHeap completion_queue = build_heap(clusters_count, &error);
    if (error) {
        puts("couldn't allocate min heap");
        free_heap(&completion_queue);
        free(tasks_scheduling_info);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < clusters_count; ++i) {
        HeapItem item = {.item=tasks_scheduling_info[i].end};
        if (insert(&completion_queue, item)) {
            puts("[1]: couldn't insert item into heap");
            free_heap(&completion_queue);
            free(tasks_scheduling_info);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = clusters_count; i < tasks_count; ++i) {
        size_t prev_task_completion_time = pop_minimum(&completion_queue, &error).item;
        if (error) { 
            puts("[1] couldn't get minimum from a heap");
            free_heap(&completion_queue);
            free(tasks_scheduling_info);
            return EXIT_FAILURE;
        }
        size_t delay = 0;
        if (prev_task_completion_time > tasks_scheduling_info[i].start) {
            delay = prev_task_completion_time - tasks_scheduling_info[i].start;
        }
        HeapItem pending_task = {.item=tasks_scheduling_info[i].end + delay}; 
        if (insert(&completion_queue, pending_task)) {
            puts("[2]: couldn't insert item into heap");
            free_heap(&completion_queue);
            free(tasks_scheduling_info);
            return EXIT_FAILURE;
        }
    }

    size_t min_time = -1;
    for (size_t i = 0; i < clusters_count; ++i) {
        size_t prev_task_completion_time = pop_minimum(&completion_queue, &error).item;
        if (error) { 
            puts("[2] couldn't get minimum from a heap");
            free_heap(&completion_queue);
            free(tasks_scheduling_info);
            return EXIT_FAILURE;
        }
        min_time = min(min_time, prev_task_completion_time);
    }
    printf("%zu\n", min_time);
    free_heap(&completion_queue);
    free(tasks_scheduling_info);
    return EXIT_SUCCESS;
}
