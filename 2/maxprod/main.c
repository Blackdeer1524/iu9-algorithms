#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
 

size_t gcd(size_t left, size_t right) { 
    while (left && right) {
        if (left > right) { 
            left %= right;
        } else {
            right %= left;
        }
    }
    return left + right;    
}


typedef struct {
    size_t numerator;
    size_t denominator;
} Frac;


void fracsimplify(Frac *dst) {
    size_t common_factor = gcd(dst->numerator, dst->denominator);
    dst->numerator /= common_factor;
    dst->denominator /= common_factor;
}


bool fracnew(size_t numerator, size_t denominator, Frac *dst) {
    if (denominator == 0) {
        return true;
    }
    dst->numerator=numerator;
    dst->denominator=denominator;
    fracsimplify(dst);
    return false;
}


Frac fracmul(Frac left, Frac right) {
    Frac res = {
        .numerator = left.numerator * right.numerator,
        .denominator = left.denominator * right.denominator
    };
    size_t common_factor = gcd(res.numerator, res.denominator);
    
    res.numerator /= common_factor;
    res.denominator /= common_factor;
    return res;
}


bool less(Frac left, Frac right) {
    // size_t gcd_of_denominators   = gcd(left.denominator, right.denominator);
    // size_t least_common_multiple = (left.denominator / gcd_of_denominators) * right.denominator;
    // size_t factors_needed_for_left = least_common_multiple / left.denominator;
    // size_t factors_needed_for_right = least_common_multiple / right.denominator;

    // factors_needed_for_left * left.numerator ? factors_needed_for_right * right.numerator
    // left.numerator / factors_needed_for_right ? right.numerator / factors_needed_for_left
    // size_t left_quotient = left.numerator / factors_needed_for_right;
    // size_t right_quotient = right.numerator / factors_needed_for_left;
    // if (left_quotient != right_quotient) {
    //     return left_quotient < right_quotient;
    // }
    // return left.numerator % factors_needed_for_right < right.numerator % factors_needed_for_left;

    size_t left_quotient = left.numerator / left.denominator;
    size_t right_quotient = right.numerator / right.denominator;
    if (left_quotient != right_quotient) {
        return left_quotient < right_quotient; 
    }
    return (left.numerator % left.denominator) < (right.numerator % right.denominator);
}


int main() {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }    
    Frac *array = malloc(n * sizeof(Frac));
    for (size_t i = 0; i < n; ++i) {
        int numerator, denominator;
        if (scanf("%d/%d", &numerator, &denominator) != 2 || fracnew((size_t) numerator, (size_t) denominator, array+i)) {
            free(array);
            return EXIT_FAILURE;
        } 
    }
    
    Frac cur_prod = array[0];
    Frac best_prod = array[0];

    size_t cur_start = 0, cur_end = 0, best_start = 0, best_end = 0;

    for (size_t i = 1; i < n; ++i) {
        cur_prod = fracmul(cur_prod, array[i]);
        if (less(cur_prod, array[i])) {
            cur_prod = array[i];
            cur_start = i;
        } else {
            cur_end = i;
        }
        if (less(best_prod, cur_prod)) {
            best_start = cur_start;
            best_end = cur_end;
            best_prod = cur_prod;
        }
    }

    printf("%zu %zu %lf", best_start, best_end, (double) best_prod.numerator / best_prod.denominator);
    free(array);
    return EXIT_SUCCESS;
}