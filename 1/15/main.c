#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

size_t fib(size_t i) {
    if (i <= 2) {
        return 1;
    }

    size_t start = 1;
    size_t middle = 1;
    size_t next;
    for (size_t j = 2; j < i; ++j) {
        next = start + middle;
        start = middle;
        middle = next;
    }
    return next;
}


char *fibstr(int n) {
    if (n <= 0) {
        return NULL;
    }

    size_t res_length = fib(n);
    char *res = malloc(sizeof (char) * (res_length + 1));
    res[res_length] = '\0';

    if (n == 1) {
        res[0] = 'a';
        return res;
    } else if (n == 2) {
        res[0] = 'b';
        return res;
    }
    res[0] = 'a';
    res[1] = 'b';
    // ab
    size_t ll_size = 1;
    size_t l_size = 1;
    size_t cur_size;
    for (size_t i = 3; i < n; ++i) {
        cur_size = ll_size + l_size;

        memmove(res + l_size, res, cur_size);
        char *prev_part = res + l_size + ll_size;
        memcpy(res, prev_part, cur_size - ll_size);

        ll_size = l_size;
        l_size = cur_size;
    }
    return res;
}


int main() {
//    for (int i = 1; i < 10; ++i){
//        printf("%d ", fib(i));
//    }
    for (int i = 1; i <= 10; ++i) {
        char *res = fibstr(i);
        printf("%s\n", res);
        free(res);
    }
    return 0;
}