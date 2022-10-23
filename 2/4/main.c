#include <stdio.h>

#define SIZE 10
int arr[SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

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


void shellsort(unsigned long nel,
               int (*compare)(unsigned long i, unsigned long j),
               void (*swap)(unsigned long i, unsigned long j)) {
    if (nel == 1) {
        return;
    }

    unsigned long start = 1, middle = 1, next;
    while ((next = start + middle) < nel) {
        start = middle;
        middle = next;
    }

    while (start != 0) {
        for (unsigned long i = middle; i < nel; ++i) {
            for (unsigned long j = i; (j >= middle) && compare(j - middle, j) == 1; j -= middle) {
                swap(j - middle, j);
            }
        }

        next = middle;
        middle = start;
        start = next - middle;
    }
}


int main() {
    shellsort(SIZE, cmp, swap);
    for (int i = 0; i < SIZE; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}