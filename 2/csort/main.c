#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csort_utils.h"

#define BUFFER_SIZE 1001

int main() {
    char buffer[BUFFER_SIZE] = {'\0'};
    
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        return EXIT_FAILURE;
    }
    size_t scanned_strlen = strlen(buffer); 
    if (scanned_strlen > 0 && buffer[scanned_strlen - 1] == '\n')
        buffer[--scanned_strlen] = '\0';

    char *dest = (char *) malloc(sizeof(char) * (scanned_strlen + 1));
    
    csort(buffer, dest);

    printf("%s", dest);

    free(dest);
    return EXIT_SUCCESS;
}
