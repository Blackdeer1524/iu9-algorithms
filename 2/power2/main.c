#include <stdio.h>
#include <stdlib.h>

int is_power_of_2(int number) {
    // number = abs(number);
    return number && !(number & (number - 1));
}


void count_powers(int *seq, size_t length, size_t start_index, int cur_sum, size_t *count) {
    cur_sum += seq[start_index];
    if (is_power_of_2(cur_sum)) {
        *count += 1;
    }

    for (size_t i=start_index + 1; i < length; ++i) {
        count_powers(seq, length, i, cur_sum, count);
    }
}


int main() {
    size_t n;
    scanf("%zu", &n);
    
    int *seq = malloc(sizeof(int) * n);
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", seq + i);
    }

    size_t count = 0;
    for (size_t i = 0; i < n; ++i) {
        count_powers(seq, n, i, 0, &count);
    }

    printf("%zu", count);
    free(seq);
    return 0;
} 