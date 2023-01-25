#include "unity.h"
#include "segment_tree.h"

void setUp() {}
void tearDown() {}


void test_gcd(void) { 
    TEST_ASSERT_EQUAL(1, gcd(1, 0));
    TEST_ASSERT_EQUAL(1, gcd(0, 1));

    TEST_ASSERT_EQUAL(3, gcd(6, 3));
    TEST_ASSERT_EQUAL(3, gcd(3, 6));

    TEST_ASSERT_EQUAL(1, gcd(5, 11));
}


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


// void test_tree_build(void) {
//     int given[4] = {4, 9, 13, 18};

//     Node ll = {
//         .l_bound=0,
//         .r_bound=0,
//         .l_child=NULL,
//         .r_child=NULL,
//         .value=4};

//     Node lr = {
//         .l_bound=1,
//         .r_bound=1,
//         .l_child=NULL,
//         .r_child=NULL,
//         .value=9};

//     Node l = {
//         .l_bound=0,
//         .r_bound=1,
//         .l_child=&ll,
//         .r_child=&lr,
//         .value=9};

//     ll.parent = &l;
//     lr.parent = &l;

//     Node rl = {
//         .l_bound=2,
//         .r_bound=2,
//         .l_child=NULL,
//         .r_child=NULL,
//         .value=13};

//     Node rr = {
//         .l_bound=3,
//         .r_bound=3,
//         .l_child=NULL,
//         .r_child=NULL,
//         .value=18};

//     Node r = {
//         .l_bound=2,
//         .r_bound=3,
//         .l_child=&rl,
//         .r_child=&rr,
//         .value=18};

//     rl.parent = &r;
//     rr.parent = &r;

//     Node root = {
//         .l_bound=0,
//         .r_bound=3,
//         .value=18,
//         .parent=NULL,
//         .l_child=&l,
//         .r_child=&r,
//         };

//     l.parent = &root;
//     r.parent = &root;

//     Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));
//     are_identical(&root, built_tree);
//     free_segment_tree(built_tree);
// }


void test_interval_gcd(void) { 
                // 0  1  2  3   4    5
    int given[] = {2, 4, 8, 9, -13, 26};
    Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));

    TEST_ASSERT_EQUAL(2, interval_gcd(built_tree, 0, 1));
    TEST_ASSERT_EQUAL(2, interval_gcd(built_tree, 0, 2));
    TEST_ASSERT_EQUAL(4, interval_gcd(built_tree, 1, 2));
    TEST_ASSERT_EQUAL(1, interval_gcd(built_tree, 2, 3));
    TEST_ASSERT_EQUAL(13, interval_gcd(built_tree, 4, 5));

    free_segment_tree(built_tree);
}


void test_update(void) {    
    int given[] = {2, 4, 8, 9, -13, 26};
    Node *built_tree = build_segment_tree(given, sizeof(given) / sizeof(given[0]));

    TEST_ASSERT_EQUAL(1, interval_gcd(built_tree, 2, 3));
    TEST_ASSERT_FALSE(update(built_tree, 2, -18));
    TEST_ASSERT_EQUAL(9, interval_gcd(built_tree, 2, 3));

    free_segment_tree(built_tree);
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_gcd);
    // RUN_TEST(test_tree_build);
    RUN_TEST(test_interval_gcd);
    RUN_TEST(test_update);

    return UNITY_END();
}