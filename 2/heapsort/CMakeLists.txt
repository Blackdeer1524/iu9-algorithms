add_executable(heapsort main.c)
target_link_libraries(heapsort libheap)
add_subdirectory(lib)

if (test_flag)
    add_subdirectory(tests)
endif()