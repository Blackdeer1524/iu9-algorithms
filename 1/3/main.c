#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


int *generate_fib_list(int x, int *generated_size) {
    int list_size = 10;
    int *fib_list = malloc(sizeof(int) * list_size);
    int current_size = 0;

    int start = 0;
    int middle = 1;
    int next;
    while ((next = middle + start) <= x) {
        if (current_size == list_size) {
            list_size <<= 1;
            int *next_mem_location = malloc(sizeof (int) * list_size);
            memcpy(next_mem_location, fib_list, list_size >> 1);
            free(fib_list);
            fib_list = next_mem_location;
        }

        fib_list[current_size] = next;

        start = middle;
        middle = next;
        ++current_size;
    }

    *generated_size = current_size;
    return fib_list;
}


void fibsys(int x, int *fib_list) {

}


int main() {
    int n;
    int *test = generate_fib_list(8, &n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", test[i]);
    }
    return 0;
}