#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>


void selection_sort(int64_t *base, size_t length) {
    assert(base != NULL && length);

    for (size_t i = 0; i < length - 1; ++i) {
        int64_t cur_min = base[i];
        size_t cur_min_index = i;
        for (size_t j = i + 1; j < length; ++j) {
            if (cur_min > base[j]) {
                cur_min = base[j];
                cur_min_index = j;
            }
        }
        if (cur_min_index != i) {
            int64_t placeholder = base[i];
            base[i] = base[cur_min_index];
            base[cur_min_index] = placeholder;
        }
    }
}


size_t partition(int64_t *base, size_t l, size_t r) {
    size_t pivot_index = r;

    size_t i = l;
    for (size_t j = i; j < r; ++j)  {
        if (base[j] <= base[pivot_index]) {
            int64_t placeholder = base[i];
            base[i] = base[j];
            base[j] = placeholder;
            ++i;
        }
    }
    int64_t placeholder = base[i];
    base[i] = base[r];
    base[r] = placeholder;
    return i;
}

size_t random_partition(int64_t *base, size_t l, size_t r) {
    size_t subarray_length = r - l + 1;
    size_t pivot_index = l + (rand() % subarray_length);
    int64_t placeholder = base[pivot_index];
    base[pivot_index] = base[r];
    base[r] = placeholder;
    return partition(base, l, r);
}


void quick_sort(int64_t *base, size_t l, size_t r, size_t m) {
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



int64_t test_sort(int64_t *base, size_t length) {
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


int main() {
    size_t n, m;
    scanf("%zu %zu", &n, &m);

    int64_t *arr = malloc(sizeof(int64_t) * n);
    for (size_t i = 0; i < n; ++i) {
        scanf("%ld", arr + i);
    }

    quick_sort(arr, 0, n - 1, m);

    for (size_t i = 0; i < n; ++i) {
        printf("%ld ", arr[i]);
    }

    free(arr);
    return 0;
}