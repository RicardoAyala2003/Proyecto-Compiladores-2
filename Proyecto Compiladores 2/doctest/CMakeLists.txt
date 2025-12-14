cmake_minimum_required(VERSION 3.14)
project(ProyectoCompiladores2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Descargar doctest usando FetchContent
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

# Archivos fuente del proyecto
set(SOURCES
    ../ast.cpp
    ../Lexer.cpp
    ../Parser.cpp
)

# Librería del proyecto
add_library(proyecto_lib ${SOURCES})

# Incluye headers
target_include_directories(proyecto_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tests con doctest
add_executable(proyecto_tests
    maindoctest.cpp
)
target_link_libraries(proyecto_tests proyecto_lib doctest::doctest)

# Habilitar CTest
enable_testing()
add_test(NAME proyecto_tests COMMAND proyecto_tests)

# Opcional: warnings
target_compile_options(proyecto_lib PRIVATE -Wall -Wextra -pedantic)
target_compile_options(proyecto_tests PRIVATE -Wall -Wextra -pedantic)
