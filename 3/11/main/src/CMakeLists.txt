include_directories(${lib_include_dir})
add_executable(${target_name} main.c)
target_link_libraries(${target_name} Lexer)

message("lib path: " ${lib_path})
message("lib include path: " ${lib_include_dir})
