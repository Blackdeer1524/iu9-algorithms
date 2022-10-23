#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#define abs(x) (((x) > 0) ? (x) : -(x))


void insertion_sort(int *base, size_t length) {
    if (length <= 1) {
        return;
    }

    for (size_t i = 1; i < length; ++i) {
        int temp = base[i];
        size_t j;
        for (j = i; j > 0 && abs(base[j - 1]) > abs(temp); --j) {
            base[j] = base[j - 1];
        }
        base[j] = temp;
    }
}


//void print_arr(int *base, size_t length) {
//    for (size_t i = 0; i < length; ++i) {
//        printf("%d ", base[i]);
//    }
//    printf("\n");
//}


void merge(int *base, size_t l, size_t midpoint, size_t r) {
    assert(l < midpoint);
    assert(midpoint <= r);

    int *placeholder_array = malloc(sizeof (int) * (r - l + 1));

    size_t l_side_index = l;
    size_t r_side_index = midpoint;
    size_t placeholder_arr_index = 0;

    while (l_side_index < midpoint && r_side_index < r) {
        if (abs(base[l_side_index]) < abs(base[r_side_index])) {
            placeholder_array[placeholder_arr_index] = base[l_side_index++];
        } else {
            placeholder_array[placeholder_arr_index] = base[r_side_index++];
        }
        ++placeholder_arr_index;
    }

    while (l_side_index < midpoint) {
        placeholder_array[placeholder_arr_index] = base[l_side_index++];
    }

// not needed
//    while (r_side_index < r) {
//        placeholder_array[placeholder_arr_index] = base[r_side_index++];
//    }

    for (size_t i = 0; i < placeholder_arr_index; ++i) {
        base[l + i] = placeholder_array[i];
    }

    free(placeholder_array);
}



void merge_sort(int *base, size_t l, size_t r) {
    assert(l <= r);

    size_t subarray_length = r - l + 1;
    if (subarray_length <= 5) {
        insertion_sort(base + l, subarray_length);
        return;
    }

    size_t midpoint = l + (r - l) / 2;
    merge_sort(base, l, midpoint - 1);
    merge_sort(base, midpoint, r);
    merge(base, l, midpoint, r);
}


#define SIZE 10

// merge + insertion sort
int main() {
    int arr[SIZE] = {5, 1, 1, 1, 2, 3, 5, 4, -20, 10, };
    merge_sort(arr, 0, SIZE - 1);
    for (size_t i = 0; i < SIZE; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}