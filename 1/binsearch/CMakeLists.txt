get_filename_component(section_path ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(section ${section_path} NAME)
get_filename_component(exercise ${CMAKE_CURRENT_SOURCE_DIR} NAME)

string(REPLACE " " "_" section ${section})
string(REPLACE " " "_" exercise ${exercise})

add_executable(${section}.${exercise} main.c)
