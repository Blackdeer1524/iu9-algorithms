#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>


int64_t max_prive_div(int64_t x) {
    if (x == 0) {
        return 0;
    } else if (x < 0) {
        x = -x;
    }
    if (x == 1) {
        return 1;
    }
    
    bool *sieve = calloc((x + 1), sizeof(bool));
    int64_t offset = 1;
    for (int64_t i = 2; i <= x; ++i) {
        if (sieve[i]) {
            continue;
        }
        if (x % i != 0) {
            sieve[i] = true;
        } else {
            offset = i;
        }
        for (int64_t j = i * i; j <= x; j += i) {
            sieve[j] = true;
        }
    }

    free(sieve);
    return offset;
}



int main() {
    int64_t x;
    if (!scanf("%ld", &x)) {
        return EXIT_FAILURE;
    }

    int64_t res = max_prive_div(x);
    if (printf("%ld", res) < 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}