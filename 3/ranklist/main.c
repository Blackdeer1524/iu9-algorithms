#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skip_list.h"

void print_list(SkipList *list) {
    Node *start = list->head;
    do {
        printf("[%2zu] %11d->", start->level, start->key);
        if (start->values_list == NULL) {
            printf("%s", "NULL");
        } else {
            printf("\"%s\"", start->values_list->value);
        }
        printf("%s", " | ");
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


int main() {
    srand(42);
    SkipList *skip_list = build_skip_list(32);
    
    char buffer[8] = {};
    int status = EXIT_SUCCESS;
    do {
        if (scanf("%s", buffer) != 1) {
            status = EXIT_FAILURE;
            break;
        } 
        if (!strncmp(buffer, "INSERT", 6)) {
            int k;
            if (scanf("%d", &k) != 1) {
                status = EXIT_FAILURE;
                break;
            }
            char *v = NULL;
            size_t allocated_space_for_input = 0;
            signed long long actual_length;
            if ((actual_length = getline(&v, &allocated_space_for_input, stdin)) == -1) {
                status = EXIT_FAILURE;
                free(v);
                break;
            }
            v[actual_length - 1] = '\0';
            if (insert(skip_list, k, v)) {
                status = EXIT_FAILURE;
                free(v);
                break;
            }
        } else if (!strncmp(buffer, "DELETE", 6)) {
            int k;
            if (scanf("%d", &k) != 1) {
                status = EXIT_FAILURE;
                break;
            }
            if (delete(skip_list, k)) {
                status = EXIT_FAILURE;
                break;
            }
        } else if (!strncmp(buffer, "LOOKUP", 6)) {
            int k;
            if (scanf("%d", &k) != 1) {
                status = EXIT_FAILURE;
                break;
            }
            char *res;
            if (lookup(skip_list, k, &res)) {
                status = EXIT_FAILURE;
                break;
            }
            printf("%s\n", res);
        } else if (!strncmp(buffer, "RANK", 4)) {
            int k;
            if (scanf("%d", &k) != 1) {
                status = EXIT_FAILURE;
                break;
            }
            size_t res;
            if (rank(skip_list, k, &res)) {
                status = EXIT_FAILURE;
                break;
            }
            printf("%zu\n", res - 1);
        } else if (!strncmp(buffer, "PRINT", 5)) {
            print_list(skip_list);
        }
    } while (strncmp(buffer, "END", 3));

    free_skip_list(skip_list);
    return status;
}
