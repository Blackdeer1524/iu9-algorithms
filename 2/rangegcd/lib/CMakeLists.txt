add_library(libtable ./src/table.c)
target_include_directories(libtable PUBLIC ./include)

add_library(libgcdmat ./src/gcd_matrix.c)
target_include_directories(libgcdmat PUBLIC ./include)
target_link_libraries(libgcdmat libtable)
