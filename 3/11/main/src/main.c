#include <stdio.h>

#include "lexer.h"
#include "avl.h"


int main() {
    char *items[] = {
            "alpha", "beta", "gamma"
    };

    struct node *test = create_node(items[0], 0);
    for (int i = 1; i < sizeof (items) / sizeof (items[0]); ++i) {
        insert(test, items[i]);
        print_tree(test, "");
        printf("\n");
    }

    int val = get(test, "beta1");
    printf("%d", val);
    return 0;
}