#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <stdint.h>

int64_t *generate_fib_list(int64_t x, int64_t *generated_size) {
    int64_t list_size = 10;
    int64_t *fib_list = malloc(sizeof(int64_t) * list_size);
    int64_t current_size = 0;

    int64_t start = 0;
    int64_t middle = 1;
    int64_t next;
    while ((next = middle + start) <= x) {
        if (current_size == list_size) {
            list_size <<= 1;
            fib_list = realloc(fib_list, list_size * sizeof(int64_t));
        }

        fib_list[current_size] = next;

        start = middle;
        middle = next;
        ++current_size;
    }

    *generated_size = current_size;
    return fib_list;
}


int64_t bin_search(const int64_t *array, int64_t n, int64_t item) {
    int64_t l = 0;
    int64_t r = n - 1;
    while (l <= r) {
        int64_t m = l + ((r - l) / 2);
        int64_t m_ar_item = array[m];
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


void fibsys(int64_t x, const int64_t *fib_list, int64_t n) {
    int64_t next_x = x;
    int64_t max_fib_ind = bin_search(fib_list, n, x);

    int64_t cum_sum = 0;

    while (next_x > 0) {
        cum_sum += fib_list[max_fib_ind];
        next_x -= fib_list[max_fib_ind];
        int64_t next_max_fib_ind = bin_search(fib_list, n, next_x);
        printf("1");
        for (int64_t i = 0; i < max_fib_ind - next_max_fib_ind - 1; ++i) {
            printf("0");
        }
        max_fib_ind = next_max_fib_ind;
    }
    assert(next_x == 0);
    assert(cum_sum == x);
}


int main() {
    int64_t x;
    scanf("%ld", &x);

    if (!x) {
        printf("0");
        return 0;
    }

    int64_t generated_size;
    int64_t *generated_fib_list = generate_fib_list(x, &generated_size);

    fibsys(x, generated_fib_list, generated_size);
    free(generated_fib_list);

    // int64_t items[] = {1, 3, 5, 10, 20, 50, 37, 100};
    // for (int64_t i = 0; i < sizeof (items) / sizeof (items[0]); ++i) {
    //     int64_t fib_seq_length;
    //     int64_t x = items[i];
    //     int64_t *fib_seq = generate_fib_list(x, &fib_seq_length);
    //     print64_tf("%d: ", x);
    //     fibsys(x, fib_seq, fib_seq_length);
    //     print64_tf("\n");
    //     free(fib_seq);
    // }

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