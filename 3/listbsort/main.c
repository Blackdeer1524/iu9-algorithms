#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


typedef struct Elem {
    struct Elem *next;
    char *word;
} Elem;



Elem *insert(Elem *head, char *word) {
    Elem *new_head = malloc(sizeof(Elem));
    new_head->next = NULL;
    new_head->word = word;
    if (head != NULL) { 
        new_head->next = head;
    }
    return new_head;
}


void print_list(Elem *head) {
    if (head == NULL) {
        return;
    }

    do {
        printf("%s ", head->word);
        head = head->next;
    } while (head != NULL);
}


void free_list(Elem *head) {
    if (head == NULL) {
        return;
    }

    do {
        Elem *next = head->next;
        free(head);
        head = next;
    } while (head != NULL);
}


void bubble_sort(Elem *head) {
    bool swapped_items;
    do {
        Elem *current = head;
        swapped_items = false;
        while (current->next != NULL) {
            if (strlen(current->word) > strlen(current->next->word)) {
                char *placeholder = current->word;
                current->word = current->next->word;
                current->next->word = placeholder;
                swapped_items = true;
            }   
            current = current->next;
        }
    } while (swapped_items);
}


int main() {
    char *line = NULL;
    size_t allocated_len = 0;
    signed long len = 0;
    if ((len = getline(&line, &allocated_len, stdin)) == -1) {
        free(line);
        return EXIT_FAILURE;
    }
    line[--len] = '\0';

    Elem *head = NULL;
    char *start = line;
    while (true) {
        for (; *start != '\0' && isblank(*start); ++start) {}
        if (*start == '\0') {
            break;
        }
        Elem *new_head = insert(head, start);  // <--------------------------------                                                             
        if (new_head == NULL) {                                                //  |                        
            free_list(head);                                                   //  |                    
            free(line);                                                        //  |               
            return EXIT_FAILURE;                                               //  |                        
        }                                                                      //  | 
        head = new_head;                                                       //  |                
        for (; *start != '\0' && !isblank(*start); ++start) {}                 //  |                                                      
        if (*start == '\0') {                                                  //  |                      
            break;                                                             //  |           
        }                                                                      //  |           
        *start = '\0';  // Ставим нолик т.к. он нужен для вычисления длины слова списка
        ++start;
    }

    bubble_sort(head);
    print_list(head);
    free_list(head);
    free(line);
    return EXIT_SUCCESS;
}
