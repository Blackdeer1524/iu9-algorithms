#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int main() {
    char *sentence = NULL;
    size_t allocated_size = 0;

    signed long long actual_length;
    if ((actual_length = getline(&sentence, &allocated_size, stdin)) == -1) {
        return EXIT_FAILURE;
    } 
    sentence[actual_length - 1] = '\0';
    tokenize(sentence, strlen(sentence));
    return EXIT_SUCCESS;
}