#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


void revarray(void *base, size_t nel, size_t width) {
    if (base == NULL || nel == 1) {
        return;
    }

    char *char_base = (char *) base; 

    char *intermediate_buffer = malloc(width);
    char *right_item = char_base + (nel - 1) * width;
    for (size_t i = 0; i < nel / 2; ++i) {
        memcpy(intermediate_buffer, char_base, width);
        memcpy(char_base, right_item, width);
        memcpy(right_item, intermediate_buffer, width);
        char_base += width;
        right_item -= width;
    }
    free(intermediate_buffer);
}

int main() {
    double even_test_array[] = {3.F, 6.F, 10.F, 13.F};
    int odd_test_array[] = {3, 6, 10, 13, 15};

    size_t even_base_type_width = sizeof (even_test_array[0]);
    size_t odd_base_type_width = sizeof (odd_test_array[0]);

    size_t even_test_array_length = sizeof (even_test_array) / even_base_type_width;
    size_t odd_test_array_length = sizeof (odd_test_array) / odd_base_type_width;

    for (size_t i = 0; i < even_test_array_length; ++i) {
        printf("%lf ", even_test_array[i]);
    }
    printf("\n");
    revarray(even_test_array, even_test_array_length, even_base_type_width);
    for (size_t i = 0; i < even_test_array_length; ++i) {
        printf("%lf ", even_test_array[i]);
    }
    printf("\n");

    for (size_t i = 0; i < odd_test_array_length; ++i) {
        printf("%d ", odd_test_array[i]);
    }
    revarray(odd_test_array, odd_test_array_length, odd_base_type_width);
    printf("\n");
    for (size_t i = 0; i < odd_test_array_length; ++i) {
        printf("%d ", odd_test_array[i]);
    }
    printf("\n");
}