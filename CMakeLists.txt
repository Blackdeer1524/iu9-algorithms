cmake_minimum_required(VERSION 3.22)
project(iu_algos C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_C_FLAGS "-g3 -Wall -Werror -O0 -fsanitize=address -fdiagnostics-color=always") 
set(CMAKE_LINK_DEF_FILE_FLAG "-fsanitize=address")

add_subdirectory(2)
