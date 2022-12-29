#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#define SIZE 2

int arr[SIZE] = {5, 4, 3, 2, 1};

void bubblesort(unsigned long nel,
                int (*compare)(unsigned long i, unsigned long j),
                void (*swap)(unsigned long i, unsigned long j)) {
    if (nel <= 1) {
        return;
    }
    unsigned l = 0, r = nel;
    while (l < r) {
        for (unsigned long i = l; i < r - 1; ++i) {
            int cmp = compare(i, i + 1);
            if (cmp == 1) {
                swap(i, i + 1);
            }
        }
        --r;
        for (unsigned long i = r - 1; i > l; --i) {
            int cmp = compare(i, i - 1);
            if (cmp == -1) {
                swap(i, i - 1);
            }
        }
        ++l;
    }
}


int cmp(unsigned long i, unsigned long j) {
    if (arr[i] > arr[j]) {
        return 1;
    } else if (arr[i] < arr[j]) {
        return -1;
    } else {
        return 0;
    }
}


void swap(unsigned long i, unsigned long j) {
    int placeholder = arr[i];
    arr[i] = arr[j];
    arr[j] = placeholder;
}


int main() {
    bubblesort(SIZE, cmp, swap);

    for (int i = 0; i < SIZE; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}