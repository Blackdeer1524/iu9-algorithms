add_subdirectory(lib)
add_executable(rangegcd main.c)
add_executable(rangegcd_submission submission.c)
target_link_libraries(rangegcd libsegtree)

if (test_flag)
    add_subdirectory(tests)
endif()
