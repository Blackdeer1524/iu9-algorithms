#include <stdio.h>
#include "lexer.h"
#include "avl.h"


int main() {
//    struct node *test = create_node(14, 0);

//    int array[] = {7, 14, 16,
//                   3, 11, 15,
//                   17, 1, 9,
//                   12};
//    for (int i = 0; i < sizeof (array) / sizeof (array[0]); ++i) {
//        insert(test, array[i]);
//        print_tree(test, "");
//        printf("\n");
//    }
//    insert(test, 10);
//    print_tree(test, "");
//    printf("\n");

//    struct node *test = create_node(15, 0);
//    int array[] = {10, 20, 17, 30};
//    for (int i = 0; i < sizeof (array) / sizeof (array[0]); ++i) {
//        insert(test, array[i]);
//        print_tree(test, "");
//        printf("\n");
//    }
//    insert(test, 25);
//    print_tree(test, "");
//    printf("\n");

    struct node *test = create_node(0, 0);
    for (int i = 20; i > -1; --i) {
        insert(test, i);
        print_tree(test, "");
        printf("\n");
    }
    return 0;
}