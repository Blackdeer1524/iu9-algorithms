#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *concat(char **s, int n) {
    size_t new_string_length = 0;

    for (size_t i = 0; i < n; ++i) {
        new_string_length += strlen(s[i]);
    }

    char *result = malloc(sizeof (char) * (new_string_length + 1));
    result[new_string_length] = '\0';
    char *res_pointer = result;

    for (size_t i = 0; i < n; ++i) {
        size_t current_str_length = strlen(s[i]);
        memmove(res_pointer, s[i], current_str_length);
        res_pointer += current_str_length;
    }
    return result;
}


int main() {
    int n;
    scanf("%d", &n);
    char **test = malloc(sizeof(char *) * n);
    for (size_t i = 0; i < n; ++i) {
        char *r = malloc(sizeof(char) * 1000);
        scanf("%s", r);
        test[i] = r;
    }

    char *concat_res = concat(test, n);
    printf("%s", concat_res);
    free(concat_res);


    for (size_t i = 0; i < n; ++i) {
        free(test[i]);
    }
    free(test);
    return 0;
}