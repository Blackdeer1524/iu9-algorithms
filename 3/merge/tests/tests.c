#define UNIT_TEST 1
#include "unity.h"
#include "heap.h"


void setUp(void) {} 

void tearDown(void) {}


void test_min_heap_property(Heap *heap) {
    for (size_t i = heap->length - 1; i > 0; --i) {
        TEST_ASSERT_LESS_OR_EQUAL(heap->data[i].item, heap->data[parent(i)].item);
    }
}

void test_min_heap(void) {
    {
        bool error = false;
        Heap heap = build_heap(2, &error);
        TEST_ASSERT_FALSE(error);

        int test_values[] = {1, 2};
        for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i) {
            HeapItem t = {.item = test_values[i], .source_index = 0};
            TEST_ASSERT_FALSE(insert(&heap, t));
        }
        
        test_min_heap_property(&heap);
    }
    {
        bool error = false;
        Heap heap = build_heap(5, &error);
        TEST_ASSERT_FALSE(error);

        int test_values[] = {5, 4, 3, 2, 1};
        for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i) {
            HeapItem t = {.item = test_values[i], .source_index = 0};
            TEST_ASSERT_FALSE(insert(&heap, t));
        }
        
        test_min_heap_property(&heap);
    }
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_min_heap);

    return UNITY_END();
}