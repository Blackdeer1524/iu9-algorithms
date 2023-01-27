add_executable(math_utils_tests math_utils_tests.c)
target_link_libraries(math_utils_tests 
                      libmutils
                      Unity)
add_test(math_utils_tests math_utils_tests)

add_executable(rangegcd_table_tests table_tests.c)
target_link_libraries(rangegcd_table_tests 
                      libtable
                      Unity)
add_test(rangegcd_table_tests rangegcd_table_tests)

add_executable(rangegcd_gcd_matrix_tests gcd_matrix_tests.c)
target_link_libraries(rangegcd_gcd_matrix_tests
                      libgcdmat
                      Unity)
add_test(rangegcd_gcd_matrix_tests rangegcd_gcd_matrix_tests)
