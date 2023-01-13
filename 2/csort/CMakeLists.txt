add_executable(csort main.c)
add_subdirectory(lib)
target_link_libraries(csort csort_utils)

if (test_flag)
    add_subdirectory(tests)
endif()