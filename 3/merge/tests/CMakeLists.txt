add_executable(merge_tests tests.c)
target_link_libraries(merge_tests
                      Unity
                      libheap)
add_test(merge_tests merge_tests)
