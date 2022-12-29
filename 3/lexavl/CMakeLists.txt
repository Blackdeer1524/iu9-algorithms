get_filename_component(section_path ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(section ${section_path} NAME)
get_filename_component(exercise ${CMAKE_CURRENT_SOURCE_DIR} NAME)

string(REPLACE " " "_" section ${section})
string(REPLACE " " "_" exercise ${exercise})

set(lib_path ${section_path}/${exercise}/lib)
set(lib_include_dir ${lib_path}/include)
set(target_name ${section}.${exercise})

add_subdirectory(lib/src)
add_subdirectory(main/src)
