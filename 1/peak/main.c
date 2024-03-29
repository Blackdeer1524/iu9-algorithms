#include <stdio.h>
#define SIZE 3

int array[SIZE] = {1, 3, 1};

int int_less(unsigned long i, unsigned long j) {
    if (array[i] < array[j]) {
        return 1;
    } else {
        return 0;
    }
}

// Элемент последовательности чисел,
// значение которого — не меньше значений его непосредственных соседей,
// называется пиком
// a[i-1] <= a[i], a[i + 1] <= a[i]

unsigned long peak(unsigned long nel,
                   int (*less)(unsigned long i, unsigned long j)) {
    if (nel <= 1) {
        return nel;
    }

    if (!less(0, 1)) {
        return 0;
    }

    if (!less(nel - 1, nel - 2)) {
        return nel - 1;
    }

    for (unsigned long i = 1; i < nel - 1; ++i) {
        if (!less(i, i - 1) && !less(i, i + 1)) {
            return i;
        }
    }
    return 0;
}


int main() {
    printf("%ld", peak(SIZE, int_less));
}
