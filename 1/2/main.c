#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>

uint64_t P_n(int64_t a, int64_t b, int64_t m) {
    if (!b) {
        return 0;
    }
    return ((a * (b % 2)) % m + (2 * P_n(a, b / 2, m)) % m) % m;
}

int main() {
    uint64_t a = 520688861061345203;
    uint64_t b = 5327611179439278236;
    uint64_t m = 5299761356315091779;
    
    scanf("%ld %ld %ld", &a, &b, &m);
    uint64_t res = P_n(a, b, m);
    printf("%ld", res);
    return 0;
}