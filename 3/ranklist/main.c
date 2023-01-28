#include <stdlib.h>
#include <stdio.h>
#include "skip_list.h"

void print_list(SkipList *list) {
    Node *start = list->head;
    do {
        printf("[%2zu] %11d | ", start->level, start->key);
        for (size_t i = 0; i < start->level; ++i) {
            if (start->ptrs_with_distance[i].next == NULL) {
                printf("(NULL, %zu) ", start->ptrs_with_distance[i].distance);
            } else {
                printf("(%d, %zu) ", start->ptrs_with_distance[i].next->key, start->ptrs_with_distance[i].distance);
            }
        }
        start = start->ptrs_with_distance[0].next;
        putchar('\n');
    } while (start != NULL);  
}

#include <assert.h>
#include <string.h>

int main() {
    // SkipList *a = build_skip_list(2);
    SkipList *a = build_skip_list(32);
    srand(42);
    
    for (size_t i = 0; i <= 10; i += rand() % 10) {
        printf("%zu\n", i);
        assert(!insert(a, i, "123"));
        // char *b;

        // assert(!lookup(a, i, &b));
        // assert(!strncmp(b, "123", 3));
        // assert(!delete(a, i));
        // assert(!lookup(a, i, &b));
        // assert(!lookup(a, i, &b));
        // assert(b == NULL);
    }


    // insert(a, 3, "123");
    // insert(a, -1, "123");
    // insert(a, 0, "123");
    // insert(a, 1, "123");
    // insert(a, 2, "123");
    // insert(a, 4, "123");
    // insert(a, 10, "123");
    // insert(a, 4, "123");


    print_list(a);
    free_skip_list(a);
    return EXIT_SUCCESS;
}
