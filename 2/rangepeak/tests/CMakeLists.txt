add_executable(rangemax_tests tests.c)
target_link_libraries(rangemax_tests Unity libsegtree)
add_test(rangemax_tests rangemax_tests)
