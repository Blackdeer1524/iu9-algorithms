#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prefix.h" 


int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *str = argv[1];
    if (find_prefixes(str, strlen(str))) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}