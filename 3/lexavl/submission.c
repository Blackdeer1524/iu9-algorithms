#define _GNU_SOURCE

// =========./lib/include/avl.h=========

#ifndef IU_ALGOS_AVL_H
#define IU_ALGOS_AVL_H

struct node;

typedef struct node node;

typedef enum {
    NO_INSERT,
    LEFT_T,
    RIGHT_T
} subtree_t;

void print_tree(node *root, char *pref);

void free_tree(node *root);

struct node *create_node(char *key, int height);

int avlget(struct node *root, char *identifier_name);

subtree_t avlinsert(struct node **root, char *item);

#endif //IU_ALGOS_AVL_H

// =========./lib/src/avl.c=========

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// #include "avl.h"


// Это - основа. Это, так сказать, база
// https://www.youtube.com/watch?v=jDM6_TnYIqE

static int new_identifier_index = 0;

typedef struct node {
    char *identifier_name;
    int identifier_value;
    int height;
    node *left;
    node *right;
} node;


void print_tree(node *root, char *pref) {
    printf("<%s> (k:%s, i:%d, h:%d) ", pref, root->identifier_name, root->identifier_value, root->height);
    size_t pref_length = strlen(pref);
    if (root->left != NULL) {
        char *l_pref = malloc(sizeof (char) * (pref_length + 2));
        strncpy(l_pref, pref, pref_length);
        l_pref[pref_length] = 'L';
        l_pref[pref_length + 1] = '\0';
        print_tree(root->left, l_pref);
        free(l_pref);
    }
    if (root->right != NULL) {
        char *r_pref = malloc(sizeof (char) * (pref_length + 2));
        strncpy(r_pref, pref, pref_length);
        r_pref[pref_length] = 'R';
        r_pref[pref_length + 1] = '\0';
        print_tree(root->right, r_pref);
        free(r_pref);
    }
}


void free_tree(node *root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root->identifier_name);
    free(root);
}


static int height(node* p) {
    return (p == NULL) ? -1 : p->height;
}


static int bfactor(node* p) {
    return height(p->right) - height(p->left);
}


static void fixheight(node* p) {
    int hl = height(p->left);
    int hr = height(p->right);
    if (hl == -1 && hr == -1) {
        p->height = 0;
    } else {
        p->height = (hl > hr ? hl : hr) + 1;
    }
}


struct node *create_node(char *identifier_name, int height) {
    struct node *leaf = malloc(sizeof (struct node));
    leaf->identifier_name = malloc(sizeof(char) * (strlen(identifier_name) + 1));
    strcpy(leaf->identifier_name, identifier_name);
    leaf->identifier_value = new_identifier_index++;
    leaf->left = NULL;
    leaf->right = NULL;
    leaf->height = height;
    return leaf;
}


int avlget(struct node *root, char *identifier_name) {
    if (root == NULL) {
        return -1;
    }

    int cmp = strcmp(root->identifier_name, identifier_name);
    if (cmp == 0) {
        return root->identifier_value;
    } else if (cmp < 0) {
        return avlget(root->right, identifier_name);
    } else {
        return avlget(root->left, identifier_name);
    }
}


