add_subdirectory(lib)
add_executable(rangepeak main.c)
# add_executable(rangepeak_submission submission.c)
target_link_libraries(rangepeak libsegtree)

if (test_flag)
    add_subdirectory(tests)
endif()
