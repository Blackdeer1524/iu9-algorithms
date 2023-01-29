add_subdirectory(lib)
add_executable(ranklist main.c)
target_link_libraries(ranklist libskiplist)

add_executable(ranklist_submission submission.c)

if (test_flag)
    add_subdirectory(tests)
endif()
