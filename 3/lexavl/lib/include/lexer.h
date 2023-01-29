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
