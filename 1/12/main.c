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
    if (nel == 1) {
        return 1;
    }
    unsigned long peak_count = 0;

    if (less(0, 1) + less(1, 0) == 0 || less(0, 1) == 0) {
        ++peak_count;
    }

    if (less(nel - 2, nel - 1) + less(nel - 1, nel - 2) == 0 || less(nel - 2, nel - 1) == 0) {
        ++peak_count;
    }

    for (unsigned long i = 1; i < nel - 1; ++i) {
        int lm_cmp = less(i - 1, i);
        int ml_cmp = less(i, i - 1);
        int rm_cmp = less(i + 1, i);
        int mr_cmp = less(i, i + 1);

        // 1 ------ 1 \
        //              ------
        //                     \ 0
        int flat_left_peak = lm_cmp + ml_cmp == 0 && rm_cmp == 1;
        //                / 1 ------ 1
        //         ------
        //     O /
        int flat_right_peak = lm_cmp == 1 && rm_cmp + mr_cmp == 0;
        // 1 ------ 1 ------ 1
        int flat_peak = lm_cmp + ml_cmp + rm_cmp + mr_cmp == 0;

        if (flat_left_peak || flat_right_peak || flat_peak) {
            ++peak_count;
        }
    }
    return peak_count;
}


int main() {
    printf("%ld", peak(SIZE, int_less));
}
