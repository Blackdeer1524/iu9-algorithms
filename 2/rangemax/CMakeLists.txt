add_subdirectory(lib)
add_executable(rangemax main.c)
target_link_libraries(rangemax libsegtree)

if (test_flag)
    add_subdirectory(tests)
endif()
