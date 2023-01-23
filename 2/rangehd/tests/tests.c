#include <stdlib.h>
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
    TEST_ASSERT_EQUAL(expected->value, given->value);
    are_identical(expected->l_child, given->l_child);
    are_identical(expected->r_child, given->r_child);
}


void test_tree_build(void) {
    char given[] = "abca";

    Node ll = {
        .l_bound=0,
        .r_bound=0,
        .l_child=NULL,
        .r_child=NULL,
        .value=0b1};

    Node lr = {
        .l_bound=1,
        .r_bound=1,
        .l_child=NULL,
        .r_child=NULL,
        .value=0b10};

    Node l = {
        .l_bound=0,
        .r_bound=1,
        .l_child=&ll,
        .r_child=&lr,
        .value=0b11};

    ll.parent = &l;
    lr.parent = &l;

    Node rl = {
        .l_bound=2,
        .r_bound=2,
        .l_child=NULL,
        .r_child=NULL,
        .value=0b100};

    Node rr = {
        .l_bound=3,
        .r_bound=3,
        .l_child=NULL,
        .r_child=NULL,
        .value=0b1};

    Node r = {
        .l_bound=2,
        .r_bound=3,
        .l_child=&rl,
        .r_child=&rr,
        .value=0b101};

    rl.parent = &r;
    rr.parent = &r;

    Node root = {
        .l_bound=0,
        .r_bound=3,
        .value=0b110,  // 0b011 ^ 0b101,
        .parent=NULL,
        .l_child=&l,
        .r_child=&r,
        };

    l.parent = &root;
    r.parent = &root;

    Node *built_tree = build_segment_tree(given);
    are_identical(&root, built_tree);
    free_segment_tree(built_tree);
}


void test_is_hyperdrome(void) {
    Node *root = build_segment_tree("abcab");
    
    bool error = false;
    TEST_ASSERT_TRUE(is_hyperdrome(root, 0, 4, &error));
    TEST_ASSERT_FALSE(error);

    TEST_ASSERT_FALSE(is_hyperdrome(root, 1, 4, &error));
    TEST_ASSERT_FALSE(error);
    free_segment_tree(root);
}


void test_update(void) {
    Node *root = build_segment_tree("abcdcaq");

    bool error = false;
    TEST_ASSERT_FALSE(is_hyperdrome(root, 0, 6, &error));
    TEST_ASSERT_FALSE(error);

    update(root, 4, "abc");
    TEST_ASSERT_TRUE(is_hyperdrome(root, 0, 6, &error));
    TEST_ASSERT_FALSE(error);
    free_segment_tree(root);

    root = build_segment_tree("bcqtrccb");
    TEST_ASSERT_FALSE(is_hyperdrome(root, 0, 7, &error));
    TEST_ASSERT_FALSE(error);

    update(root, 2, "ccbb");
    TEST_ASSERT_TRUE(is_hyperdrome(root, 0, 7, &error));
    TEST_ASSERT_FALSE(error);
    free_segment_tree(root);
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_tree_build);
    RUN_TEST(test_is_hyperdrome);
    RUN_TEST(test_update);

    return UNITY_END();
}