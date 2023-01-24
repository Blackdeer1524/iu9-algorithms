#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>


void inplace_csort(char *data, size_t length) {
    size_t counting[26] = {};
    for (size_t i = 0; i < length; ++i) {
        ++counting[data[i] - 'a'];
    }

    for (int i = 1; i < 26; ++i) {
        counting[i] += counting[i-1];
    }
    
    bool break_flag = false;
    for (int i = 25; !break_flag && i > 0; --i) {
        char letter = i + 'a';
        while (counting[i] >= counting[i - 1]) {
            if (counting[i] == 0) {
                break_flag = true;
                break;
            }
            data[--counting[i]] = letter;
        }
    }
    
    while (counting[0]) {
        data[--counting[0]] = 'a';
    }
}


#define INPUT_SIZE 1000000

int main() {
    char data[INPUT_SIZE];
    scanf("%s", data);
    size_t length = strlen(data);
    inplace_csort(data, length);
    printf("%s\n", data);
    return 0;
}