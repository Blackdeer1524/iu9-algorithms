add_executable(cluster_tests tests.c)
target_link_libraries(cluster_tests
                      Unity
                      libheap)
add_test(cluster_tests cluster_tests)
