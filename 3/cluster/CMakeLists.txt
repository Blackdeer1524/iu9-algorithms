add_subdirectory(lib)
add_executable(cluster main.c)
target_link_libraries(cluster libheap)
add_executable(cluster_submission submission.c)

if (test_flag)
    add_subdirectory(tests)
endif()
