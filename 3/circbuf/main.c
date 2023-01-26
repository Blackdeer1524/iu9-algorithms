#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>


typedef struct {
    int *data; 
    size_t capacity;
    size_t length;
    size_t read_index;
    size_t write_index;
} Queue;


#define INIT_QUEUE_SIZE 4

Queue InitQueue() {
    Queue queue = {
        .data=malloc(INIT_QUEUE_SIZE * sizeof(int)),
        .capacity=INIT_QUEUE_SIZE,
        .length=0,
        .read_index=0,
        .write_index=0
    };
    return queue;
}


bool QueueEmpty(Queue *queue) {
    return !queue->length;
}


void Enqueue(Queue *queue, int item) {
    queue->data[queue->write_index] = item;
    queue->write_index = (queue->write_index + 1) % queue->capacity;
    ++queue->length;

    if (queue->write_index == queue->read_index) {
        int *new_location = malloc((queue->capacity << 1) * sizeof(int));

        size_t n_items_from_read_ptr_to_the_array_end = queue->capacity - queue->read_index;
        memcpy(new_location, 
               queue->data + queue->read_index, 
               sizeof(int) * n_items_from_read_ptr_to_the_array_end);

        size_t n_items_before_read_ptr = queue->read_index;
        memcpy(new_location + n_items_from_read_ptr_to_the_array_end, 
               queue->data, 
               sizeof(int) * (n_items_before_read_ptr));
        
        free(queue->data); 
        queue->data = new_location;
        queue->read_index = 0;
        queue->write_index = queue->length;
        queue->capacity <<= 1;
    }
}


int Dequeue(Queue *queue) {
    int value = queue->data[queue->read_index];
    queue->read_index = (queue->read_index + 1) % queue->capacity;
    --queue->length;
    return value;
}


int main() {
    char buffer[16] = {};
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
        } else if (!strncmp(buffer, "EMPTY", 5)) {
            bool is_empty = QueueEmpty(&queue);
            if (is_empty) {
                puts("true");
            } else {
                puts("false");
            }
        }
    } while (strncmp(buffer, "END", 3));

    free(queue.data);
    return EXIT_SUCCESS;
}