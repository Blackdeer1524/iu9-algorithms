#include <stdio.h>
#include <ctype.h>

int wcount(char *s) {
    if (s == NULL) {
        return 0;
    }
    int word_count = 0;
    char c;
    while (1) {
        while ((c = *s) != '\0' && isblank(c)) {
            ++s;
        }
        if (c == '\0') {
            break;
        }
        ++word_count;
        while ((c = *s) != '\0' && !isblank(c)) {
            ++s;
        }
    }
    return word_count;
}

int main() {
    char *test = "";
    printf("%d", wcount(test));
    return 0;
}