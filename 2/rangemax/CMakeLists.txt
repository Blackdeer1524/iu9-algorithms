add_subdirectory(lib)
add_executable(rangemax main.c)
add_executable(rangemax_submission submission.c)
target_link_libraries(rangemax libsegtree)

if (test_flag)
    add_subdirectory(tests)
endif()
