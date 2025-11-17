cmake_minimum_required(VERSION 3.14)
project(LexerProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Librería del Lexer (reutilizable)
add_library(lexer_lib
    Lexer.cpp
    Lexer.hpp
)

# Ejecutable principal para analizar archivos .txt
add_executable(lexer_main
    main.cpp
)
target_link_libraries(lexer_main PRIVATE lexer_lib)

# Mensaje de ayuda
message(STATUS "========================================")
message(STATUS "Lexer Project Configuration")
message(STATUS "========================================")
message(STATUS "Build target:")
message(STATUS "  lexer_main  - Analyze .txt files")
message(STATUS "")
message(STATUS "Usage example:")
message(STATUS "  ./build/lexer_main program.txt")
message(STATUS "========================================")