subtree_t avlinsert(struct node **root_ptr, char *identifier_name) {
    node *root = *root_ptr;
    if (root == NULL) {
        *root_ptr = create_node(identifier_name, 0);
        return NO_INSERT;
    }

    int cmp = strcmp(root->identifier_name, identifier_name);    
    if (cmp > 0) {
        // L
        subtree_t insertion_direction = avlinsert(&root->left, identifier_name);
        fixheight(root);
        int balancing_factor = bfactor(root);
        if (-2 < balancing_factor && balancing_factor < 2) {
            return LEFT_T;
        }

        switch (insertion_direction) {
            case LEFT_T: {  // LL
                // swaps root and middle
                node placeholder = *root;  // full copy
                node *l_subtree = root->left;
                node *lr_subtree = l_subtree->right;
                *root = *l_subtree;
                *l_subtree = placeholder;

                // root and r_subtree are swapped
                // root contains r_subtree data now
                // r_subtree contains root data now
                root->right = l_subtree;
                root->right->left = lr_subtree;

                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            case RIGHT_T: {  // LR
                node *l_node = root->left;
                node *lr_node = l_node->right;

                node *lrl_subtree;
                node *lrr_subtree;
                lrl_subtree = lr_node->left;
                lrr_subtree = lr_node->right;

                node placeholder = *root;
                *root = *lr_node;
                *lr_node = placeholder;

                root->right = lr_node;
                root->right->left = lrr_subtree;
                root->left = l_node;
                root->left->right = lrl_subtree;
                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            case NO_INSERT:
                break;
            default:
                exit(1);
                break;
        }
        return LEFT_T;
    } else if (cmp < 0) {
        // R
        subtree_t insertion_direction = avlinsert(&root->right, identifier_name);
        fixheight(root);
        int balancing_factor = bfactor(root);
        if (-2 < balancing_factor && balancing_factor < 2) {
            return RIGHT_T;
        }

        switch (insertion_direction) {
            case LEFT_T: {  // RL
                node *r_node = root->right;
                node *rl_node = r_node->left;

                node *rlr_subtree;
                node *rll_subtree;
                rlr_subtree = rl_node->right;
                rll_subtree = rl_node->left;

                node placeholder = *root;
                *root = *rl_node;
                *rl_node = placeholder;

                root->left = rl_node;
                root->left->right = rll_subtree;
                root->right = r_node;
                root->right->left = rlr_subtree;
                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            case RIGHT_T: {  // RR
                // swaps root and middle
                node placeholder = *root;  // full copy
                node *r_subtree = root->right;
                node *rl_subtree = r_subtree->left;
                *root = *r_subtree;
                *r_subtree = placeholder;

                // root and r_subtree are swapped
                // root contains r_subtree data now
                // r_subtree contains root data now
                root->left = r_subtree;
                root->left->right = rl_subtree;

                fixheight(root->left);
                fixheight(root->right);
                fixheight(root);
                break;
            }
            case NO_INSERT:
                break;
            default:
                exit(1);
                break;
        }
        return RIGHT_T;
    }
    return NO_INSERT;
}

// =========./lib/include/lexer.h=========

#ifndef IU_ALGOS_LEXER_H
#define IU_ALGOS_LEXER_H

#include <stdio.h>

typedef enum {
    CONST,
    SPEC,
    IDENT
}  LEXEM_T;

typedef enum {
    SPEC_plus,
    SPEC_minus,
    SPEC_mul,
    SPEC_div,
    SPEC_l_parenthesis,
    SPEC_r_parenthesis
} SPEC_T;


typedef struct  {
    LEXEM_T tag;
    int value;
} lexem;


void tokenize(const char *sentence, size_t sentence_length);

#endif //IU_ALGOS_LEXER_H

// =========./lib/src/lexer.c=========

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

// #include "lexer.h"
// #include "avl.h"


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
        // printf("value: %s\n", buffer);

        lexem next_lexem = classify_token(
                next_token_start,
                new_token_length,
                contains_chars,
                &identifier_tree_node);

        // printf("<%s> type: %d; value:%d\n", buffer, next_lexem.tag, next_lexem.value);
        switch (next_lexem.tag)
        {
        case CONST:
            printf("%s ", "CONST");
            break;
        case SPEC:
            printf("%s ", "SPEC");
            break;
        case IDENT:
            printf("%s ", "IDENT");
            break;
        default:
            break;
        }
        printf("%d\n", next_lexem.value);
        next_token_start += new_token_length;
    }
    free_tree(identifier_tree_node);
    free(buffer);
}

// ====main.c======================================

#include <string.h>
#include <stdlib.h>
// #include "lexer.h"


int main() {
    size_t sentence_length;
    if (scanf("%zu", &sentence_length) != 1) {
        return EXIT_FAILURE;
    }
    getchar();
    size_t placeholder = sentence_length;
    char *sentence = malloc((++sentence_length) * sizeof(char));
    if (getline(&sentence, &placeholder, stdin) == -1) {
        free(sentence);
        return EXIT_FAILURE;
    }
    sentence[sentence_length - 1] = '\0';
    tokenize(sentence, sentence_length);
    free(sentence);
    return EXIT_SUCCESS;
}
