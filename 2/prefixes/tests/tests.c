#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "prefix.h"


void setUp() {}
void tearDown() {}


void test_prefix_table_building(void) {
    {
        char given[] = "asdfghjk";
        size_t expected[] = {0};
        size_t *res;
        TEST_ASSERT_FALSE(build_prefix_table(given, strlen(given), &res));
        TEST_ASSERT_EQUAL_INT64_ARRAY(expected, res, sizeof(expected) / sizeof(size_t));
        free(res);
    }
    {
        char given[] = "aa";
        size_t expected[] = {0, 1};
        size_t *res;
        TEST_ASSERT_FALSE(build_prefix_table(given, strlen(given), &res));
        TEST_ASSERT_EQUAL_INT64_ARRAY(expected, res, sizeof(expected) / sizeof(size_t));
        free(res);
    }
    {
        char given[] = "123123";
        size_t expected[] = {0, 0, 0, 1, 2, 3};
        size_t *res;
        TEST_ASSERT_FALSE(build_prefix_table(given, strlen(given), &res));
        TEST_ASSERT_EQUAL_INT64_ARRAY(expected, res, sizeof(expected) / sizeof(size_t));
        free(res);
    }
    {
        char given[] = "ababcabababc";
                          // a  b  a  b  c  a  b  a  b  a  b  c
        size_t expected[] = {0, 0, 1, 2, 0, 1, 2, 3, 4, 3, 4, 5};
        size_t *res;
        TEST_ASSERT_FALSE(build_prefix_table(given, strlen(given), &res));
        TEST_ASSERT_EQUAL_INT64_ARRAY(expected, res, sizeof(expected) / sizeof(size_t));
        free(res);
    }
}


void test_gcd(void) { 
    TEST_ASSERT_EQUAL(1, gcd(1, 3));
    TEST_ASSERT_EQUAL(3, gcd(3, 3));
    TEST_ASSERT_EQUAL(3, gcd(3, 6));
    TEST_ASSERT_EQUAL(3, gcd(6, 3));
    TEST_ASSERT_EQUAL(1, gcd(5, 6));
    TEST_ASSERT_EQUAL(1, gcd(6, 5));
    TEST_ASSERT_EQUAL(6, gcd(18, 12));
    TEST_ASSERT_EQUAL(6, gcd(12, 18));
    TEST_ASSERT_EQUAL(1, gcd(0, 1));
    TEST_ASSERT_EQUAL(1, gcd(1, 0));
}



int main() {
    UNITY_BEGIN();

    RUN_TEST(test_prefix_table_building);
    RUN_TEST(test_gcd);

    return UNITY_END();
}