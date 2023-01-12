#include <string.h>
#include "bmall.h"


int main(int argc, char *argv[]) {
    // char *src = argv[2];
    // char *pattern = argv[1];
        
    // char *src     = "ndd9Md9PdPdPndd9ZTadnxddrddxds3ddrddsddddMLddd9ddrddr6dyddr"; 
    // char *pattern = "ddrdd";
    char *src = "aaaaaaaaaaaaa";
                //  abcba
                    // abcba
    char *pattern = "aaaaa";

    boyer_moore_str_search(src, strlen(src), pattern, strlen(pattern));
    return 0;
}