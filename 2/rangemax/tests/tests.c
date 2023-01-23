#include "unity.h"
#include "segment_tree.h"

void setUp() {}
void tearDown() {}


void is_identical(Node *expected, Node *given) {
    if (expected == NULL || given == NULL) {
        TEST_ASSERT_EQUAL(expected, given);
        return;
    }
    TEST_ASSERT_EQUAL(expected->r_bound, given->r_bound);
    TEST_ASSERT_EQUAL(expected->l_bound, given->l_bound);
    TEST_ASSERT_EQUAL(expected->value, given->value);
    is_identical(expected->l_child, given->l_child);
    is_identical(expected->r_child, given->r_child);
}


void test_tree_build(void) {
    int given[4] = {4, 9, 13, 18};

    Node ll = {
        .l_bound=0,
        .r_bound=0,
        .l_child=NULL,
        .r_child=NULL,
        .value=4};

    Node lr = {
        .l_bound=1,
        .r_bound=1,
        .l_child=NULL,
        .r_child=NULL,
        .value=9};

    Node l = {
        .l_bound=0,
        .r_bound=1,
        .l_child=&ll,
        .r_child=&lr,
        .value=9};

    ll.parent = &l;
    lr.parent = &l;

    Node rl = {
        .l_bound=2,
        .r_bound=2,
        .l_child=NULL,
        .r_child=NULL,
        .value=13};

    Node rr = {
        .l_bound=3,
        .r_bound=3,
        .l_child=NULL,
        .r_child=NULL,
        .value=18};

    Node r = {
        .l_bound=2,
        .r_bound=3,
        .l_child=&rl,
        .r_child=&rr,
        .value=18};

    rl.parent = &r;
    rr.parent = &r;

    Node root = {
        .l_bound=0,
        .r_bound=3,
        .value=18,
        .parent=NULL,
        .l_child=&l,
        .r_child=&r,
        };

    l.parent = &root;
    r.parent = &root;

    Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));
    is_identical(&root, built_tree);
    free_segment_tree(built_tree);
}


void test_get_max(void) { 
    int given[4] = {4, 9, 13, 18};
    Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));

    bool error = false;
    TEST_ASSERT_EQUAL(18, get_max(built_tree, 0, 3, &error));
    TEST_ASSERT_FALSE(error);

    TEST_ASSERT_EQUAL(13, get_max(built_tree, 1, 2, &error));
    TEST_ASSERT_FALSE(error);

    TEST_ASSERT_EQUAL(4, get_max(built_tree, 0, 0, &error));
    TEST_ASSERT_FALSE(error);

    free_segment_tree(built_tree);
}



int main() {
    UNITY_BEGIN();

    RUN_TEST(test_tree_build);
    RUN_TEST(test_get_max);

    return UNITY_END();
}