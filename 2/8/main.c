#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>


void selection_sort(int *base, size_t length) {
    assert(base != NULL && length);

    for (size_t i = 0; i < length - 1; ++i) {
        int cur_min = base[i];
        size_t cur_min_index = i;
        for (size_t j = i + 1; j < length; ++j) {
            if (cur_min > base[j]) {
                cur_min = base[j];
                cur_min_index = j;
            }
        }
        if (cur_min_index != i) {
            int placeholder = base[i];
            base[i] = base[cur_min_index];
            base[cur_min_index] = placeholder;
        }
    }
}


size_t partition(int *base, size_t l, size_t r) {
    size_t pivot_index = r;

    size_t i = l;
    for (size_t j = i; j < r; ++j)  {
        if (base[j] <= base[pivot_index]) {
            int placeholder = base[i];
            base[i] = base[j];
            base[j] = placeholder;
            ++i;
        }
    }
    int placeholder = base[i];
    base[i] = base[r];
    base[r] = placeholder;
    return i;
}

size_t random_partition(int *base, size_t l, size_t r) {
    size_t subarray_length = r - l + 1;
    size_t pivot_index = l + (rand() % subarray_length);
    int placeholder = base[pivot_index];
    base[pivot_index] = base[r];
    base[r] = placeholder;
    return partition(base, l, r);
}


void quick_sort(int *base, size_t l, size_t r, size_t m) {
    if (r <= l) {
        return;
    }

    size_t subarray_length = r - l + 1;
    if (subarray_length < m) {
        selection_sort(base + l, subarray_length);
        return;
    }

    size_t q = random_partition(base, l, r);
    if (q) {
        quick_sort(base, l, q - 1, m);
    }

    quick_sort(base, q + 1, r, m);
}



int test_sort(int *base, size_t length) {
    if (!length || base == NULL) {
        return 0;
    }

    for (size_t i = 1; i < length; ++i) {
        if (base[i - 1] > base[i]) {
            return 1;
        }
    }
    return 0;
}


#define SIZE 10


int main() {
//    srand((unsigned int)time(NULL));
    int test[SIZE] = {5, 3, 1, 9, 12, 16, 7, -100, 13, 44};
//    selection_sort(test, SIZE);

    size_t m = 7;

    quick_sort(test, 0, SIZE - 1, m);
    for (size_t i = 0; i < SIZE; ++i) {
        printf("%d ", test[i]);
    }

    fflush(stdout);
    assert(!test_sort(test, SIZE));


    return 0;
}