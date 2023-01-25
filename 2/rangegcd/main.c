#include <stdlib.h>
#include <stdio.h>
#include "table.h"




int main() {
    // size_t n;
    // if (scanf("%zu", &n) != 1) {
    //     return EXIT_FAILURE;
    // }

    // int *array = malloc(sizeof(int) * n);
    // for (size_t i = 0; i < n; ++i) {
    //     if (scanf("%d", array + i) != 1) {
    //         free(array);
    //         return EXIT_FAILURE;
    //     }
    //     if (array[i] < 0) {
    //         array[i] = -array[i];
    //     }
    // }
    
    
    size_t n = 10;
    int array[] = {-3, 1, 5, 10, 13, 26, -52, 0, 10, 0};
    for (size_t i = 0; i < n; ++i) { 
        if (array[i] < 0) {
            array[i] = -array[i];
        }
    }

    


    return EXIT_SUCCESS;
}