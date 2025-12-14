# Proyecto Compiladores 2
Compilador que traduce un lenguaje imperativo simplificado a C++.

## Estructura
```
Proyecto Compiladores 2/
├── CMakeLists.txt
├── ast.tc                   # Definición del AST
├── gramatica.y              # Gramática (Bison)
├── Lexer.cpp / Lexer.hpp    # Analizador léxico
├── main.cpp
├── doctest/                 # Tests
│   ├── CMakeLists.txt
│   └── maindoctest.cpp
└── ejemplos/                # 96 casos de prueba
```

**Archivos generados:** `ast.cpp`, `ast.hpp`, `Parser.cpp`, `Parser.hpp`

## Requisitos
```bash
sudo apt install build-essential cmake bison treecc
```

## Compilación
```bash
# Configurar
cmake -B build -S .

# Generar y compilar
clear && bison -o Parser.cpp --header=Parser.hpp gramatica.y && treecc -o ast.cpp -h ast.hpp ast.tc && cmake --build build
```

## Uso
```bash
# Compilar programa
./build/proyecto_compilador ejemplos/factorial_calculation.c

# Ejecutar
g++ -o programa codigo.cpp && ./programa
```

## Tests
```bash
cd doctest
mkdir build && cd build
cmake .. && cmake --build .
./proyecto_tests
```

## Características
- **Tipos:** `int`, `float`
- **Keywords:** `if`, `else`, `while`, `print`, `input`
- **Operadores:** `+`, `-`, `*`, `/`, `%`, `<`, `>`, `<=`, `>=`, `==`, `!=`, `&&`, `||`, `!`
- **Comentarios:** `//` y `/* */`