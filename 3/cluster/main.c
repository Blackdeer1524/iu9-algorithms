#include <stdio.h>
#include "heap.h"


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
        size_t min_time = 0;
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
