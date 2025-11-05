Proyecto Compiladores 2
-----------------------

Este proyecto consiste en el desarrollo de un compilador educativo en C++.
Incluye las fases principales de un compilador: análisis léxico, sintáctico,
semántico y generación de código intermedio.

Estructura sugerida de carpetas
-------------------------------
Proyecto-Compiladores-2/
├── CMakeLists.txt
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── semantic/
│   ├── codegen/
│   └── main.cpp
├── include/
├── examples/
├── tests/
├── docs/
├── build/
└── README.md

Requisitos
-----------
- C++17 o superior
- CMake 3.15+
- Compilador: GCC, Clang o MSVC

Instalación y compilación
--------------------------
mkdir build
cd build
cmake ..
cmake --build .

Uso
---
Ejemplo de ejecución:
./build/Compilador examples/programa_ejemplo.lang

Tests
-----
Los tests pueden implementarse con Catch2 o GoogleTest.

Ejemplo:
ctest --output-on-failure

Buenas prácticas
----------------
- Mantener las gramáticas y documentación en docs/
- Dividir las fases del compilador en módulos
- Crear pruebas unitarias para cada fase

Licencia
--------
MIT License
