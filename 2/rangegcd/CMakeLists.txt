add_subdirectory(lib)
add_executable(rangegcd main.c)
target_link_libraries(rangegcd libtable)

if (test_flag) 
    add_subdirectory(tests)
endif()
