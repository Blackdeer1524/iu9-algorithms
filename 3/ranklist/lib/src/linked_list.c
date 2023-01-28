#include "linked_list.h"


LinkedList *add_node(LinkedList *prev, char *value) {
    LinkedList *head = (LinkedList *) malloc(sizeof(LinkedList));
    if (head == NULL) { 
        return head;
    }
    head->next = prev;    
    head->value = value;
    return head; 
}


void free_linked_list(LinkedList *head) {
    while (head != NULL) {
        LinkedList *next = head->next;
        free(head);
        head = next;
    }
}