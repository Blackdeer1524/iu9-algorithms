#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>


size_t partition(int64_t *base, size_t l, size_t r) {
    size_t pivot_index = r;

    size_t i = l;
    for (size_t j = i; j < r; ++j)  {
        if (base[j] <= base[pivot_index]) {
            int64_t placeholder = base[i];
            base[i] = base[j];
            base[j] = placeholder;
            ++i;
        }
    }
    int64_t placeholder = base[i];
    base[i] = base[r];
    base[r] = placeholder;
    return i;
}

size_t random_partition(int64_t *base, size_t l, size_t r) {
    size_t subarray_length = r - l + 1;
    size_t pivot_index = l + (rand() % subarray_length);
    int64_t placeholder = base[pivot_index];
    base[pivot_index] = base[r];
    base[r] = placeholder;
    return partition(base, l, r);
}


typedef struct {
    int low, high;
} Task;


typedef struct Stack {
    Task pending_task;
    struct Stack *next;
} Stack;


Stack *stack_push(Stack *stack, int low, int high) {
    Task new_task = {
        .low=low,
        .high=high
    };
    Stack *stack_node = malloc(sizeof(Stack));
    stack_node->pending_task = new_task;
    stack_node->next = stack;
    return stack_node;
}


Stack *stack_pop(Stack *stack, Task *dst) {
    *dst = stack->pending_task;
    return stack->next;
}


void quick_sort(int64_t *base, size_t l, size_t r) {
    if (r <= l) {
        return;
    }

    // самый первый итем стака - заглушка
    Stack *tasks_stack = malloc(sizeof(Stack));
    tasks_stack->next = NULL;
    tasks_stack = stack_push(tasks_stack, l, r);
    while (tasks_stack->next != NULL) {
        Task current_task; 
        Stack *next = stack_pop(tasks_stack, &current_task);
        free(tasks_stack);
        tasks_stack = next;

        size_t q = random_partition(base, current_task.low, current_task.high);
        if (q && (size_t) current_task.low <= q - 1) {
            tasks_stack = stack_push(tasks_stack, current_task.low, q - 1);
        } 
        if (q + 1 <= (size_t) current_task.high) {
            tasks_stack = stack_push(tasks_stack, q + 1, current_task.high);
        }
    }
    free(tasks_stack);
}


int64_t test_sort(int64_t *base, size_t length) {
    if (!length || base == NULL) {
        return 0;
    }

    for (size_t i = 1; i < length; ++i) {
        if (base[i - 1] > base[i]) {
            return 1;
        }
    }
    return 0;
}


int main() {
    size_t n;
    scanf("%zu", &n);

    int64_t *arr = malloc(sizeof(int64_t) * n);
    for (size_t i = 0; i < n; ++i) {
        scanf("%ld", arr + i);
    }

    quick_sort(arr, 0, n - 1);

    for (size_t i = 0; i < n; ++i) {
        printf("%ld ", arr[i]);
    }

    free(arr);
    return 0;
}

