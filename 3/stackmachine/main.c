#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct Stack Stack; 
typedef int item_t; 

struct Stack {
    item_t value;
    Stack *next;
};


Stack *stack_push(Stack *dst, item_t value) {
    Stack *new_node = malloc(sizeof(Stack));
    new_node->value = value;
    new_node->next = dst;
    return new_node;
}


Stack *stack_pop(Stack *src, item_t *result) {
    *result = src->value;
    Stack *next = src->next;
    free(src);
    return next;
}


void neg(Stack *src) {
    src->value = -src->value;
}


Stack *dup(Stack *src) {
    return stack_push(src, src->value);
}


void swap(Stack *src) {
    item_t placeholder = src->value;
    src->value = src->next->value;
    src->next->value = placeholder;
}


// ADD SUB MUL DIV MAX MIN
Stack *binary_op(Stack *src, item_t (operator)(item_t left, item_t right)) {
    // сначала снимаем ЛЕВЫЙ, потом - ПРАВЫЙ (?)
    item_t left, right;
    src = stack_pop(src, &left);
    src = stack_pop(src, &right);
    src = stack_push(src, operator(left, right));
    return src;
}


item_t add(item_t left, item_t right) {
    return left + right;
}


item_t subtract(item_t left, item_t right) {
    return left - right;
}

item_t multiply(item_t left, item_t right) {
    return left * right;
}

item_t divide(item_t left, item_t right) {
    return left / right;
}

item_t min(item_t left, item_t right) {
    return (left < right) ? left : right;
}

item_t max(item_t left, item_t right) {
    return (left > right) ? left : right;
}


int main() {
    char buffer[32] = {};
    Stack *stack = malloc(sizeof(Stack));
    stack->next = NULL;
    stack->value = 0;
    do {
        scanf("%s", buffer);
        if (!strncmp(buffer, "CONST", 5)) {
            int res;
            scanf("%d", &res);
            stack = stack_push(stack, res);
        } else if (!strncmp(buffer, "ADD", 3)) {
            stack = binary_op(stack, add);
        } else if (!strncmp(buffer, "SUB", 3)) {
            stack = binary_op(stack, subtract);
        } else if (!strncmp(buffer, "MUL", 3)) {
            stack = binary_op(stack, multiply);
        } else if (!strncmp(buffer, "DIV", 3)) {
            stack = binary_op(stack, divide);
        } else if (!strncmp(buffer, "MAX", 3)) {
            stack = binary_op(stack, max);
        } else if (!strncmp(buffer, "MIN", 3)) {
            stack = binary_op(stack, min);
        } else if (!strncmp(buffer, "NEG", 3)) {
            neg(stack);
        } else if (!strncmp(buffer, "DUP", 3)) {
            stack = dup(stack);
        } else if (!strncmp(buffer, "SWAP", 4)) {
            swap(stack);
        }
    } while (strncmp(buffer, "END", 3));

    printf("%d", stack->value); 
    free(stack->next);
    free(stack);
    return EXIT_SUCCESS;
}