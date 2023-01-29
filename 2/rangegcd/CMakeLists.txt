add_subdirectory(lib)
add_executable(rangegcd main.c)
target_link_libraries(rangegcd libgcdmat)

add_executable(rangegcd_submission submission.c)

if (test_flag) 
    add_subdirectory(tests)
endif()
