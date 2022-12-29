#include <stdlib.h>
#include <stdio.h>

typedef union {
    int x;
    unsigned char bytes[4];
} Int32;


#define BYTE_SIZE 256

void csort_ubytes(Int32 *data, Int32 *results, size_t length, int radix_place) {
    size_t count[BYTE_SIZE] = {};
    for (size_t i = 0; i < length; ++i) {
        ++count[data[i].bytes[radix_place]];
    }

    for (size_t i = 1; i < BYTE_SIZE; ++i) {
        count[i] += count[i-1];        
    }

    for (size_t i = length - 1; i > 0; --i) {
        results[--count[data[i].bytes[radix_place]]] = data[i];
    }
    results[--count[data[0].bytes[radix_place]]] = data[0];
}

#define MAX_NEGATIVE 128

void csort_bytes(Int32 *data, Int32 *results, size_t length, int radix_place) {
    size_t count[BYTE_SIZE] = {};
    // -128, ...0, ... +127
    for (size_t i = 0; i < length; ++i) {
        ++count[(char)(data[i].bytes[radix_place]) + MAX_NEGATIVE];
    }

    for (size_t i = 1; i < BYTE_SIZE; ++i) {
        count[i] += count[i-1];        
    }

    for (size_t i = length - 1; i > 0; --i) {
        results[--count[(char)(data[i].bytes[radix_place]) + MAX_NEGATIVE]] = data[i];
    }
    results[--count[(char)(data[0].bytes[radix_place]) + MAX_NEGATIVE]] = data[0];
}


void radix_sort(Int32 *data, size_t length) {
    Int32 *buffer = malloc(sizeof(Int32) * length); 
    
    csort_ubytes(data, buffer, length, 0);
    csort_ubytes(buffer, data, length, 1);
    csort_ubytes(data, buffer, length, 2);
    csort_bytes(buffer, data, length, 3);
    
    free(buffer);
}

void print_data(Int32 *data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", data[i].x);
    }
    putc('\n', stdout);
}

int main() {
    size_t n;
    scanf("%zu", &n);
    Int32 *data = malloc(sizeof(Int32) * n); 

    int placeholder; 
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &placeholder);
        data[i].x = placeholder;
    }
    radix_sort(data, n);
    print_data(data, n);
    return 0;
}