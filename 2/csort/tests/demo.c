#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *scan_str(){
    char *buf = (char *) calloc(1200, 1);
    int i = 0;
    char c;
    while ((c = getchar()) != '\n'){
        if (c == ' ' && (i == 0 || buf[i - 1] == ' '))
            continue;
        buf[i] = c;
        i++;
    }
    if (buf[i - 1] == ' ')
        i--;
    buf[i] = '\0';
    char *str = (char *)calloc(strlen(buf) + 1, 1);
    strcpy(str, buf);
    free(buf);
    return (str);
}

int how_many_words(char *str) {
    int spaces = 0;
    int i = 0;
    while(str[i]){
        if (str[i] == ' ')
            spaces++;
        i++;
    }
    if (i == 0)
        return (0);
    return (spaces + 1);
}

void make_index_array(int *arr, int words, char *str){
    int i_arr = 0;
    int i_str = 0;
    int in_word = 0;
    while (i_arr < words){
        if (in_word == 0 && str[i_str] != ' '){
            arr[i_arr] = i_str;
            i_arr++;
            in_word = 1;
        }
        else if (in_word == 1 && str[i_str] == ' ')
            in_word = 0;
        i_str++;
    }
    arr[i_arr] = (int)strlen(str) + 1;
}


int find_len(int *arr, int n, int num){
    int i = 0;
    while (i < n){
        if (arr[i] == num)
            break;
        i++;
    }
    if (i == n - 1 && arr[i] != num)
        return (0);
    return (arr[i + 1] - arr[i] - 1);
}



void csort(char *src, char *dest){
    int words = how_many_words(src);
    int *indx_arr = (int *) malloc((words + 1) * sizeof(int));
    make_index_array(indx_arr, words, src);
    int *count = (int *) calloc(words, sizeof(int));
    for (int i = 0; i < words; i++)
        count[i] = -1;
    for (int i = 0; i < words; i++){
        int len_i = indx_arr[i + 1] - indx_arr[i] - 1;
        int k = 0;
        for (int j = 0; j < words; j++){
            int len_j = indx_arr[j + 1] - indx_arr[j] - 1;
            if (len_i > len_j)
                k++;
        }
        while (count[k] != -1)
            k++;
        count[k] = indx_arr[i];
    }
    for (int i = 0; i < words; i++){
        strncat(dest, src + count[i], find_len(indx_arr, words, count[i]));
        if (i < words - 1)
            strcat(dest, " ");
    }
    
    free(indx_arr);
    free(count);
}



int main() {
    char *src = scan_str();
    char *dest = (char *)calloc(strlen(src) + 1, 1);
    csort(src, dest);
    puts(dest);
    free(src);
    free(dest);
    return 0;
}

