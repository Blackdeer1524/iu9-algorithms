#include <string.h>
#include "lexer.h"

int main() {
    char *sentence = "1 + x - x + (alpha beta gamma) - x";
    tokenize(sentence, strlen(sentence));
}