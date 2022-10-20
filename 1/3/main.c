#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>


int *generate_fib_list(int x, int *generated_size) {
    int list_size = 10;
    int *fib_list = malloc(sizeof(int) * list_size);
    int current_size = 0;

    int start = 0;
    int middle = 1;
    int next;
    while ((next = middle + start) <= x) {
        if (current_size == list_size) {
            list_size <<= 1;
            int *next_mem_location = malloc(sizeof (int) * list_size);
            memcpy(next_mem_location, fib_list, list_size >> 1);
            free(fib_list);
            fib_list = next_mem_location;
        }

        fib_list[current_size] = next;

        start = middle;
        middle = next;
        ++current_size;
    }

    *generated_size = current_size;
    return fib_list;
}


int bin_search(const int *array, int n, int item) {
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int m = r - l / 2;
        int m_ar_item = array[m];
        if (m_ar_item == item) {
            return m;
        } else if (m_ar_item < item) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return r;
}


void fibsys(int x, const int *fib_list, int n) {
    int next_x = x;
    int max_fib_ind = bin_search(fib_list, n, x);

    int cum_sum = 0;

    while (next_x > 0) {
        cum_sum += fib_list[max_fib_ind];
        next_x -= fib_list[max_fib_ind];
        int next_max_fib_ind = bin_search(fib_list, n, next_x);
        printf("1");
        for (int i = 0; i < max_fib_ind - next_max_fib_ind - 1; ++i) {
            printf("0");
        }
        max_fib_ind = next_max_fib_ind;
    }
    assert(next_x == 0);
    assert(cum_sum == x);
}


int main() {
    int items[] = {1, 3, 5, 10, 20, 50, 37, 100};
    for (int i = 0; i < sizeof (items) / sizeof (items[0]); ++i) {
        int fib_seq_length;
        int x = items[i];
        int *fib_seq = generate_fib_list(x, &fib_seq_length);
        printf("%d: ", x);
        fibsys(x, fib_seq, fib_seq_length);
        printf("\n");
        free(fib_seq);
    }

//    // Edge cases
//    // will never occur here
//    assert(bin_search(test, n, 0) == -1);
//    // will never occur here
//    assert(bin_search(test, n, 9) == 4);
//
//    assert(bin_search(test, n, 1) == 0);
//    assert(bin_search(test, n, 4) == 2);
//    assert(bin_search(test, n, 8) == 4);

    return 0;
}