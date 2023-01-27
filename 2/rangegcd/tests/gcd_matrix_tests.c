#define DEBUG_
#include "unity.h"
#include "gcd_matrix.h"


// extern inline LogTable table_build(size_t n_rows, size_t n_cols);
extern inline void table_free(LogTable *table);
extern inline table_item_t get_item(LogTable *table, size_t row, size_t col);
extern inline void set_item(LogTable *table, size_t row, size_t col, table_item_t item);


void setUp(void) {}

void tearDown(void) {}


void test_gcd_matrix(void) {
    {
        table_item_t array[1] = {3};
        bool error = false;
        LogTable gcd_table = get_gcd_table(array, sizeof(array) / sizeof(array[0]), &error);
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(3, get_item(&gcd_table, 0, 0));

        table_free(&gcd_table);
    }
    {
        table_item_t array[2] = {-3, 9};
        bool error = false;
        LogTable gcd_table = get_gcd_table(array, sizeof(array) / sizeof(array[0]), &error);
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(3, get_item(&gcd_table, 0, 0));
        TEST_ASSERT_EQUAL(9, get_item(&gcd_table, 0, 1));

        table_free(&gcd_table);
    }
    {   
        table_item_t array[9] = {-3, 1, 5, 10, 13, 26, -52, 0, 10};
        bool error = false;
        LogTable gcd_table = get_gcd_table(array, sizeof(array) / sizeof(array[0]), &error);
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
}


void test_interval_gcd(void) {
    {
        table_item_t array[1] = {3};
        bool error = false;
        LogTable gcd_table = get_gcd_table(array, sizeof(array) / sizeof(array[0]), &error);
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(3, interval_gcd(&gcd_table, 0, 0, &error));
        TEST_ASSERT_FALSE(error);

        table_free(&gcd_table);
    }
    {
        table_item_t array[2] = {-3, 9};
        bool error = false;
        LogTable gcd_table = get_gcd_table(array, sizeof(array) / sizeof(array[0]), &error);

        TEST_ASSERT_EQUAL(3, interval_gcd(&gcd_table, 0, 0, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(9, interval_gcd(&gcd_table, 1, 1, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(3, interval_gcd(&gcd_table, 0, 1, &error));
        TEST_ASSERT_FALSE(error);
        
        table_free(&gcd_table);
    }

    {
        table_item_t array[9] = {-3, 1, 5, 10, 13, 26, -52, 0, 10};
        bool error = false;
        LogTable gcd_table = get_gcd_table(array, sizeof(array) / sizeof(array[0]), &error);
        TEST_ASSERT_FALSE(error);
        
        TEST_ASSERT_EQUAL(1, interval_gcd(&gcd_table, 1, 1, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(1, interval_gcd(&gcd_table, 0, 1, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(10, interval_gcd(&gcd_table, 8, 8, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(10, interval_gcd(&gcd_table, 7, 8, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(1, interval_gcd(&gcd_table, 0, 8, &error));
        TEST_ASSERT_FALSE(error);
        
        TEST_ASSERT_EQUAL(13, interval_gcd(&gcd_table, 4, 7, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(2, interval_gcd(&gcd_table, 6, 9, &error));
        TEST_ASSERT_FALSE(error);

        table_free(&gcd_table);
    }
}


int main() {
    UNITY_BEGIN();

    // RUN_TEST(test_gcd);
    // RUN_TEST(test_log2);
    // RUN_TEST(test_gcd_matrix);
    // RUN_TEST(test_interval_gcd);

    return UNITY_END();
}