#include <stdio.h>
#include <assert.h>

#define TABLE_SIZE 8

typedef struct set_item set_item;

struct set_item {
    int value;
    int count;
};

set_item set[TABLE_SIZE] = {};

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
    int test_items[8] = {5, 8, 0, 0, 3, 2, 1, 10};

    for (int i = 0; i < 8; ++i) {
        insert(set, test_items[i]);
    }

    for (int i = 0; i < 8; ++i) {
        printf("<c:%d, v:%d> ", set[i].count, set[i].value);
    }
    printf("\n");

    for (int i = 0; i < 8; ++i) {
        set_item *res = get(set, test_items[i]);
        assert(res != NULL);
        assert(res->value == test_items[i]);
        printf("<c:%d, v:%d> ", res->count, res->value);
    }

}