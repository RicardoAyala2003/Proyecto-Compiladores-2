# Proyecto Compiladores 2

Bienvenido/a a Proyecto Compiladores 2.
Este repositorio contiene el código, la documentación y los recursos asociados a un proyecto educativo de compiladores desarrollado en C++.
El objetivo es implementar paso a paso las fases principales de un compilador, desde el análisis léxico hasta la generación de código intermedio.

------------------------------------------------------------

## Descripción

Proyecto Compiladores 2 es un trabajo práctico cuyo propósito es diseñar e implementar las fases fundamentales de un compilador para un mini-lenguaje de programación.

Incluye:

- Análisis léxico (Lexer): tokenización del código fuente, con manejo de comentarios, literales y palabras reservadas.
- Análisis sintáctico (Parser): construcción del árbol sintáctico (AST) usando técnicas LL(1) o LR.
- Análisis semántico: manejo de tablas de símbolos, validación de tipos y detección de errores semánticos.
- Generación de código intermedio: producción de Three Address Code (TAC) o estructura similar.
- (Opcional) generación de código objeto o ensamblador.

------------------------------------------------------------

## Características principales

- Lexer implementado manualmente o mediante herramientas (Flex opcional).
- Parser manual o generado con Bison opcional.
- AST estructurado en clases C++.
- Sistema de compilación mediante CMake.
- Soporte para múltiples pruebas de entrada/salida.

------------------------------------------------------------

## Estructura de carpetas sugerida

Proyecto-Compiladores-2/
├── CMakeLists.txt          # Configuración principal de CMake
├── src/                    # Código fuente (lexer, parser, semántica, main, etc.)
│   ├── lexer/
│   ├── parser/
│   ├── semantic/
│   ├── codegen/
│   └── main.cpp
├── include/                # Archivos de cabecera (.hpp / .h)
├── examples/               # Programas de ejemplo del lenguaje
├── tests/                  # Pruebas unitarias e integración
├── docs/                   # Diagramas, gramáticas, autómatas, documentación
├── build/                  # Carpeta generada por CMake (compilación)
└── README.md

------------------------------------------------------------

## Requisitos

- C++17 o superior
- CMake 3.15+
- Compilador compatible:
  - GCC 9.0 o superior
  - Clang 10 o superior
  - MSVC 2019 o superior

(Opcional: Flex/Bison si se automatizan las fases léxica o sintáctica).

------------------------------------------------------------

## Instalación y compilación

Compilación con CMake:

mkdir -p build
cd build
cmake ..
cmake --build .

Esto generará el ejecutable principal dentro de build/ (por ejemplo build/Compilador).

------------------------------------------------------------

## Uso

Ejecutar el compilador sobre un archivo fuente del mini-lenguaje.

Ejemplo:

./build/Compilador examples/programa_ejemplo.lang

Si el programa admite opciones de salida:

./build/Compilador examples/programa_ejemplo.lang -o build/programa_ejemplo.out

------------------------------------------------------------

## Tests

Los tests pueden implementarse usando Catch2 o GoogleTest.

Ejemplo de ejecución:

ctest --output-on-failure

O directamente:

./build/tests/lexer_tests
./build/tests/parser_tests

------------------------------------------------------------

## Buenas prácticas

- Mantener las gramáticas y autómatas documentados en docs/.
- Dividir las fases del compilador en módulos (lexer, parser, semantic, codegen).
- Usar nombres consistentes y evitar dependencias circulares entre módulos.
- Crear tests para cada fase (por ejemplo, testear el lexer aislado antes del parser).
- Incluir programas de ejemplo en examples/ que validen todas las construcciones del lenguaje.

------------------------------------------------------------

## Ejemplo de contenido en docs/

- gramatica.ebnf — gramática formal del lenguaje.
- automata_lexer.pdf — diagrama de autómata del analizador léxico.
- ast_diagram.png — representación del árbol sintáctico.
- semantic_rules.md — reglas semánticas del lenguaje.

------------------------------------------------------------
