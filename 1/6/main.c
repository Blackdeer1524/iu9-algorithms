#include <stdio.h>
#include <stdlib.h>


const int *maximum_k_subarray(const int *seq, int seq_length, int k) {
    if (seq_length <= k) {
        return seq;
    }

    int current_subarray_sum, max_subarray_sum, first_item_of_current_subarray;
    current_subarray_sum = first_item_of_current_subarray = seq[0];
    for (int i = 1; i < k; ++i) {
        current_subarray_sum += seq[i];
    }
    max_subarray_sum = current_subarray_sum;

    const int *max_k_subarray = seq;
    // sliding window
    for (int i = k; i < seq_length; ++i) {
        int current_item = seq[i];
        if ((current_subarray_sum = current_subarray_sum - first_item_of_current_subarray + current_item) >= max_subarray_sum) {
            max_subarray_sum = current_subarray_sum;
            max_k_subarray = seq + i - k + 1;
        }
        first_item_of_current_subarray = seq[i - k + 1];
    }
    return max_k_subarray;
}


int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int *seq = malloc(sizeof (int) * n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", seq + i);
    }

    const int *max_subarray = maximum_k_subarray(seq, n, k);
    for (int i = 0; i < k - 1; ++i) {
        printf("%d ", max_subarray[i]);
    }
    printf("%d", max_subarray[k - 1]);

    free(seq);
    return 0;
}