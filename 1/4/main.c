#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int add_item(uint32_t *dst, int item) {
    if (item > 31 || item < 0) {
        return 1;
    }
    *dst |= 1 << item;
    return 0;
}

uint32_t intersection(uint32_t l, uint32_t r) {
    return l & r;
}

void print_set(uint32_t set) {
    for (int i = 0; i < 31; ++i) {
        if (set & (1 << i)) {
            printf("%d ", i);
        }
    }
    if (set & (1 << 31)) {
        printf("%d ", 31);
    }
}


int main() {
    size_t A_size;
    scanf("%zu", &A_size);

    uint32_t set_1 = 0;
    for (size_t i = 0; i < A_size; ++i) {
        int item;
        scanf("%d", &item);
        add_item(&set_1, item);
    }

    size_t B_size;
    scanf("%zu", &B_size);

    uint32_t set_2 = 0;
    for (size_t i = 0; i < B_size; ++i) {
        int item;
        scanf("%d", &item);
        add_item(&set_2, item);
    }

    uint32_t set_intersection = intersection(set_1, set_2);
    print_set(set_intersection);
}