add_subdirectory(lib)
add_executable(lexavl main.c)
target_link_libraries(lexavl liblexer)

add_executable(lexavl_submission submission.c)
