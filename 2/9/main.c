#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void inplace_csort(char *data, size_t length) {
    size_t counting[26] = {};
    for (size_t i = 0; i < length; ++i) {
        ++counting[data[i] - 'a'];
    }

    for (int i = 1; i < 26; ++i) {
        counting[i] += counting[i-1];
    }
    
    for (int i = 25; i > 0; --i) {
        char letter = i + 'a';
        while (counting[i] >= counting[i - 1]) {
            if (counting[i] == 0) {
                goto done;
            }
            data[--counting[i]] = letter;
        }
    }
    
    while (counting[0]) {
        data[--counting[0]] = 'a';
    }

    done:
}


int main() {
    char data[100] = {};
    scanf("%s", data);
    size_t length = strlen(data);
    printf("%s\n", data);
    csort(data, length);
    printf("%s\n", data);
    return 0;
}