#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>


// math.h нужно линковать как либу
int int_sqrt(int s, bool *error) {
    if (s < 0) {
        *error = true;
        return 0;
    }

    *error = false;
	if (s <= 1) {
		return s;
    }

	int x0 = s / 2;
	int x1 = ( x0 + s / x0 ) / 2;
	while (x1 < x0) {
		x0 = x1;
		x1 = (x0 + s / x0) / 2;
	}		
	return x0;
}


int max_prive_div(int x, bool *error) {
    if (x == 0) {
        return 0;
    } else if (x < 0) {
        x = -x;
    }
    if (x == 1) {
        return 1;
    }

    *error = false;
    int x_sqrt = int_sqrt(x, error);
    if (*error) {
        return -1;
    }

    bool *sieve = malloc(sizeof(bool) * (x_sqrt + 1));

    static_assert(sizeof(bool) == 1, "sizeof(bool) != 1");
    memset(sieve, true, x_sqrt + 1);
    for (int i = 2; i <= x_sqrt; ++i) {
        if (!sieve[i]) {
            continue;
        }
        for (int j = 2 * i; j <= x_sqrt; j += i) {
            sieve[j] = false;
        }
    }

    int res = x_sqrt;
    for (; res > 1; --res) {
        if (sieve[res] && x % res == 0) {
            res = x / res;
            break;
        }
    }

    free(sieve);
    return res;
}



int main() {
    int x;
    if (!scanf("%d", &x)) {
        return EXIT_FAILURE;
    }

    bool error = false;
    int res = max_prive_div(x, &error);
    if (error || printf("%d", res) < 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
