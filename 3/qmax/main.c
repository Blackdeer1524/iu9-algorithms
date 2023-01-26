#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>


typedef struct Stack Stack;

struct Stack {
    int item;
    Stack *next;
};


Stack *push(Stack *stack, int item) {
    Stack *next = malloc(sizeof(Stack));
    next->item = item;
    next->next = stack;
    return next;
}


Stack *pop(Stack *stack, int *res) {
    *res = stack->item;
    Stack *next = stack->next;
    free(stack); 
    return next;
}


bool is_empty(Stack *stack) {
    return stack->next == NULL;
}


void free_stack(Stack *stack) {
    while (stack->next != NULL) { 
        Stack *next = stack->next;
        free(stack);
        stack = next;
    }
    free(stack);
}



typedef struct {
    Stack *backward;     //  Куда добавляются элементы
    Stack *forward;      //  откуда берутся
    Stack *max_forward;  //  хранит максумумы
    int backward_max; 
} Queue;


Queue InitQueue() {
    Stack *backward    = malloc(sizeof(Stack));  // Первый элемент всегда пуст
    Stack *forward     = malloc(sizeof(Stack));
    Stack *max_forward = malloc(sizeof(Stack));
    
    backward->item = 0;
    backward->next = NULL;

    forward->item = 0;
    forward->next = NULL;

    max_forward->item = INT_MIN;
    max_forward->next = NULL;
    
    Queue queue = {
        .backward = backward,
        .forward = forward,
        .max_forward = max_forward,
        .backward_max = INT_MIN
    };

    return queue;
}


void FreeQueue(Queue *queue) {
    free_stack(queue->backward);
    free_stack(queue->forward);
    free_stack(queue->max_forward);
}


bool QueueEmpty(Queue *queue) {
    return is_empty(queue->backward) && is_empty(queue->forward);
}


#define max(x, y) ((x) > (y) ? (x) : (y))


void Enqueue(Queue *queue, int item) {
    queue->backward_max = max(item, queue->backward_max); 
    queue->backward = push(queue->backward, item);
}


int Maximum(Queue *queue) {
    return max(queue->backward_max, queue->max_forward->item); 
}


int Dequeue(Queue *queue) {
    if (is_empty(queue->forward)) {
        while (!is_empty(queue->backward)) {
            int popped_item;
            queue->backward  = pop(queue->backward, &popped_item);
            queue->forward = push(queue->forward, popped_item);
            queue->max_forward = push(queue->max_forward, max(queue->max_forward->item, popped_item));
        }
        queue->backward_max = INT_MIN;
    }
    int res, placeholder;
    queue->forward     = pop(queue->forward, &res);
    queue->max_forward = pop(queue->max_forward, &placeholder);
    return res;
}

int main() { 
    char buffer[6] = {};
    Queue queue = InitQueue(); 
    do {
        scanf("%s", buffer);
        if (!strncmp(buffer, "ENQ", 3)) {
            int item;
            scanf("%d", &item);
            Enqueue(&queue, item);
        } else if (!strncmp(buffer, "DEQ", 3)) {
            int item = Dequeue(&queue);
            printf("%d\n", item);
        } else if (!strncmp(buffer, "MAX", 3)) {
            int max_item = Maximum(&queue);
            printf("%d\n", max_item);
        } if (!strncmp(buffer, "EMPTY", 5)) {
            if (QueueEmpty(&queue)) {
                puts("true");
            } else {
                puts("false");   
            }
        } 
    } while (strncmp(buffer, "END", 3));

    FreeQueue(&queue);
    return EXIT_SUCCESS;
}