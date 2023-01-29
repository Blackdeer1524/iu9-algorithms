#define DEBUG_
#include "unity.h"
#include "log_table.h"


extern inline void table_free(LogTable *table);
extern inline table_item_t get_item(LogTable *table, size_t row, size_t col);
extern inline void set_item(LogTable *table, size_t row, size_t col, table_item_t item);


LogTable *table;

void setUp(void) {
    table = table_build(3);
    TEST_ASSERT_TRUE(table != NULL);
    table->data[0][0] = 3;
    table->data[0][1] = 6;
    table->data[0][2] = 2;
    table->data[1][0] = 3;
    table->data[1][1] = 2;
}

void tearDown(void) {
    table_free(table);
}


void test_get_item(void) {
    TEST_ASSERT_EQUAL(3, get_item(table, 0, 0));
    TEST_ASSERT_EQUAL(6, get_item(table, 0, 1));
    TEST_ASSERT_EQUAL(2, get_item(table, 0, 2));
    TEST_ASSERT_EQUAL(3, get_item(table, 1, 0));
    TEST_ASSERT_EQUAL(2, get_item(table, 1, 1));
}


void test_set_item(void) {
    set_item(table, 0, 0, 5);
    TEST_ASSERT_EQUAL(5, get_item(table, 0, 0));

    set_item(table, 0, 1, 5);
    TEST_ASSERT_EQUAL(5, get_item(table, 0, 1));

    set_item(table, 0, 2, 5);
    TEST_ASSERT_EQUAL(5, get_item(table, 0, 2));

    set_item(table, 1, 0, 5);
    TEST_ASSERT_EQUAL(5, get_item(table, 1, 0));

    set_item(table, 1, 1, 5);
    TEST_ASSERT_EQUAL(5, get_item(table, 1, 1));
}



int main() {
    UNITY_BEGIN();

    RUN_TEST(test_get_item);
    RUN_TEST(test_set_item);

    return UNITY_END();
}