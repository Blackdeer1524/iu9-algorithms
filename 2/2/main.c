#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ispower2(int x) {
    if (x < 0) {
        x = -x;
    }
    return !(x & (x - 1));
}

void count_pow2(int *arr, int arr_length, int cur_ind, int cur_sum, int *ans) {
    assert(cur_ind < arr_length);
    if (ispower2(cur_sum)) {
        ++(*ans);
    }
    for (int i = cur_ind + 1; i < arr_length; ++i) {
        count_pow2(arr, arr_length, i, cur_sum + arr[i], ans);
    }
}

//#define SIZE 5

int main() {
    int n;  //  = SIZE;
    scanf("%d", &n);

    int *seq = malloc(sizeof(int) * n);
    for(int i = 0; i < n; ++i)
        scanf("%d", seq + i);

//    int seq[SIZE] = {1, 2, 3, 4, 5};
    int ans = 0;
    for(int i = 0; i < n; ++i)
        count_pow2(seq, n, i, seq[i], &ans);

    printf("%d", ans);
    free(seq);

    return 0;
}