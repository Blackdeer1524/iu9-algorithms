#include "unity.h"
#include "math_utils.h"


void setUp(void) {}

void tearDown(void) {}

void test_gcd(void) {
    TEST_ASSERT_EQUAL(0, gcd(0, 0));
    TEST_ASSERT_EQUAL(3, gcd(0, 3));
    TEST_ASSERT_EQUAL(3, gcd(3, 0));
    TEST_ASSERT_EQUAL(3, gcd(6, 3));
    TEST_ASSERT_EQUAL(3, gcd(3, 6));
    TEST_ASSERT_EQUAL(1, gcd(5, 11));
}


void test_log2(void) {
    TEST_ASSERT_EQUAL(0, int_log2(1));
    TEST_ASSERT_EQUAL(1, int_log2(2));
    TEST_ASSERT_EQUAL(1, int_log2(3));
    TEST_ASSERT_EQUAL(2, int_log2(4));
    TEST_ASSERT_EQUAL(2, int_log2(7));
    TEST_ASSERT_EQUAL(3, int_log2(15));
    TEST_ASSERT_EQUAL(4, int_log2(16));
}



int main() {
    UNITY_BEGIN();

    RUN_TEST(test_gcd);
    RUN_TEST(test_log2);

    return UNITY_END();
}