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
    size_t *log2_table = precompute_log2(8); 
    TEST_ASSERT_EQUAL(0, log2_table[0]);
    TEST_ASSERT_EQUAL(0, log2_table[1]);
    TEST_ASSERT_EQUAL(1, log2_table[2]);
    TEST_ASSERT_EQUAL(1, log2_table[3]);
    TEST_ASSERT_EQUAL(2, log2_table[4]);
    TEST_ASSERT_EQUAL(2, log2_table[5]);
    TEST_ASSERT_EQUAL(2, log2_table[6]);
    TEST_ASSERT_EQUAL(2, log2_table[7]);
    TEST_ASSERT_EQUAL(3, log2_table[8]);
    free(log2_table);
}



int main() {
    UNITY_BEGIN();

    RUN_TEST(test_gcd);
    RUN_TEST(test_log2);

    return UNITY_END();
}