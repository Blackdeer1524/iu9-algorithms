#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int main() {
    size_t sentence_length;
    if (scanf("%zu", &sentence_length) != 1) {
        return EXIT_FAILURE;
    }
    getchar();
    size_t placeholder = sentence_length;
    char *sentence = malloc((++sentence_length) * sizeof(char));
    if (getline(&sentence, &placeholder, stdin) == -1) {
        free(sentence);
        return EXIT_FAILURE;
    }
    sentence[sentence_length - 1] = '\0';
    tokenize(sentence, sentence_length);
    free(sentence);
    return EXIT_SUCCESS;
}
