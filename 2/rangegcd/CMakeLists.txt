add_subdirectory(lib)
add_executable(rangegcd main.c)
target_link_libraries(rangegcd libtable)
