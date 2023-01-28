#include <limits.h>
#include <memory.h>
#include "skip_list.h"


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
    skip_list->lenght = 0;
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


static int generate_level(size_t max_level) {
    size_t new_level = 1;
    for (size_t c = 1; c < max_level && !(rand() % 2); ++c) {
        ++new_level;
    }
    return new_level;
}

#if DEBUG
    #include <assert.h>
#else
    #define assert(expr)
#endif

#define min(x, y) (((x) < (y)) ? (x) : (y))

bool insert(SkipList *list, int key, char *word) {
    if (list == NULL || word == NULL) {
        return true;
    }
    Pair **update_list = (Pair **) malloc(list->max_level * sizeof(Pair *)); // list->head->ptrs_with_distance;
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
        *rightmost_node_value_list = add_node(*rightmost_node_value_list, word);
        free(sequence_index_per_level);
        free(update_list);
        return false;
    }

    Node *new_node = malloc(sizeof(Node));
    new_node->key = key;
    size_t new_node_level = generate_level(list->max_level);
    new_node->level = new_node_level; 
    new_node->ptrs_with_distance = (Pair *) malloc(sizeof(Pair) * new_node_level);
    
    for (size_t i = new_node_level; i < list->max_level; ++i) {
        ++update_list[i]->distance;
    }
    
    for (size_t i = 0; i < new_node_level; ++i) {
        new_node->ptrs_with_distance[i].next = update_list[i]->next;
        new_node->ptrs_with_distance[i].distance = (update_list[i]->distance + 1) - (sequence_index_per_level[0] + 1);
        update_list[i]->next = new_node;
        update_list[i]->distance = (sequence_index_per_level[0] + 1) - sequence_index_per_level[i];
    }

    free(sequence_index_per_level);
    free(update_list);
    return false;
}

