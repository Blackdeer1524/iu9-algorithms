#include <stdlib.h>
#include <stdio.h>
#include "skip_list.h"

int main() {
    SkipList *a = build_skip_list(2);
    insert(a, 1, "123");
    return EXIT_SUCCESS;
}
