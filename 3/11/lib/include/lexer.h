#ifndef IU_ALGOS_LEXER_H
#define IU_ALGOS_LEXER_H

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


void tokenize(char *sentence, int sentence_length);

#endif //IU_ALGOS_LEXER_H
