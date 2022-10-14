#include <stdio.h>
#include <stdlib.h>


double P_n(double x, const int *coefs, int n, int *error_flag) {
    if (n < 0) {
        *error_flag = 1;
        return 0;
    }
    if (n == 0) {
        return *coefs;
    }
    return coefs[n] + x * P_n(x, coefs, n - 1, error_flag);
}


double P_prime_n(double x, const int *coefs, int n, int *error_flag) {
    if (n < 0) {
        *error_flag = 1;
        return 0;
    }

    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return coefs[n];
    }

    return P_n(x, coefs, n - 1, error_flag) + x * P_prime_n(x, coefs, n - 1, error_flag);
}


int main() {
//    int n = 0;
//    double x_0 = 0;
//    scanf("%d %lf", &n, &x_0);
//
//    int *poly_coefs = malloc((n + 1) * sizeof (int));
//    for (int i = 0; i < n; ++i) {
//        scanf("%d", poly_coefs + i);
//    }
//    int error_flag = 0;
    int n = 2;
    double x_0 = 2;
    int *poly_coefs = malloc((n + 1) * sizeof (int));
    poly_coefs[0] = 1;
    poly_coefs[1] = 1;
    poly_coefs[2] = 0;

    int error_flag = 0;

    double res = P_n(x_0, poly_coefs, n, &error_flag);
    printf("%lf\n", res);

    error_flag = 0;
    res = P_prime_n(x_0, poly_coefs, n, &error_flag);
    printf("%lf\n", res);

    free(poly_coefs);
    return 0;
}