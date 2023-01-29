add_library(liblexer 
            STATIC 
            ./src/lexer.c 
            ./src/avl.c)
target_include_directories(liblexer PUBLIC ./include)
