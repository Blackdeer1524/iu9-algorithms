#include <stdint.h>
#include <stdio.h>


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
    uint32_t set_1 = 0;
    add_item(&set_1, 2);
    add_item(&set_1, 4);
    add_item(&set_1, 0);

    uint32_t set_2 = 0;
    add_item(&set_2, 0);
    add_item(&set_2, 1);
    add_item(&set_2, 3);

    print_set(set_1);
    printf("\n");
    uint32_t set_intersection = intersection(set_1, set_2);
    print_set(set_intersection);
}