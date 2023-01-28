#include <stdlib.h>
#include <stdio.h>
#include "skip_list.h"

void print_list(SkipList *list) {
    Node *start = list->head;
    do {
        printf("[%2zu] %11d | ", start->level, start->key);
        for (size_t i = 0; i < start->level && start->ptrs_with_distance[i].next != NULL; ++i) {
            printf("%4d ", start->ptrs_with_distance[i].next->key);
        }
        start = start->ptrs_with_distance[0].next;
        putchar('\n');
    } while (start != NULL);  
}

int main() {
    // SkipList *a = build_skip_list(2);
    SkipList *a = build_skip_list(5);
    srand(42);
    
    for (size_t i = 20; i > 0; i -= 4) {
        insert(a, i, "123");
    }

    for (size_t i = 2; i < 10; i += 4) {
        insert(a, i, "123");
    }


    // insert(a, 3, "123");
    // insert(a, -1, "123");
    // insert(a, 0, "123");
    // insert(a, 1, "123");
    // insert(a, 2, "123");
    // insert(a, 3, "123");
    // insert(a, 4, "123");
    // insert(a, 4, "123");


    print_list(a);
    return EXIT_SUCCESS;
}
