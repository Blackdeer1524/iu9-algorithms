#include <stdio.h>
#include <stdlib.h>


int P_n(int a, int b, int m) {
    if (!b) {
        return 0;
    }
    return (a * (b % 2) % m + 2 * P_n(a, b >> 1, m) % m) % m;
}

int main() {
    int a = 3;
    int b = 2;
    int m = 6;
    int res = P_n(a, b, m);
    printf("a=%d, b=%d, m=%d, res=%d", a, b, m, res);
    return 0;
}