#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t maximum_k_subarray(const int64_t *seq, int64_t seq_length, int64_t k) {
    if (seq_length < k) {
        return 0;
    }

    int64_t current_subarray_sum, max_subarray_sum, first_item_of_current_subarray;
    current_subarray_sum = first_item_of_current_subarray = seq[0];
    for (int64_t i = 1; i < k; ++i) {
        current_subarray_sum += seq[i];
    }
    max_subarray_sum = current_subarray_sum;

    const int64_t *max_k_subarray = seq;
    // sliding window
    for (int64_t i = k; i < seq_length; ++i) {
        int64_t current_item = seq[i];
        if ((current_subarray_sum = current_subarray_sum - first_item_of_current_subarray + current_item) >= max_subarray_sum) {
            max_subarray_sum = current_subarray_sum;
            max_k_subarray = seq + i - k + 1;
        }
        first_item_of_current_subarray = seq[i - k + 1];
    }
    return max_subarray_sum;
}


int main() {
    int64_t n;
    scanf("%ld", &n);

    int64_t *seq = malloc(sizeof (int64_t) * n);
    for (int64_t i = 0; i < n; ++i) {
        scanf("%ld", seq + i);
    }

    int64_t k;
    scanf("%ld", &k);

    int64_t max_subarray = maximum_k_subarray(seq, n, k);
    // for (int64_t i = 0; i < k - 1; ++i) {
    //     printf("%d ", max_subarray[i]);
    // }
    printf("%ld", max_subarray);

    free(seq);
    return 0;
}