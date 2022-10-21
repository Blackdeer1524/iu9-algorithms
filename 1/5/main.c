#include <stdio.h>
#include <assert.h>

#define TABLE_SIZE 8

typedef struct set_item set_item;

struct set_item {
    int value;
    int count;
};

set_item int_counter[TABLE_SIZE] = {};

int set_hash(int value) {
    return value % TABLE_SIZE;
}

void insert(set_item counter[], int item) {
    int item_hash = set_hash(item);
    while (counter[item_hash].value != item && counter[item_hash].count) {
        item_hash = (item_hash + 1) % TABLE_SIZE;
    }

    if (!counter[item_hash].count) {
        counter[item_hash].value = item;
    }
    ++counter[item_hash].count;
}


set_item *get(set_item counter[], int item) {
    int start_item_hash;
    int item_hash = start_item_hash = set_hash(item);
    while (counter[item_hash].value != item || !counter[item_hash].count) {
        item_hash = (item_hash + 1) % TABLE_SIZE;
        if (item_hash == start_item_hash) {
            return NULL;
        }
    }
    assert(counter[item_hash].value == item);
    return counter + item_hash;
}


int main() {
    int test_items[8] = {1, 2, 0, 0, 1, 1, 1, 3};
    int test_items_2[8] = {0, 0, 1, 1, 3, 1, 2, 1};

    for (int i = 0; i < 8; ++i) {
        insert(int_counter, test_items[i]);
    }

    for (int i = 0; i < 8; ++i) {
        printf("<c:%d, v:%d> ",
               int_counter[i].count,
               int_counter[i].value);
    }
    printf("\n");

    for (int i = 0; i < 8; ++i) {
        set_item *res = get(int_counter, test_items[i]);
        assert(res != NULL);
        assert(res->value == test_items[i]);
        printf("<c:%d, v:%d> ",
               res->count,
               res->value);
    }
    printf("\n");

    for (int i = 0; i < 8; ++i) {
        set_item *res = get(int_counter, test_items_2[i]);
        if (res == NULL || res->count == 0) {
            printf("%d wasn't found\n", test_items_2[i]);
        }
        --res->count;
    }
}