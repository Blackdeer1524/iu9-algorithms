#include "unity.h"
#include "segment_tree.h"

void setUp() {}
void tearDown() {}


void are_identical(Node *expected, Node *given) {
    if (expected == NULL || given == NULL) {
        TEST_ASSERT_EQUAL(expected, given);
        return;
    }
    TEST_ASSERT_EQUAL(expected->r_bound, given->r_bound);
    TEST_ASSERT_EQUAL(expected->l_bound, given->l_bound);
    TEST_ASSERT_EQUAL(expected->leftmost_info.value, given->leftmost_info.value);
    TEST_ASSERT_EQUAL(expected->leftmost_info.is_peak, given->leftmost_info.is_peak);
    TEST_ASSERT_EQUAL(expected->rightmost_info.value, given->rightmost_info.value);
    TEST_ASSERT_EQUAL(expected->rightmost_info.is_peak, given->rightmost_info.is_peak);

    are_identical(expected->l_child, given->l_child);
    are_identical(expected->r_child, given->r_child);
}


#define new_Node(dst_ptr, \
                 _peak_count, _l_bound, _r_bound, \
                 _leftmost_info_value, _leftmost_info_is_peak, \
                 _rightmost_info_value, _rightmost_info_is_peak, \
                 _left_child, _right_child) \
    do { \
        BorderInfo _leftmost_info = { \
        .value = _leftmost_info_value, \
        .is_peak = _leftmost_info_is_peak, \
        };\
        BorderInfo _rightmost_info = { \
        .value = _rightmost_info_value, \
        .is_peak = _rightmost_info_is_peak \
        };\
        dst_ptr->peak_count     = _peak_count; \
        dst_ptr->l_bound        = _l_bound; \
        dst_ptr->r_bound        = _r_bound; \
        \
        dst_ptr->leftmost_info  = _leftmost_info; \
        dst_ptr->rightmost_info = _rightmost_info; \
        \
        dst_ptr->parent         = NULL; \
        dst_ptr->l_child        = _left_child; \
        dst_ptr->r_child        = _right_child; \
    } while(0)


void test_tree_build(void) {
    int given[6] = {1, 1, 2, 1, 0, 1};

    Node *ll = malloc(sizeof(Node));
    new_Node(ll, 1, 0, 0, given[0], true, given[0], true, NULL, NULL);

    Node *lrl = malloc(sizeof(Node));;
    new_Node(lrl, 1, 1, 1, given[1], true, given[1], true, NULL, NULL);

    Node *lrr = malloc(sizeof(Node));;
    new_Node(lrr, 1, 2, 2, given[2], true, given[2], true, NULL, NULL);

    Node *lr = malloc(sizeof(Node));;
    new_Node(lr, 1, 1, 2, given[1], false, given[2], true, lrl, lrr);

    lrl->parent = lr;
    lrr->parent = lr;

    Node *l = malloc(sizeof(Node));;
    new_Node(l, 2, 0, 2, given[0], true, given[2], true, ll, lr);

    ll->parent = l;
    lr->parent = l;
    
    Node *rl = malloc(sizeof(Node));;
    new_Node(rl, 1, 3, 3, given[3], true, given[3], true, NULL, NULL);

    Node *rrl = malloc(sizeof(Node));;
    new_Node(rrl, 1, 4, 4, given[4], true, given[4], true, NULL, NULL);

    Node *rrr = malloc(sizeof(Node));;
    new_Node(rrr, 1, 5, 5, given[5], true, given[5], true, NULL, NULL);

    Node *rr = malloc(sizeof(Node));;
    new_Node(rr, 1, 4, 5, given[4], false, given[5], true, rrl, rrr);

    rrl->parent = rr;
    rrr->parent = rr;

    Node *r = malloc(sizeof(Node));;
    new_Node(r, 2, 3, 5, given[3], true, given[5], true, rl, rr);

    rl->parent = r;
    rr->parent = r;

    Node *root = malloc(sizeof(Node));;
    new_Node(root, 3, 0, 5, given[0], true, given[5], true, l, r);
    l->parent = root;
    r->parent = root;

    Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));
    are_identical(root, built_tree);
    free_segment_tree(built_tree);
    free_segment_tree(root);
}


void test_get_peak_count(void) { 
    {
        int given[] = {1, 1, 2, 1, 0, 1};
        Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));

        bool error = false;
        TEST_ASSERT_EQUAL(1, get_peak_count(built_tree, 0, 0, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(2, get_peak_count(built_tree, 0, 2, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(2, get_peak_count(built_tree, 0, 3, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(1, get_peak_count(built_tree, 1, 3, &error));
        TEST_ASSERT_FALSE(error);

        TEST_ASSERT_EQUAL(2, get_peak_count(built_tree, 3, 5, &error));
        TEST_ASSERT_FALSE(error);

        free_segment_tree(built_tree);
    }
    {
        int given[] = {-893, 623, 44, 317, -422, -385, -733, -988, 18, 595};
        Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));
        
        bool error = false;
        TEST_ASSERT_EQUAL(1, get_peak_count(built_tree, 4, 7, &error));
        TEST_ASSERT_FALSE(error);

        free_segment_tree(built_tree);
    }

}


void test_update(void) {
    int given[] = {1, 1, 2, 1, 0, 1};
    Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));

    bool error = false;
    TEST_ASSERT_EQUAL(2, get_peak_count(built_tree, 0, 3, &error));
    TEST_ASSERT_FALSE(error);

    TEST_ASSERT_FALSE(update(built_tree, 2, 1));
    TEST_ASSERT_EQUAL(4, get_peak_count(built_tree, 0, 3, &error));
    TEST_ASSERT_FALSE(error);

    TEST_ASSERT_FALSE(update(built_tree, 2, 0));
    TEST_ASSERT_EQUAL(3, get_peak_count(built_tree, 0, 3, &error));
    TEST_ASSERT_FALSE(error);

    free_segment_tree(built_tree);
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_tree_build);
    RUN_TEST(test_get_peak_count);
    RUN_TEST(test_update);

    return UNITY_END();
}