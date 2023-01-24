#include <stdio.h>
#include <string.h>

#include "segment_tree.h"


int main() {
    // FILE* stdin = fopen("./input.txt", "r");
    size_t n;
    scanf("%zu", &n);

    int *array = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", array + i);
    }

    Node *tree = build_segment_tree(array, n);

    char buffer[5];
    buffer[4] = '\0';

    bool error = false;
    while (getchar() != EOF) {
        buffer[0] = getchar();
        buffer[1] = getchar();
        buffer[2] = getchar();

        if (!strcmp(buffer, "END")) {
            break;
        } 
        buffer[3] = getchar();
        
        if (!strcmp(buffer, "PEAK")) {
            size_t l, r;
            scanf("%zu %zu", &l, &r);

            size_t res = get_peak_count(tree, l, r, &error);
            if (error) {
                break;
            }
            printf("%zu\n", res);
        } else if (!strcmp(buffer, "UPD")) {
            size_t index;
            int new_value;
            scanf("%zu %d", &index, &new_value);

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