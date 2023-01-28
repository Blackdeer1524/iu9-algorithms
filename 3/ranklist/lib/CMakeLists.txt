add_library(liblinkedlist ./src/linked_list.c)
target_include_directories(liblinkedlist PUBLIC ./include)

add_library(libskiplist ./src/skip_list.c)
target_include_directories(libskiplist PUBLIC ./include)
target_link_libraries(libskiplist liblinkedlist)
