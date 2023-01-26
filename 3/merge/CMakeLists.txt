add_subdirectory(lib)
add_executable(merge main.c)
target_link_libraries(merge libheap)
