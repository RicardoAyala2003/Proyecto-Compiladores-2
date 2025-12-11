cmake_minimum_required(VERSION 3.10)

project(ProyectoCompiladores2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Archivos fuente

set(SOURCES

    main.cpp

    Lexer.cpp

    Parser.cpp

    ast.cpp

)

# Archivos header

set(HEADERS

    Lexer.hpp

    Parser.hpp

    ast.hpp

)

# Ejecutable principal

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

