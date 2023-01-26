#define UNIT_TEST 1
#include "unity.h"
#include "heap.h"


void setUp(void) {} 

void tearDown(void) {}


void assert_min_heap_property(Heap *heap) {
    if (heap->length <= 1) {
        return;
    }

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
        
        assert_min_heap_property(&heap);
        free(heap.data);
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
        
        assert_min_heap_property(&heap);
        free(heap.data);
    }
}


void test_get_min(void) {
    {
        bool error = false;
        Heap heap = build_heap(5, &error);
        TEST_ASSERT_FALSE(error);

        int test_values[] = {5, 4, 3, 2, 1};
        for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i) {
            HeapItem t = {.item = test_values[i], .source_index = 0};
            TEST_ASSERT_FALSE(insert(&heap, t));
        }
    
        int res;
        res = get_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(1, res);
        res = pop_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(1, res);

        res = get_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(2, res);
        res = pop_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(2, res);

        res = get_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(3, res);
        res = pop_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(3, res);

        res = get_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(4, res);
        res = pop_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(4, res);

        res = get_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(5, res);
        res = pop_minimum(&heap, &error).item;
        TEST_ASSERT_FALSE(error);
        TEST_ASSERT_EQUAL(5, res);

        pop_minimum(&heap, &error);
        TEST_ASSERT_TRUE(error);

        error = false;
        get_minimum(&heap, &error);
        TEST_ASSERT_TRUE(error);

        assert_min_heap_property(&heap);
        free(heap.data);
    }
} 


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_min_heap);
    RUN_TEST(test_get_min);

    return UNITY_END();
}