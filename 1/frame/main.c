#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define print_frame_line(frame_width) do { \
    putchar('*'); \
    for (int j = 0; j < (frame_width); ++j) { \
        putchar(' '); \
    } \
    putchar('*'); \
    putchar('\n'); \
} while(0)


#define print_horizontal_bar(width) do { \
    for (int i = 0; i < (width); ++i) { \
        putchar('*'); \
    } \
    putchar('\n'); \
} while(0)


int main(int argc, char *argv[]) {
    if (argc != 4) {
        puts("Usage: frame <height> <width> <text>");
        return EXIT_SUCCESS;
    }

    int height = atoi(argv[1]);
    if (height < 3) { 
        puts("Error");
        return EXIT_SUCCESS;
    }
    int frame_height = height - 2;

    int width = atoi(argv[2]);
    int frame_width = width - 2;

    char *text = argv[3];
    int text_length = (int) strlen(text);
    if (frame_width < text_length) {
        puts("Error");
        return EXIT_SUCCESS;
    }

    int top_margin = (frame_height - 1) / 2;
    int bottom_margin = frame_height - top_margin - 1;

    int free_horizontal_space = frame_width - strlen(text);
    int left_margin = free_horizontal_space / 2;
    int right_margin = free_horizontal_space - left_margin;

    print_horizontal_bar(width);
    for (int i = 0; i < top_margin; ++i) {
        print_frame_line(frame_width);
    }
    
    putchar('*');
    for (int i = 0; i < left_margin; ++i) {
        putchar(' ');
    }
    printf("%s", text);
    for (int i = 0; i < right_margin; ++i) {
        putchar(' ');
    }
    putchar('*');
    putchar('\n');

    for (int i = 0; i < bottom_margin; ++i) {
        print_frame_line(frame_width);
    }

    print_horizontal_bar(width);
    return EXIT_SUCCESS;
}