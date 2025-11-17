cmake_minimum_required(VERSION 3.14)
project(LexerProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Descargar doctest usando FetchContent
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

# Librería del Lexer
add_library(lexer_lib
    Lexer.cpp
    Lexer.hpp
)

# Ejecutable principal
add_executable(lexer_main
    main.cpp
)
target_link_libraries(lexer_main lexer_lib)

# Ejecutable de tests
add_executable(lexer_tests
    tests.cpp
)
target_link_libraries(lexer_tests lexer_lib doctest::doctest)

# Habilitar testing
enable_testing()
add_test(NAME lexer_tests COMMAND lexer_tests)