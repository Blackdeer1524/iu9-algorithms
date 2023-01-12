add_executable(bmall main.c)

add_subdirectory(lib)
target_link_libraries(bmall libbmall)

if (test_flag)
    add_subdirectory(tests)
endif()
