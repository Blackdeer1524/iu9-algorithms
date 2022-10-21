#include <stdlib.h>
#include <stdio.h>

int maxarray(void *base,
             size_t nel,
             size_t width,
             int (*compare)(void *a, void *b)) {
    if (nel == 0 || base == NULL) {
        return 0;
    }

    int max_item_index = 0;
    void *current_max_item = base;
    for (int i = 1; i < nel; ++i, base += width) {
        int cmp = compare(current_max_item, base);
        if (cmp < 0) {
            current_max_item = base;
            max_item_index = i;
        }
    }
    return max_item_index;
}


int int_cmp(int *l, int *r) {
    return *l - *r;
}


int main() {
    int test_collection[] = {1, 5, 6, 23, 3, 9, 19};
    size_t item_width = sizeof test_collection[0];
    size_t collection_length = sizeof test_collection / item_width;
    int max_item_index = maxarray(test_collection, collection_length, item_width, (int (*)(void *, void *)) int_cmp);
    printf("%d", max_item_index);
}