#include <stdio.h>
#include <string.h>

#include "segment_tree.h"


int main() {
    char array[1000001]; 
    scanf("%s", array);

    Node *tree = build_segment_tree(array);

    char buffer[4];
    buffer[3] = '\0';

    bool error = false;
    while (getchar() != EOF) {
        buffer[0] = getc(stdin);
        buffer[1] = getc(stdin);
        buffer[2] = getc(stdin);

        if (!strcmp(buffer, "END")) {
            break;
        } else if (!strcmp(buffer, "HD ")) {
            size_t l, r;
            fscanf(stdin, "%zu %zu", &l, &r);

            bool yes = is_hyperdrome(tree, l, r, &error);
            if (error) {
                break;
            }
            if (yes) {
                puts("YES");
            } else {
                puts("NO");
            }
        } else if (!strcmp(buffer, "UPD")) {
            size_t index;
            fscanf(stdin, "%zu", &index);
            scanf("%s", array);
            if (update(tree, index, array)) {
                break;
            }
        } else {
            printf("afsdads");
        }
    }

    free_segment_tree(tree);
    return error;
}