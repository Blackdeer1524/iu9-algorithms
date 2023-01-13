add_executable(prefixes_tests tests.c)
target_link_libraries(prefixes_tests
                      libprefix
                      Unity)
add_test(prefixes_tests prefixes_tests)
