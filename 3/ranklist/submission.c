#define  _GNU_SOURCE
#include <stdio.h>

// ========./lib/include/skiplist.h=========
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>

typedef struct LinkedList LinkedList;

struct LinkedList {
    char *value;
    LinkedList *next;    
};

LinkedList *add_node(LinkedList *prev, char *value);

void free_linked_list(LinkedList *head);

#endif

// ========./lib/src/skiplist.c=========

// #include "linked_list.h"

LinkedList *add_node(LinkedList *prev, char *value) {
    LinkedList *head = (LinkedList *) malloc(sizeof(LinkedList));
    if (head == NULL) { 
        return NULL;
    }
    head->next = prev;    
    head->value = value;
    return head; 
}


void free_linked_list(LinkedList *head) {
    while (head != NULL) {
        LinkedList *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

// ========./lib/include/skiplist.h=========

#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <stdlib.h>
#include <stdbool.h>
// #include "linked_list.h"

typedef struct Node Node;

typedef struct Pair {
    Node *next;
    size_t distance;
} Pair;


struct Node {
    int key;
    LinkedList *values_list;   // Может быть NULL только в заголовке
    size_t level;
    Pair *ptrs_with_distance;   
};

typedef struct SkipList {
    size_t max_level;
    Node *head;
} SkipList;


SkipList *build_skip_list(size_t max_level);

bool lookup(SkipList *list, int key, char **res);

bool insert(SkipList *list, int key, char *word);

bool delete(SkipList *list, int key);

void free_skip_list(SkipList *list);

bool rank(SkipList *list, int key, size_t *res);

#endif
// ========./lib/src/skiplist.c=========
#include <limits.h>
// #include "skip_list.h"


SkipList *build_skip_list(size_t max_level) { 
    SkipList *skip_list;
    if (!max_level || (skip_list = malloc(sizeof(SkipList))) == NULL) {
        return NULL;
    }

    skip_list->head = malloc(sizeof(Node)); 
    if (skip_list->head == NULL) {
        free(skip_list);
        return NULL;
    }
    skip_list->max_level = max_level;
    skip_list->head->key = INT_MIN;
    skip_list->head->level = max_level;
    skip_list->head->values_list = NULL;
    skip_list->head->ptrs_with_distance = (Pair *) malloc(max_level * sizeof(Pair));
    if (skip_list->head->ptrs_with_distance == NULL) {
        free(skip_list->head);
        free(skip_list);
        return NULL;
    }
    for (size_t i = 0; i < max_level; ++i) {
        skip_list->head->ptrs_with_distance[i].distance = 1;
        skip_list->head->ptrs_with_distance[i].next = NULL;
    }
    return skip_list;
}


void free_skip_list(SkipList *list) {
    if (list == NULL) {
        return;
    }
    Node *head = list->head;
    do {
        Node *next = head->ptrs_with_distance[0].next;
        free_linked_list(head->values_list);
        free(head->ptrs_with_distance);
        free(head);
        head = next;
    } while (head != NULL);
    free(list);
}


static int generate_level(size_t max_level) {
    size_t new_level = 1;
    for (size_t c = 1; c < max_level && !(rand() % 2); ++c) {
        ++new_level;
    }
    return new_level;
}


#define min(x, y) (((x) < (y)) ? (x) : (y))


bool lookup(SkipList *list, int key, char **res) {
    if (list == NULL) {
        *res = NULL; 
        return true;
    }

    Node *head = list->head;
    size_t cur_search_level = list->max_level - 1;
    while (cur_search_level > 0 && head->key != key) {
        if (head->ptrs_with_distance[cur_search_level].next == NULL 
            || head->ptrs_with_distance[cur_search_level].next->key > key) {
            --cur_search_level;
        } else {
            head = head->ptrs_with_distance[cur_search_level].next;
        }
    }

    if (!cur_search_level) {
        while (head->ptrs_with_distance[0].next != NULL && head->ptrs_with_distance[0].next->key <= key) {
            head = head->ptrs_with_distance[0].next;
        }
    }

    if (head->key == key) {
        *res = head->values_list->value; 
    } else {
        *res = NULL; 
    }
    return false;
}


bool rank(SkipList *list, int key, size_t *res) {
    if (list == NULL) {
        return true;
    }

    Node *head = list->head;
    size_t cur_search_level = list->max_level - 1;
    size_t sequence_number = 0;
    while (cur_search_level > 0 && head->key != key) {
        if (head->ptrs_with_distance[cur_search_level].next == NULL 
            || head->ptrs_with_distance[cur_search_level].next->key > key) {
            --cur_search_level;
        } else {
            sequence_number += head->ptrs_with_distance[cur_search_level].distance;
            head = head->ptrs_with_distance[cur_search_level].next;
        }
    }

    if (!cur_search_level) {
        while (head->ptrs_with_distance[0].next != NULL && head->ptrs_with_distance[0].next->key <= key) {
            sequence_number += head->ptrs_with_distance[0].distance;
            head = head->ptrs_with_distance[0].next;
        }
    }

    if (head->key != key) {
        *res = 0;
        return true;
    } 
    *res = sequence_number; 
    return false;
}


bool insert(SkipList *list, int key, char *word) {
    if (list == NULL || word == NULL) {
        return true;
    }
    Pair **update_list = (Pair **) malloc(list->max_level * sizeof(Pair *)); 
    if (update_list == NULL) {
        return true;
    }
    size_t *sequence_index_per_level = calloc(list->max_level, sizeof(size_t));
    if (sequence_index_per_level == NULL) {
        free(update_list); 
        return true; 
    }

    for (size_t i = 0; i < list->max_level; ++i) { 
        update_list[i] = &list->head->ptrs_with_distance[i];
    }    
    LinkedList **rightmost_node_value_list = NULL;

    int cur_key = list->head->key;
    size_t cur_search_level = list->max_level - 1;
    while (cur_search_level > 0 && cur_key != key) {
        if (update_list[cur_search_level]->next == NULL 
            || update_list[cur_search_level]->next->key > key) {
            sequence_index_per_level[cur_search_level - 1] = sequence_index_per_level[cur_search_level];
            --cur_search_level;
        } else {
            cur_key = update_list[cur_search_level]->next->key;
            sequence_index_per_level[cur_search_level] += update_list[cur_search_level]->distance;
            rightmost_node_value_list = &update_list[cur_search_level]->next->values_list;
            for (size_t i = 0; i <= cur_search_level; ++i) {
                update_list[i] = &update_list[cur_search_level]->next->ptrs_with_distance[i];  
            }
        }
    }

    if (!cur_search_level) {
        sequence_index_per_level[0] = sequence_index_per_level[1];
        while (update_list[0]->next != NULL && update_list[0]->next->key <= key) {
            cur_key = update_list[cur_search_level]->next->key;
            rightmost_node_value_list = &update_list[cur_search_level]->next->values_list;
            update_list[0] = &update_list[0]->next->ptrs_with_distance[0];
            ++sequence_index_per_level[0];
        }
    }

    if (cur_key == key) {
        if (rightmost_node_value_list == NULL) {
            free(sequence_index_per_level);
            free(update_list);
            return true;
        }
        LinkedList *placeholder = add_node(*rightmost_node_value_list, word);
        if (placeholder == NULL) {
            free(sequence_index_per_level);
            free(update_list);
            return true;            
        }
        *rightmost_node_value_list = placeholder;
        free(sequence_index_per_level);
        free(update_list);
        return false;
    }

    Node *new_node = malloc(sizeof(Node));
    new_node->key = key;
    size_t new_node_level = generate_level(list->max_level);
    new_node->level = new_node_level; 
    new_node->ptrs_with_distance = (Pair *) malloc(sizeof(Pair) * new_node_level);
    new_node->values_list = NULL;
    LinkedList *placeholder = add_node(new_node->values_list, word);
    if (placeholder == NULL) {
        free(new_node);
        free(sequence_index_per_level);
        free(update_list);
        return true;
    }
    new_node->values_list = placeholder;

    for (size_t i = new_node_level; i < list->max_level; ++i) {
        ++update_list[i]->distance;
    }
    
    for (size_t i = 0; i < new_node_level; ++i) {
        new_node->ptrs_with_distance[i].next = update_list[i]->next;
        new_node->ptrs_with_distance[i].distance = (sequence_index_per_level[i] + update_list[i]->distance) - (sequence_index_per_level[0] + 1) + 1;
        update_list[i]->next = new_node;
        update_list[i]->distance = (sequence_index_per_level[0] + 1) - sequence_index_per_level[i];
    }

    free(sequence_index_per_level);
    free(update_list);
    return false;
}


bool delete(SkipList *list, int key) {
    if (list == NULL) {
        return true;
    }
    Pair **update_list = (Pair **) malloc(list->max_level * sizeof(Pair *)); // list->head->ptrs_with_distance;
    if (update_list == NULL) {
        return true;
    }

    for (size_t i = 0; i < list->max_level; ++i) { 
        update_list[i] = &list->head->ptrs_with_distance[i];
    }    

    int cur_key = list->head->key;
    size_t cur_search_level = list->max_level - 1;
    while (cur_search_level > 0 && cur_key != key) {
        if (update_list[cur_search_level]->next == NULL 
            || update_list[cur_search_level]->next->key >= key) {
            --cur_search_level;
        } else {
            cur_key = update_list[cur_search_level]->next->key;
            for (size_t i = 0; i <= cur_search_level; ++i) {
                update_list[i] = &update_list[cur_search_level]->next->ptrs_with_distance[i];  
            }
        }
    }

    while (update_list[0]->next != NULL && update_list[0]->next->key < key) {
        update_list[0] = &update_list[0]->next->ptrs_with_distance[0];
    }

    Node *deleting_node = update_list[0]->next;
    if (deleting_node == NULL || deleting_node->key != key) {
        free(update_list);
        return true;
    }

    for (size_t i = deleting_node->level; i < list->max_level; ++i) {
        --update_list[i]->distance;
    }
    
    for (size_t i = 0; i < deleting_node->level; ++i) {
        update_list[i]->next = deleting_node->ptrs_with_distance[i].next;
        update_list[i]->distance += deleting_node->ptrs_with_distance[i].distance - 1;
    }

    free(deleting_node->ptrs_with_distance);
    free_linked_list(deleting_node->values_list);
    free(deleting_node);
    free(update_list);
    return false;
}

// ========./main.c=========================

#include <stdlib.h>
#include <string.h>
// #include "skip_list.h"


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
