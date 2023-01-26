add_subdirectory(lib)
add_executable(merge main.c)
target_link_libraries(merge libheap)

if (test_flag)
    add_subdirectory(tests)
endif()
