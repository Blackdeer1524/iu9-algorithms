add_executable(ranklist_tests tests.c)
target_link_libraries(ranklist_tests Unity libskiplist)
add_test(ranklist_tests ranklist_tests)
