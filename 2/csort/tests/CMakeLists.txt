add_executable(csort_tests tests.c)
target_link_libraries(csort_tests
                      csort_utils
                      Unity)
add_test(csort_tests csort_tests)
