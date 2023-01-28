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