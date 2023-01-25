#define DEBUG_
#include "unity.h"
#include "gcd_matrix.h"



extern inline Table table_build(size_t n_rows, size_t n_cols);
extern inline void table_free(Table *table);
extern inline size_t _get_index(Table *table, size_t row, size_t col);
extern inline table_item_t get_item(Table *table, size_t row, size_t col);
extern inline void set_item(Table *table, size_t row, size_t col, table_item_t item);



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


void test_gcd_matrix(void) {
    table_item_t array[9] = {-3, 1, 5, 10, 13, 26, -52, 0, 10};
    bool error = false;
    Table gcd_table = get_gcd_table(array, sizeof(array) / sizeof(array[0]), &error);
    TEST_ASSERT_FALSE(error);
    TEST_ASSERT_EQUAL(1, get_item(&gcd_table, 3, 0));
    TEST_ASSERT_EQUAL(10, get_item(&gcd_table, 3, 1));

    TEST_ASSERT_EQUAL(1, get_item(&gcd_table,  2, 0));
    TEST_ASSERT_EQUAL(13, get_item(&gcd_table, 2, 1));
    TEST_ASSERT_EQUAL(10, get_item(&gcd_table, 2, 2));

    TEST_ASSERT_EQUAL(1, get_item(&gcd_table,  1, 0));
    TEST_ASSERT_EQUAL(5, get_item(&gcd_table,  1, 1));
    TEST_ASSERT_EQUAL(13, get_item(&gcd_table, 1, 2));
    TEST_ASSERT_EQUAL(52, get_item(&gcd_table, 1, 3));
    TEST_ASSERT_EQUAL(10, get_item(&gcd_table, 1, 4));

    TEST_ASSERT_EQUAL(3, get_item(&gcd_table,  0, 0));
    TEST_ASSERT_EQUAL(1, get_item(&gcd_table,  0, 1));
    TEST_ASSERT_EQUAL(5, get_item(&gcd_table,  0, 2));
    TEST_ASSERT_EQUAL(10, get_item(&gcd_table, 0, 3));
    TEST_ASSERT_EQUAL(13, get_item(&gcd_table, 0, 4));
    TEST_ASSERT_EQUAL(26, get_item(&gcd_table, 0, 5));
    TEST_ASSERT_EQUAL(52, get_item(&gcd_table, 0, 6));
    TEST_ASSERT_EQUAL(0, get_item(&gcd_table,  0, 7));
    TEST_ASSERT_EQUAL(10, get_item(&gcd_table, 0, 8));
    
    table_free(&gcd_table);
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_gcd);
    RUN_TEST(test_log2);
    RUN_TEST(test_gcd_matrix);

    return UNITY_END();
}