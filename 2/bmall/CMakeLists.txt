add_executable("bmall" main.c)

add_custom_command(
    COMMAND "${PROJECT_SOURCE_DIR}/memtest.sh" ${CMAKE_CURRENT_BINARY_DIR}/bmall
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT  "valgrind_report.txt"
    COMMENT "Running valgrind check..."
)

add_custom_target(
    valgrind_check ALL
    DEPENDS "${PROJECT_SOURCE_DIR}/memtest.sh"
    valgrind_report.txt
) 
