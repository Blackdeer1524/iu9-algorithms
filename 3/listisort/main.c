#include <stdio.h>
#include <stdlib.h>


typedef struct Elem {
    struct Elem *prev, *next;
    int v;
} Elem;


Elem *insert_after(Elem *current, int item) {
    Elem *next = malloc(sizeof(Elem));
    if (next == NULL) {
        return NULL;
    }
    next->v = item;
    if (current == NULL) { 
        next->next = next;
        next->prev = next;
        return next;    
    }

    next->next = current->next;
    next->prev = current;
    current->next = next;
    next->next->prev = next;
    return next;
}   


void insertion_sort(Elem *start) {
    for (Elem *pivot = start->next; pivot != start; pivot = pivot->next) {
        int temp = pivot->v;
        Elem *current = pivot;
        for (;current != start && current->prev->v > temp; current = current->prev) {
            current->v = current->prev->v;
        }
        current->v = temp;
    }
}


void free_list(Elem *start) {
    if (start == NULL) { 
        return;
    }
    Elem *head = start;
    do {
        Elem *next = head->next;
        free(head);
        head = next;
    } while (head != start);
}


void print_list(Elem *start) { 
    if (start == NULL) {
        return;
    }
    Elem *head = start;
    do {
        printf("%d ", head->v);
        head = head->next;
    } while (head != start);
}


int main() {
    size_t n;
    if (scanf("%zu", &n) != 1) { 
        return EXIT_FAILURE;
    }
    if (!n) {
        return EXIT_SUCCESS;
    }


    Elem *head = NULL;
    for (size_t i = 0; i < n; ++i) {
        int item;
        if (scanf("%d", &item) != 1) {
            return EXIT_FAILURE;
        }
        Elem *next = insert_after(head, item);
        if (next == NULL) {
            free_list(head);
            return EXIT_FAILURE;
        }
        head = next;
    }
    head = head->next;
    insertion_sort(head);
    print_list(head);
    free_list(head);
    return EXIT_SUCCESS;
}