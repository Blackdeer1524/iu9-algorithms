add_subdirectory(lib)
add_executable(ranklist main.c)
target_link_libraries(ranklist libskiplist)

if (test_flag)
    add_subdirectory(tests)
endif()
