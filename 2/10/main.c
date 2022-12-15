#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int Day;
    int Month;
    int Year;
} Date;

#define DAY_RADIX 31
#define MONTH_RADIX 12
#define LEFT_YEAR_BOUND 1970
#define YEAR_RADIX 2030 - LEFT_YEAR_BOUND + 1

void stable_sort_by_day(Date *data, Date *buffer, size_t length) {
    size_t counting[DAY_RADIX] = {};
    for (size_t i = 0; i < length; ++i) {
        ++counting[data[i].Day - 1];
    }

    for (int i = 1; i < DAY_RADIX; ++i) {
        counting[i] += counting[i-1];
    }

    for (size_t i = length - 1; i > 0; --i) {
        buffer[--counting[data[i].Day - 1]] = data[i];
    }
    buffer[--counting[data[0].Day - 1]] = data[0];
}

void stable_sort_by_month(Date *data, Date *buffer, size_t length) {
    size_t counting[MONTH_RADIX] = {};
    for (size_t i = 0; i < length; ++i) {
        ++counting[data[i].Month - 1];
    }

    for (int i = 1; i < MONTH_RADIX; ++i) {
        counting[i] += counting[i-1];
    }

    for (size_t i = length - 1; i > 0; --i) {
        buffer[--counting[data[i].Month - 1]] = data[i];
    }
    buffer[--counting[data[0].Month - 1]] = data[0];
}

void stable_sort_by_year(Date *data, Date *buffer, size_t length) {
    size_t counting[YEAR_RADIX] = {};
    for (size_t i = 0; i < length; ++i) {
        ++counting[data[i].Year - LEFT_YEAR_BOUND];
    }

    for (int i = 1; i < YEAR_RADIX; ++i) {
        counting[i] += counting[i-1];
    }

    for (size_t i = length - 1; i > 0; --i) {
        buffer[--counting[data[i].Year - LEFT_YEAR_BOUND]] = data[i];
    }
    buffer[--counting[data[0].Year - LEFT_YEAR_BOUND]] = data[0];
}

Date *radix_sort(Date *array, Date *result, size_t length) {
    stable_sort_by_day(array, result, length);
    stable_sort_by_month(result, array, length);
    stable_sort_by_year(array, result, length);
}

void print_date(Date date) {
    printf("%04d %02d %02d", date.Year, date.Month, date.Day);
}

int main() {
    size_t n;
    scanf("%zu", &n);
    Date *data = malloc(sizeof(Date) * n); 
    Date *res = malloc(sizeof(Date) * n); 

    Date placeholder;
    for (size_t i = 0; i < n; ++i) {
        scanf("%d %d %d", &placeholder.Year, &placeholder.Month, &placeholder.Day);
        data[i] = placeholder;
    }
    radix_sort(data, res, n);
    
    putc('\n', stdout);
    for (size_t i = 0; i < n; ++i) {
        print_date(res[i]);
        putc('\n', stdout);
    }

    return 0;
}