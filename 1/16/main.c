#include <stdio.h>

int strdiff(char *a, char *b) {
    int i;
    for (i = 0; *a != '\0' && *b != '\0'; ++i, ++a, ++b) {
        if (*a ^ *b) {
            int pos = 0;
            char a_val = *a, b_val = *b;
            for (int j = 0; j < 8; ++j, a_val >>= 1, b_val >>= 1) {
                if (a_val % 2 != b_val % 2) {
                    break;
                }
                ++pos;
            }
            return i * 8 + pos;
        }
    }

    if ((*a == '\0') ^ (*b == '\0')) {
        return i * 8;
    }

    return -1;
}


int main() {
    printf("%d", strdiff("aa1", "a"));
    return 0;
}