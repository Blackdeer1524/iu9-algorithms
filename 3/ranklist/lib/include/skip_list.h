#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

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

#endif