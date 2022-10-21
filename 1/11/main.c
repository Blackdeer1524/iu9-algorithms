#include <stdio.h>

#define SIZE 4

int array[SIZE] = {0, 1, 4, 5};
const int k = 0;

int compare(unsigned long i) {
    if (array[i] > k) {
        return 1;
    } else if (array[i] < k) {
        return -1;
    } else {
        return 0;
    }
}

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) {
    unsigned long left = 0, right = nel - 1;
    while (left <= right) {
        unsigned long mid = right - left / 2;
        int res = compare(mid);

        if (res == 1) {
            if (!mid) {
                break;
            }
            right = mid - 1;
        } else if (res == -1) {
            left = mid + 1;
        } else {
            return mid;
        }
    }

    return nel;
}

int main() {
    printf("%lu\n", binsearch(SIZE, compare));
    return 0;
}