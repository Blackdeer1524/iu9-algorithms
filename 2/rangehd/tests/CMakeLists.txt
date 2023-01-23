add_executable(rangehd_tests tests.c)
target_link_libraries(rangehd_tests 
                      Unity
                      libsegtree)
add_test(rangehd_tests rangehd_tests)
