add_executable(heapsort_tests tests.c)
target_link_libraries(heapsort_tests
                      libheap
                      Unity)
add_test(heapsort_tests heapsort_tests)
