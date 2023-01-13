#include "csort_utils.h"
#include "unity.h"
#include <string.h>

void setUp() {}
void tearDown() {}


#define generate_wcount_test(str_literal, expected_wc, expected_trimmed_length) do { \
    size_t trimmed_length, wc; \
    TEST_ASSERT_FALSE(wcount(str_literal, strlen(str_literal), &wc, &trimmed_length)); \
    TEST_ASSERT_EQUAL((expected_wc), wc); \
    TEST_ASSERT_EQUAL((expected_trimmed_length), trimmed_length); \
} while(0)


void test_word_count() {
    generate_wcount_test("",                       0, 0);
    generate_wcount_test("1",                      1, 1);
    generate_wcount_test("     145",               1, 3);
    generate_wcount_test("123    ",                1, 3);
    generate_wcount_test("123    3213",            2, 8);
    generate_wcount_test("   123    3213",         2, 8);
    generate_wcount_test("123    3213      ",      2, 8);
    generate_wcount_test("     123    3213      ", 2, 8);
}

#define generate_string_reduction_test(str_lit, expected_lit) do { \
    char *res; \
    TEST_ASSERT_FALSE(reduce_string(str_lit, strlen(str_lit), &res)); \
    TEST_ASSERT_EQUAL(strlen(expected_lit), strlen(res)); \
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_lit, res, strlen(expected_lit)); \
    free(res); \
} while(0)


void test_string_reduction() {
    generate_string_reduction_test("1",                      "1");
    generate_string_reduction_test("     145",               "145");
    generate_string_reduction_test("123    ",                "123");
    generate_string_reduction_test("123    3213",            "123 3213");
    generate_string_reduction_test("   123    3213",         "123 3213");
    generate_string_reduction_test("123    3213      ",      "123 3213");
    generate_string_reduction_test("     123    3213      ", "123 3213");
}


void test_index_table_gen() {
    {
        char *given = "1";
        size_t given_wc = 1;
        size_t *res;
        TEST_ASSERT_FALSE(compute_index_table(given, strlen(given), given_wc, &res));
        size_t expected_res[] = {0, 1};
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_res, res, sizeof(expected_res) / sizeof(size_t));    
    }
    {
        char *given = "1 2";
        size_t given_wc = 2;
        size_t *res;
        TEST_ASSERT_FALSE(compute_index_table(given, strlen(given), given_wc, &res));
        size_t expected_res[] = {0, 1, 3};
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_res, res, sizeof(expected_res) / sizeof(size_t));    
    }
    {
        char *given = "1 2 345";
        size_t given_wc = 3;
        size_t *res;
        TEST_ASSERT_FALSE(compute_index_table(given, strlen(given), given_wc, &res));
        size_t expected_res[] = {0, 1, 3, 7};
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_res, res, sizeof(expected_res) / sizeof(size_t));    
    }
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_word_count);
    RUN_TEST(test_string_reduction);
    RUN_TEST(test_index_table_gen);

    return UNITY_END();
}