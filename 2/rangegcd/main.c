#include <stdio.h>
#include <string.h>

#include "segment_tree.h"


int main() {
    // FILE* stdin = fopen("./input.txt", "r");
    size_t n;
    fscanf(stdin, "%zu", &n);

    int *array = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        fscanf(stdin, "%d", array + i);
    }

    Node *tree = build_segment_tree(array, n);

    char buffer[4];
    buffer[3] = '\0';

    int c;
    bool error = false;
    while ((c = getc(stdin)) != EOF) {
        buffer[0] = getc(stdin);
        buffer[1] = getc(stdin);
        buffer[2] = getc(stdin);

        if (!strcmp(buffer, "END")) {
            break;
        } else if (!strcmp(buffer, "MAX")) {
            size_t l, r;
            fscanf(stdin, "%zu %zu", &l, &r);

            int res = get_max(tree, l, r, &error);
            if (error) {
                break;
            }
            printf("%d\n", res);
        } else if (!strcmp(buffer, "UPD")) {
            size_t index;
            int new_value;
            fscanf(stdin, "%zu %d", &index, &new_value);

            if (update(tree, index, new_value)) {
                break;
            }
        } else {
            printf("afsdads");
        }
    }

    free(array);
    free_segment_tree(tree);
    return error;
}