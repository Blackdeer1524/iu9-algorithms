#define DEBUG_
#include "unity.h"
#include "table.h"


Table table;

void setUp(void) {
    table = table_build(3, 3);
    table.data[0] = 3;
    table.data[1] = 1;
    table.data[2] = 1;
    table.data[3] = 2;
    table.data[4] = 2;
    table.data[5] = 6;
}

void tearDown(void) {
    table_free(&table);
}


void test_get_item(void) {
    TEST_ASSERT_EQUAL(3, get_item(&table, 0, 0));
    TEST_ASSERT_EQUAL(1, get_item(&table, 0, 1));
    TEST_ASSERT_EQUAL(1, get_item(&table, 0, 2));
    TEST_ASSERT_EQUAL(2, get_item(&table, 1, 1));
    TEST_ASSERT_EQUAL(6, get_item(&table, 1, 2));
}


void test_set_item(void) {
    set_item(&table, 0, 0, 5);
    TEST_ASSERT_EQUAL(5, get_item(&table, 0, 0));

    set_item(&table, 0, 1, 5);
    TEST_ASSERT_EQUAL(5, get_item(&table, 0, 1));

    set_item(&table, 0, 2, 5);
    TEST_ASSERT_EQUAL(5, get_item(&table, 0, 2));

    set_item(&table, 1, 1, 5);
    TEST_ASSERT_EQUAL(5, get_item(&table, 1, 1));

    set_item(&table, 1, 2, 5);
    TEST_ASSERT_EQUAL(5, get_item(&table, 1, 2));
}



int main() {
    UNITY_BEGIN();

    RUN_TEST(test_get_item);
    RUN_TEST(test_set_item);

    return UNITY_END();
}