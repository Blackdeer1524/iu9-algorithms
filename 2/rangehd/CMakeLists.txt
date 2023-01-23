add_subdirectory(lib)
add_executable(rangehd main.c)
target_link_libraries(rangehd libsegtree)
add_executable(rangehd_submission submission.c)

if (test_flag)
    add_subdirectory(tests)
endif()