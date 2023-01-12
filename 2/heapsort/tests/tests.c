#include <unity.h>
#include "heap.h"


int int_cmp(const int *l, const int *r) {
    int cmpres = *l - *r;
    if (cmpres > 0) {
        return 1;
    } else if (cmpres < 0) {
        return -1;
    } 
    return 0;
}


void setUp() {}
void tearDown() {}


int assert_max_heap_property(void *base,
                             size_t nel,
                             size_t width,
                             int (*compare)(const void *a, const void *b)) {
    if (nel <= 1) {
        return 0;
    }

    for (size_t i = 0; i <= parent(nel - 1); ++i) {
        size_t left_child_index = left(i);
        size_t right_child_index = right(i);

        void *parent_value = get_item_ptr(base, width, i);
        if (left_child_index < nel) {
            if (compare(parent_value, get_item_ptr(base, width, left_child_index)) < 0) {
                return 1;
            }
        }

        if (right_child_index < nel) {
            if (compare(parent_value, get_item_ptr(base, width, right_child_index)) < 0) {
                return 1;
            }
        }
    }

    return 0;
}


#define generate_max_heap_test(array_type, array, cmp_func, outcome) do { \
    TEST_ASSERT_ ## outcome(assert_max_heap_property(array, sizeof(array) / sizeof(array_type), sizeof(array_type), cmp_func)); \
} while(0)

void test_max_heapify(void) {
    int arr_1[] = {1};
    generate_max_heap_test(int, arr_1, (int (*)(const void *, const void *)) int_cmp, FALSE);

    int arr_0[] = {};
    generate_max_heap_test(int, arr_0, (int (*)(const void *, const void *)) int_cmp, FALSE);

    int arr_9[] = {10, 3, 5, 1, 2, 3, 3, 1, 1};
    generate_max_heap_test(int, arr_9, (int (*)(const void *, const void *)) int_cmp, FALSE);

    int arr_3[] = {10, 7, 11};
    generate_max_heap_test(int, arr_3, (int (*)(const void *, const void *)) int_cmp, TRUE);

    int arr_7[] = {10, 5, 6, 5, 4, 7, 5};
    generate_max_heap_test(int, arr_7, (int (*)(const void *, const void *)) int_cmp, TRUE);
    
    int arr_10[] = {10, 3, 5, 1, 2, 3, 3, 10};
    generate_max_heap_test(int, arr_10, (int (*)(const void *, const void *)) int_cmp, TRUE);
}


int assert_sorted(void *base,
                  size_t nel,
                  size_t width,
                  int (*compare)(const void *a, const void *b)) {
    if (nel <= 1) {
        return 0;
    }

    int left_val =  *((int *) get_item_ptr(base, width, 0));
    for (size_t i=1; i<nel; ++i) {
        int current = *(int *) get_item_ptr(base, width, i);
        if (current < left_val) {
            return 1;
        }
        left_val = current;
    }
    return 0;
}  

#define generate_hsort_test(array_type, array, cmp_func, outcome) do { \
    hsort(array, sizeof(array) / sizeof(array_type), sizeof(array_type), cmp_func); \
    TEST_ASSERT_ ## outcome(assert_sorted(array, sizeof(array) / sizeof(array_type), sizeof(array_type), cmp_func)); \
} while(0)


void test_hsort(void) {
    int arr_1[] = {1};
    generate_hsort_test(int, arr_1, (int (*)(const void *, const void *)) int_cmp, FALSE);

    int arr_0[] = {};
    generate_hsort_test(int, arr_0, (int (*)(const void *, const void *)) int_cmp, FALSE);

    int arr_9[] = {10, 3, 5, 1, 2, 3, 3, 1, 1};
    generate_hsort_test(int, arr_9, (int (*)(const void *, const void *)) int_cmp, FALSE);

    int arr_3[] = {10, 7, 11};
    generate_hsort_test(int, arr_3, (int (*)(const void *, const void *)) int_cmp, FALSE);

    int arr_7[] = {10, 5, 6, 5, 4, 7, 5};
    generate_hsort_test(int, arr_7, (int (*)(const void *, const void *)) int_cmp, FALSE);
    
    int arr_10[] = {10, 3, 5, 1, 2, 3, 3, 10};
    generate_hsort_test(int, arr_10, (int (*)(const void *, const void *)) int_cmp, FALSE);
}


int main( ) {
    UNITY_BEGIN();

    RUN_TEST(test_max_heapify);
    RUN_TEST(test_hsort);

    return UNITY_END();
}