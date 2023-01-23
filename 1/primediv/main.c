#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <limits.h>
#include <inttypes.h>

// math.h нужно линковать как либу
int64_t int_sqrt(int64_t s, bool *error) {
    if (s < 0) {
        *error = true;
        return 0;
    }

    *error = false;
	if (s <= 1) {
		return s;
    }

	int64_t x0 = s / 2;
	int64_t x1 = ( x0 + s / x0 ) / 2;
	while (x1 < x0) {
		x0 = x1;
		x1 = (x0 + s / x0) / 2;
	}		
	return x0;
}



int64_t max_prive_div(int64_t x, bool *error) {
    if (x == 0) {
        return 0;
    } else if (x < 0) {
        x = -x;
    }
    if (x == 1) {
        return 1;
    }
    
    *error = false;
    int64_t x_sqrt = int_sqrt(x, error);
    if (*error) {
        return -1;
    }

    bool *sieve = calloc((x + 1), sizeof(bool));
    for (int64_t i = 2; i <= x_sqrt; ++i) {
        if (sieve[i]) {
            continue;
        }
        for (int64_t j = i * i; j <= x; j += i) {
            sieve[j] = true;
        }
    }

    int64_t res = x;
    for (; res > 1; --res) {
        if (!sieve[res] && x % res == 0) {
            break;
        }
    }

    free(sieve);
    return res;
}



int main() {
    int64_t x;
    if (!scanf("%ld", &x)) {
        return EXIT_FAILURE;
    }

    bool error = false;
    int64_t res = max_prive_div(x, &error);
    if (error || printf("%ld", res) < 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
