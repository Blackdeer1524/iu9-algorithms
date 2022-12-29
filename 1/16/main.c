#include <stdio.h>

int strdiff(char *a, char *b) {
    int i;

    for (i = 0; *a != '\0' && *b != '\0'; ++i, ++a, ++b) {
        if (*a ^ *b) {
            unsigned char a_val = *a, b_val = *b;
            int last_diff = 0;
            for (int j = 0; j < 8; ++j, a_val >>= 1, b_val >>= 1) {
                if (a_val % 2 != b_val % 2) {
                    last_diff = j;
                }
            }
            return i * 8 + last_diff;
        }
    }
    
    if (*a == *b) {
        return -1;
    }

    int last_diff = 0;
    unsigned char a_val = *a, b_val = *b;
    for (int j = 0; j < 8; ++j, a_val >>= 1, b_val >>= 1) {
        if (a_val % 2 != b_val % 2) {
            last_diff = j;
            break;
        }
    }
    return i * 8 + last_diff;
}


int main() {
    printf("%d\n", strdiff("The quick brown fox jumps over the lazy dog",
                         "T"));
    return 0;
}