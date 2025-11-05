cmake_minimum_required(VERSION 3.15)

# Proyecto Compiladores 24 - configuración CMake para C++
project(ProyectoCompiladores24 LANGUAGES CXX)

# Estándar C++ por defecto (ajustable)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generar compile_commands.json para herramientas (clangd, clang-tidy, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opciones de construcción
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# Warnings y flags recomendados
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
  # Activar ubiquitarios sanitizers si se desea (descomentar)
  # add_compile_options(-fsanitize=address,undefined)
  # add_link_options(-fsanitize=address,undefined)
endif()

# Buscar archivos fuente en src/
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.cc
  ${CMAKE_SOURCE_DIR}/src/*.cxx
)

# Directorios de include (si existen)
if(EXISTS "${CMAKE_SOURCE_DIR}/include")
  include_directories(${CMAKE_SOURCE_DIR}/include)
endif()

# Si hay fuentes en src/, crear ejecutable. Si no, mostrar aviso.
if(PROJECT_SOURCES)
  add_executable(proyecto_compiladores_24 ${PROJECT_SOURCES})
  target_include_directories(proyecto_compiladores_24 PRIVATE ${CMAKE_SOURCE_DIR}/include)

  # Instalación (opcional)
  install(TARGETS proyecto_compiladores_24
    RUNTIME DESTINATION bin
  )
else()
  message(WARNING "No se han encontrado archivos fuente en 'src/'. Agrega tus .cpp en 'src/' o actualiza CMakeLists.txt.")
endif()

# Opción para tests (usa CTest/GoogleTest u otra framework si la agregas)
option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# Mensajes útiles
message(STATUS "CMake build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")

# Sugerencias al usuario
message("")
message(STATUS "Para compilar desde PowerShell (Windows):")
message(STATUS "  mkdir -p build; cd build; cmake .. -G \"Visual Studio 16 2019\"; cmake --build . --config Release")
message(STATUS "O con Ninja/Makefiles:")
message(STATUS "  mkdir -p build; cd build; cmake .. -G Ninja; cmake --build . --config Release")
message("")

# Fin de CMakeLists.txt
