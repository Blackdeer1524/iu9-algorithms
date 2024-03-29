cmake_minimum_required(VERSION 3.22)
project(iu_algos C)
set(CMAKE_C_STANDARD 23)

set(TARGET_GROUP production CACHE STRING "Group to build")
set(CUR_MODULE CACHE STRING "module")
set(QUESTION CACHE STRING "question")

if(TARGET_GROUP STREQUAL production)
    set(CMAKE_C_FLAGS "-g3 -Wall -Wextra -Werror -O0 -fsanitize=address -fdiagnostics-color=always") 
    set(CMAKE_LINK_DEF_FILE_FLAG "-fsanitize=address")

    set("test_flag" FALSE)
elseif(TARGET_GROUP STREQUAL test)
    set(CMAKE_C_FLAGS "-g3 -Wall -Wextra -Werror -O0") 

    include(CTest)

    add_custom_target(test_memcheck
                      COMMAND ${CMAKE_CTEST_COMMAND} 
                          --force-new-ctest-process --test-action memcheck
                      COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
                      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

    set("test_flag" TRUE)
    add_subdirectory(external)
else()
    message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()

message("started building ${CUR_MODULE}/${QUESTION}")
add_subdirectory(${CUR_MODULE})
