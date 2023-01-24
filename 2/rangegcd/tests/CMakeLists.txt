add_executable(rangegcd_tests tests.c)
target_link_libraries(rangegcd_tests Unity libsegtree)
add_test(rangegcd_tests rangegcd_tests)
