#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 


int64_t P_n(int64_t x, const int64_t *coefs, size_t n) {
    if (n == 0) {
        return *coefs;
    }
    return coefs[n] + x * P_n(x, coefs, n - 1);
}


int64_t P_prime_n(int64_t x, const int64_t *coefs, size_t n) {
    if (n == 0) {
        return 0;
    }

    return P_n(x, coefs, n - 1) + x * P_prime_n(x, coefs, n - 1);
}


int main() {
   size_t n = 0;
   int64_t x_0 = 0;
   scanf("%zu %ld", &n, &x_0);

   int64_t *poly_coefs = malloc((n + 1) * sizeof (int64_t));
   for (int i = 0; i < n + 1; ++i) {
       scanf("%ld", poly_coefs + i);
   }
    // size_t n = 3;
    // int64_t *poly_coefs = malloc((n + 1) * sizeof (int64_t));

    // double x_0 = 3;
    // poly_coefs[0] = 1;
    // poly_coefs[1] = -2;
    // poly_coefs[2] = 15;
    // poly_coefs[3] = -10;

    // int error_flag = 0;

    int64_t res = P_n(x_0, poly_coefs, n);
    printf("%ld\n", res);

    res = P_prime_n(x_0, poly_coefs, n);

    printf("%ld\n", res);

    free(poly_coefs);
    return 0;
}