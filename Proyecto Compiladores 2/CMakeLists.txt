cmake_minimum_required(VERSION 3.14)
project(ProyectoCompiladores2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Bison
find_package(BISON REQUIRED)

# Generar Parser con Bison
BISON_TARGET(Parser
    gramatica.y
    ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/Parser.hpp
)

# Incluir directorio de archivos generados
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Librería del Lexer
add_library(lexer_lib
    Lexer.cpp
    Lexer.hpp
    ${BISON_Parser_OUTPUTS}
)

# Ejecutable principal
add_executable(proyecto_main
    main.cpp
)

target_link_libraries(proyecto_main PRIVATE lexer_lib)

message(STATUS "========================================")
message(STATUS "Proyecto Compiladores 2")
message(STATUS "========================================")
message(STATUS "Build target:")
message(STATUS "  proyecto_main - Parser completo")
message(STATUS "")
message(STATUS "Usage example:")
message(STATUS "  ./build/proyecto_main programa.txt")
message(STATUS "========================================")