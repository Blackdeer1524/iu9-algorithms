get_filename_component(section_path ../7 DIRECTORY)
get_filename_component(section ${section_path} NAME)
get_filename_component(exercise ../7 NAME)

string(REPLACE " " "_" section ${section})
string(REPLACE " " "_" exercise ${exercise})


include_directories(./)
add_executable(${section}.${exercise} main.c)
