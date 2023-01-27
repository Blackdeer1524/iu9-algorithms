add_library(libmutils ./src/math_utils.c)
target_include_directories(libmutils PUBLIC ./include)

add_library(libtable ./src/log_table.c)
target_include_directories(libtable PUBLIC ./include)
target_link_libraries(libtable libmutils)

add_library(libgcdmat ./src/gcd_matrix.c)
target_include_directories(libgcdmat PUBLIC ./include)
target_link_libraries(libgcdmat libtable)
target_link_libraries(libgcdmat libmutils)
