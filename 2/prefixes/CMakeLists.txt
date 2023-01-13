add_subdirectory(lib)
add_executable(prefixes main.c)
target_link_libraries(prefixes libprefix)

if (test_flag)
    add_subdirectory(tests)
endif()
