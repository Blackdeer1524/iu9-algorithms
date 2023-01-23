#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "elem.h"

typedef struct Elem Elem;

Elem  *searchlist(Elem *list, int k) {
    while (list != NULL) {
        if (list->tag == INTEGER && list->value.i == k) {
            break;
        }
        list = list->tail;
    }
    return list;
}


void append_int(Elem *head, int value) {
    assert(head != NULL);

    Elem *new_elem = malloc(sizeof(Elem));
    new_elem->tag = INTEGER;
    new_elem->value.i = value;
    new_elem->tail = NULL;

    while (head->tail != NULL) {
        head = head->tail;
    }

    head->tail = new_elem;
}


void append_float(Elem *head, float value) {
    assert(head != NULL);

    Elem *new_elem = malloc(sizeof(Elem));
    new_elem->tag = FLOAT;
    new_elem->value.f = value;
    new_elem->tail = NULL;

    while (head->tail != NULL) {
        head = head->tail;
    }

    head->tail = new_elem;
}


void append_list(Elem *head, Elem *value) {
    assert(head != NULL);

    Elem *new_elem = malloc(sizeof(Elem));
    new_elem->tag = LIST;
    new_elem->value.list = value;
    new_elem->tail = NULL;

    while (head->tail != NULL) {
        head = head->tail;
    }

    head->tail = new_elem;
}


void print_list(Elem *head) {
    printf("{");
    while (head != NULL) {
        switch (head->tag) {
            case INTEGER: {
                printf("%d ", head->value.i);
                break;
            }
            case FLOAT: {
                printf("%f ", head->value.f);
                break;
            }
            case LIST: {
                print_list(head->value.list);
                break;
            }
            default:
                exit(1);
                break;
        }
        head = head->tail;
    }
    printf("} ");
}


int main() {
    Elem main_head = {.tag = INTEGER, .value.i = 0, .tail = NULL};
    for (int i = 1; i < 10; ++i) {
        append_int(&main_head, i);
    }

    Elem inner_head = {.tag = FLOAT, .value.f = 0.f, .tail = NULL};
    for (int i = 1; i < 10; ++i) {
        append_float(&inner_head, (float) i);
    }
    append_list(&main_head, &inner_head);
    print_list(&main_head);
    printf("\n");

    Elem *search_results = searchlist(&main_head, 9);
    print_list(search_results);

    return 0;
}