#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

#include "lexer.h"
#include "avl.h"


static lexem classify_token(
        const char *token_start,
        size_t length,
        int contains_char,
        node **identifier_tree_root) {
    if (!length) {
        fprintf(stderr, "cannot classify token with 0 length\n");
        exit(1);
    } else if (length == 1) {
        lexem spec_lexem;
        spec_lexem.tag = SPEC;
        switch (*token_start) {
            case '+':
                spec_lexem.value = SPEC_plus;
                break;
            case '-':
                spec_lexem.value = SPEC_minus;
                break;
            case '*':
                spec_lexem.value = SPEC_mul;
                break;
            case '/':
                spec_lexem.value = SPEC_div;
                break;
            case '(':
                spec_lexem.value = SPEC_l_parenthesis;
                break;
            case ')':
                spec_lexem.value = SPEC_r_parenthesis;
                break;
            default:
                goto determine_const_ident;
        }
        return spec_lexem;
    }

    determine_const_ident:;

    lexem const_ident_lexem;
    int is_first_digit = isdigit(*token_start);
    if (contains_char && is_first_digit) {
        fprintf(stderr, "bad identifier: identifiers cannot start with a digit\n");
        exit(1);
    } else if (contains_char) {
        const_ident_lexem.tag = IDENT;

        char *token_buffer = malloc(sizeof (char) * (length + 1));
        strncpy(token_buffer, token_start, length);
        token_buffer[length] = '\0';
        const_ident_lexem.value = avlget(*identifier_tree_root, token_buffer);

        if (const_ident_lexem.value == -1) {
            avlinsert(identifier_tree_root, token_buffer);
            const_ident_lexem.value = avlget(*identifier_tree_root, token_buffer);
            assert(const_ident_lexem.value != -1);
        }
        free(token_buffer);
    } else {
        const_ident_lexem.tag = CONST;
        char *token_buffer = malloc(sizeof (char) * (length + 1));
        strncpy(token_buffer, token_start, length);
        token_buffer[length] = '\0';
        const_ident_lexem.value = atoi(token_buffer);
        free(token_buffer);
    }
    return const_ident_lexem;
}


static const char *get_next_token(const char *token_start, size_t *new_token_length, int *contains_chars) {
    if (token_start == NULL) {
        fprintf(stderr, "Cannot extract tokens from null pointer\n");
        exit(1);
    }

    // skips blanks
    while (*token_start != '\0' && isblank(*token_start)) {
        ++token_start;
    }
    if (*token_start == '\0') {
        return NULL;
    }

    int token_length = 0;
    int cont_chars = 0;
    char c;
    while ((c = *(token_start + token_length)) != '\0' && (isdigit(c) || isalpha(c))) {
        if (isalpha(c)) {
            cont_chars = 1;
        }
        ++token_length;
    }

    if (!token_length) {
        // cannot be \0 because it was checked above
        *new_token_length = 1;
        *contains_chars = 0;
        return token_start;
    }

//    if (c == '\0') {
//        --token_length;
//    }

    *new_token_length = token_length;
    *contains_chars = cont_chars;
    return token_start;
}


void tokenize(const char *sentence, size_t sentence_length) {
    const char *next_token_start = sentence;
    size_t new_token_length = 0;
    int contains_chars = 0;

    char *buffer = malloc(sizeof(char) * (sentence_length + 1));

    node *identifier_tree_node = NULL;

    while ((next_token_start = get_next_token(next_token_start, &new_token_length, &contains_chars)) != NULL) {
        strncpy(buffer, next_token_start, new_token_length);
        buffer[new_token_length] = '\0';
        printf("value: %s\n", buffer);

        lexem next_lexem = classify_token(
                next_token_start,
                new_token_length,
                contains_chars,
                &identifier_tree_node);

        printf("<%s> type: %d; value:%d\n", buffer, next_lexem.tag, next_lexem.value);
        next_token_start += new_token_length;
    }
    free(buffer);
}
