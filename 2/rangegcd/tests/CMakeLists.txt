add_executable(rangegcd_table_tests table_tests.c)
target_link_libraries(rangegcd_table_tests 
                      libtable
                      Unity)
add_test(rangegcd_table_tests rangegcd_table_tests)
