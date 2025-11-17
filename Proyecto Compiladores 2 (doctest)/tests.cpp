#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Lexer.hpp"
#include <vector>
#include <string>

// Helper function para crear el lexer desde un string
Lexer createLexer(const std::string& input) {
    std::vector<char> chars(input.begin(), input.end());
    return Lexer(chars);
}

// ============================================================================
// OPERADORES ARITMÉTICOS
// ============================================================================
TEST_CASE("OP_ADD - suma") {
    auto lexer = createLexer("+");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getBuffer() == "+");
}

TEST_CASE("OP_ADD seguido de número") {
    auto lexer = createLexer("+5");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("OP_ADD al final de archivo") {
    auto lexer = createLexer("+");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("OP_SUB - resta solo") {
    auto lexer = createLexer("-");
    CHECK(lexer.getNextToken() == "OP_SUB");
    CHECK(lexer.getBuffer() == "-");
}

TEST_CASE("OP_SUB seguido de espacio") {
    auto lexer = createLexer("- ");
    CHECK(lexer.getNextToken() == "OP_SUB");
}

TEST_CASE("OP_SUB seguido de letra") {
    auto lexer = createLexer("-x");
    CHECK(lexer.getNextToken() == "OP_SUB");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
}

TEST_CASE("OP_MUL - multiplicación") {
    auto lexer = createLexer("*");
    CHECK(lexer.getNextToken() == "OP_MUL");
    CHECK(lexer.getBuffer() == "*");
}

TEST_CASE("OP_MUL entre números") {
    auto lexer = createLexer("3*4");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "OP_MUL");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("OP_DIV - división solo") {
    auto lexer = createLexer("/");
    CHECK(lexer.getNextToken() == "OP_DIV");
    CHECK(lexer.getBuffer() == "/");
}

TEST_CASE("OP_DIV seguido de espacio") {
    auto lexer = createLexer("/ ");
    CHECK(lexer.getNextToken() == "OP_DIV");
}

TEST_CASE("OP_DIV seguido de número") {
    auto lexer = createLexer("/5");
    CHECK(lexer.getNextToken() == "OP_DIV");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("OP_MOD - módulo") {
    auto lexer = createLexer("%");
    CHECK(lexer.getNextToken() == "OP_MOD");
    CHECK(lexer.getBuffer() == "%");
}

TEST_CASE("OP_MOD en expresión") {
    auto lexer = createLexer("10 % 3");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "OP_MOD");
    CHECK(lexer.getNextToken() == "INTEGER");
}

// ============================================================================
// OPERADORES DE ASIGNACIÓN Y COMPARACIÓN
// ============================================================================
TEST_CASE("OP_ASSIGN - asignación simple") {
    auto lexer = createLexer("=");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getBuffer() == "=");
}

TEST_CASE("OP_ASSIGN seguido de EOF") {
    auto lexer = createLexer("=");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("OP_ASSIGN seguido de espacio") {
    auto lexer = createLexer("= ");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
}

TEST_CASE("OP_EQ - igualdad") {
    auto lexer = createLexer("==");
    CHECK(lexer.getNextToken() == "OP_EQ");
    CHECK(lexer.getBuffer() == "==");
}

TEST_CASE("OP_EQ en comparación") {
    auto lexer = createLexer("x == 5");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_EQ");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("OP_NOT - negación lógica") {
    auto lexer = createLexer("!");
    CHECK(lexer.getNextToken() == "OP_NOT");
    CHECK(lexer.getBuffer() == "!");
}

TEST_CASE("OP_NOT seguido de EOF") {
    auto lexer = createLexer("!");
    CHECK(lexer.getNextToken() == "OP_NOT");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("OP_NOT seguido de espacio") {
    auto lexer = createLexer("! ");
    CHECK(lexer.getNextToken() == "OP_NOT");
}

TEST_CASE("OP_NE - diferente") {
    auto lexer = createLexer("!=");
    CHECK(lexer.getNextToken() == "OP_NE");
    CHECK(lexer.getBuffer() == "!=");
}

TEST_CASE("OP_NE en comparación") {
    auto lexer = createLexer("a != b");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_NE");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
}

// ============================================================================
// OPERADORES RELACIONALES
// ============================================================================
TEST_CASE("OP_LT - menor que") {
    auto lexer = createLexer("<");
    CHECK(lexer.getNextToken() == "OP_LT");
    CHECK(lexer.getBuffer() == "<");
}

TEST_CASE("OP_LT seguido de EOF") {
    auto lexer = createLexer("<");
    CHECK(lexer.getNextToken() == "OP_LT");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("OP_LT seguido de espacio") {
    auto lexer = createLexer("< ");
    CHECK(lexer.getNextToken() == "OP_LT");
}

TEST_CASE("OP_LE - menor o igual") {
    auto lexer = createLexer("<=");
    CHECK(lexer.getNextToken() == "OP_LE");
    CHECK(lexer.getBuffer() == "<=");
}

TEST_CASE("OP_LE en condición") {
    auto lexer = createLexer("x <= 10");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_LE");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("OP_GT - mayor que") {
    auto lexer = createLexer(">");
    CHECK(lexer.getNextToken() == "OP_GT");
    CHECK(lexer.getBuffer() == ">");
}

TEST_CASE("OP_GT seguido de EOF") {
    auto lexer = createLexer(">");
    CHECK(lexer.getNextToken() == "OP_GT");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("OP_GT seguido de espacio") {
    auto lexer = createLexer("> ");
    CHECK(lexer.getNextToken() == "OP_GT");
}

TEST_CASE("OP_GE - mayor o igual") {
    auto lexer = createLexer(">=");
    CHECK(lexer.getNextToken() == "OP_GE");
    CHECK(lexer.getBuffer() == ">=");
}

TEST_CASE("OP_GE en condición") {
    auto lexer = createLexer("y >= 0");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_GE");
    CHECK(lexer.getNextToken() == "INTEGER");
}

// ============================================================================
// OPERADORES LÓGICOS
// ============================================================================
TEST_CASE("OP_AND - AND lógico") {
    auto lexer = createLexer("&&");
    CHECK(lexer.getNextToken() == "OP_AND");
    CHECK(lexer.getBuffer() == "&&");
}

TEST_CASE("OP_AND en expresión") {
    auto lexer = createLexer("a && b");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_AND");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
}

TEST_CASE("AND incompleto - un solo &") {
    auto lexer = createLexer("&");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("AND incompleto seguido de letra") {
    auto lexer = createLexer("&x");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("AND incompleto al final") {
    auto lexer = createLexer("&");
    auto token = lexer.getNextToken();
    CHECK(token == "ERROR");
}

TEST_CASE("OP_OR - OR lógico") {
    auto lexer = createLexer("||");
    CHECK(lexer.getNextToken() == "OP_OR");
    CHECK(lexer.getBuffer() == "||");
}

TEST_CASE("OP_OR en expresión") {
    auto lexer = createLexer("x || y");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_OR");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
}

TEST_CASE("OR incompleto - un solo |") {
    auto lexer = createLexer("|");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("OR incompleto seguido de letra") {
    auto lexer = createLexer("|x");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("OR incompleto al final") {
    auto lexer = createLexer("|");
    auto token = lexer.getNextToken();
    CHECK(token == "ERROR");
}

// ============================================================================
// NÚMEROS ENTEROS
// ============================================================================
TEST_CASE("INTEGER - número simple") {
    auto lexer = createLexer("42");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "42");
}

TEST_CASE("INTEGER - cero") {
    auto lexer = createLexer("0");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "0");
}

TEST_CASE("INTEGER - número largo") {
    auto lexer = createLexer("123456789");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "123456789");
}

TEST_CASE("INTEGER - número muy largo") {
    auto lexer = createLexer("9876543210");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "9876543210");
}

TEST_CASE("INTEGER negativo") {
    auto lexer = createLexer("-15");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "-15");
}

TEST_CASE("INTEGER negativo largo") {
    auto lexer = createLexer("-999888777");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "-999888777");
}

TEST_CASE("INTEGER seguido de operador") {
    auto lexer = createLexer("42+");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "42");
    CHECK(lexer.getNextToken() == "OP_ADD");
}

TEST_CASE("INTEGER seguido de EOF") {
    auto lexer = createLexer("99");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("INTEGER seguido de espacio") {
    auto lexer = createLexer("42 ");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "42");
}

TEST_CASE("Múltiples INTEGER") {
    auto lexer = createLexer("1 2 3");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "INTEGER");
}

// ============================================================================
// IDENTIFICADORES
// ============================================================================
TEST_CASE("IDENTIFIER simple") {
    auto lexer = createLexer("variable");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "variable");
}

TEST_CASE("IDENTIFIER de una letra") {
    auto lexer = createLexer("x");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "x");
}

TEST_CASE("IDENTIFIER con underscore al inicio") {
    auto lexer = createLexer("_temp");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "_temp");
}

TEST_CASE("IDENTIFIER solo underscore") {
    auto lexer = createLexer("_");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "_");
}

TEST_CASE("IDENTIFIER con números") {
    auto lexer = createLexer("var123");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "var123");
}

TEST_CASE("IDENTIFIER con underscores múltiples") {
    auto lexer = createLexer("mi_variable_larga");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "mi_variable_larga");
}

TEST_CASE("IDENTIFIER mayúsculas") {
    auto lexer = createLexer("CONSTANTE");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "CONSTANTE");
}

TEST_CASE("IDENTIFIER mixto") {
    auto lexer = createLexer("miVariable123_test");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "miVariable123_test");
}

TEST_CASE("IDENTIFIER seguido de EOF") {
    auto lexer = createLexer("abc");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("IDENTIFIER seguido de operador") {
    auto lexer = createLexer("x+");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
}

TEST_CASE("IDENTIFIER seguido de delimitador") {
    auto lexer = createLexer("x;");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
}

// ============================================================================
// KEYWORDS
// ============================================================================
TEST_CASE("KW_IF") {
    auto lexer = createLexer("if");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getBuffer() == "if");
}

TEST_CASE("KW_IF seguido de EOF") {
    auto lexer = createLexer("if");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("KW_IF seguido de espacio") {
    auto lexer = createLexer("if ");
    CHECK(lexer.getNextToken() == "KW_IF");
}

TEST_CASE("KW_IF seguido de paréntesis") {
    auto lexer = createLexer("if(");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getNextToken() == "LPAREN");
}

TEST_CASE("KW_ELSE") {
    auto lexer = createLexer("else");
    CHECK(lexer.getNextToken() == "KW_ELSE");
    CHECK(lexer.getBuffer() == "else");
}

TEST_CASE("KW_WHILE") {
    auto lexer = createLexer("while");
    CHECK(lexer.getNextToken() == "KW_WHILE");
    CHECK(lexer.getBuffer() == "while");
}

TEST_CASE("KW_FOR") {
    auto lexer = createLexer("for");
    CHECK(lexer.getNextToken() == "KW_FOR");
    CHECK(lexer.getBuffer() == "for");
}

TEST_CASE("KW_RETURN") {
    auto lexer = createLexer("return");
    CHECK(lexer.getNextToken() == "KW_RETURN");
    CHECK(lexer.getBuffer() == "return");
}

TEST_CASE("KW_INT") {
    auto lexer = createLexer("int");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getBuffer() == "int");
}

TEST_CASE("KW_VOID") {
    auto lexer = createLexer("void");
    CHECK(lexer.getNextToken() == "KW_VOID");
    CHECK(lexer.getBuffer() == "void");
}

TEST_CASE("KW_PRINT") {
    auto lexer = createLexer("print");
    CHECK(lexer.getNextToken() == "KW_PRINT");
    CHECK(lexer.getBuffer() == "print");
}

TEST_CASE("Keyword como parte de identificador - ifvar") {
    auto lexer = createLexer("ifvar");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "ifvar");
}

TEST_CASE("Identificador parecido a keyword - integer") {
    auto lexer = createLexer("integer");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "integer");
}

TEST_CASE("Identificador parecido a keyword - whileLoop") {
    auto lexer = createLexer("whileLoop");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getBuffer() == "whileLoop");
}

// ============================================================================
// DELIMITADORES
// ============================================================================
TEST_CASE("SEMICOLON") {
    auto lexer = createLexer(";");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getBuffer() == ";");
}

TEST_CASE("COMMA") {
    auto lexer = createLexer(",");
    CHECK(lexer.getNextToken() == "COMMA");
    CHECK(lexer.getBuffer() == ",");
}

TEST_CASE("LPAREN") {
    auto lexer = createLexer("(");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getBuffer() == "(");
}

TEST_CASE("RPAREN") {
    auto lexer = createLexer(")");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getBuffer() == ")");
}

TEST_CASE("LBRACE") {
    auto lexer = createLexer("{");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getBuffer() == "{");
}

TEST_CASE("RBRACE") {
    auto lexer = createLexer("}");
    CHECK(lexer.getNextToken() == "RBRACE");
    CHECK(lexer.getBuffer() == "}");
}

TEST_CASE("Paréntesis consecutivos") {
    auto lexer = createLexer("()");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "RPAREN");
}

TEST_CASE("Llaves consecutivas") {
    auto lexer = createLexer("{}");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Lista de parámetros") {
    auto lexer = createLexer("(a, b, c)");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "COMMA");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "COMMA");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "RPAREN");
}

// ============================================================================
// COMENTARIOS DE LÍNEA
// ============================================================================
TEST_CASE("Comentario de línea simple") {
    auto lexer = createLexer("// comentario\n42");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "42");
}

TEST_CASE("Comentario de línea al final") {
    auto lexer = createLexer("42 // comentario");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("Comentario de línea vacío") {
    auto lexer = createLexer("//\n42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de línea con \\r\\n") {
    auto lexer = createLexer("// test\r\n99");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de línea solo \\r") {
    auto lexer = createLexer("// test\r99");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Múltiples comentarios de línea") {
    auto lexer = createLexer("// uno\n// dos\n42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de línea largo") {
    auto lexer = createLexer("// esto es un comentario muy largo con muchas palabras\n42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Código después de comentario") {
    auto lexer = createLexer("x = 5; // asignación");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "EOF");
}

// ============================================================================
// COMENTARIOS DE BLOQUE
// ============================================================================
TEST_CASE("Comentario de bloque simple") {
    auto lexer = createLexer("/* comentario */ 42");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "42");
}

TEST_CASE("Comentario de bloque vacío") {
    auto lexer = createLexer("/**/ 42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de bloque multilínea") {
    auto lexer = createLexer("/* linea 1\nlinea 2\nlinea 3 */ 42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de bloque con asteriscos") {
    auto lexer = createLexer("/* * ** *** */ 42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de bloque con * intermedio") {
    auto lexer = createLexer("/* test * more */ 42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de bloque múltiples * antes de /") {
    auto lexer = createLexer("/* test ***/ 42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Comentario de bloque al final") {
    auto lexer = createLexer("42 /* fin */");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("Comentario de bloque entre tokens") {
    auto lexer = createLexer("x /* comentario */ + /* otro */ y");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
}

TEST_CASE("Comentario de bloque incompleto") {
    auto lexer = createLexer("/* sin cerrar");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("Comentario de bloque con solo *") {
    auto lexer = createLexer("/* test *");
    CHECK(lexer.getNextToken() == "ERROR");
}

// ============================================================================
// ESPACIOS EN BLANCO
// ============================================================================
TEST_CASE("Espacios múltiples") {
    auto lexer = createLexer("42     10");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Tab entre tokens") {
    auto lexer = createLexer("42\t10");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Newline entre tokens") {
    auto lexer = createLexer("42\n10");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Carriage return") {
    auto lexer = createLexer("42\r10");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Espacios al inicio") {
    auto lexer = createLexer("   42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Solo espacios") {
    auto lexer = createLexer("     ");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("Mezcla de whitespace") {
    auto lexer = createLexer(" \t\n\r 42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

// ============================================================================
// EOF
// ============================================================================
TEST_CASE("EOF - archivo vacío") {
    auto lexer = createLexer("");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("EOF después de entero") {
    auto lexer = createLexer("42");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("EOF después de operador") {
    auto lexer = createLexer("+");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("EOF después de identificador") {
    auto lexer = createLexer("variable");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("EOF después de keyword") {
    auto lexer = createLexer("if");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("EOF después de delimitador") {
    auto lexer = createLexer(";");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "EOF");
}

TEST_CASE("Múltiples llamadas a EOF") {
    auto lexer = createLexer("");
    CHECK(lexer.getNextToken() == "EOF");
    CHECK(lexer.getNextToken() == "EOF");
    CHECK(lexer.getNextToken() == "EOF");
}

// ============================================================================
// ERRORES
// ============================================================================
TEST_CASE("ERROR - carácter @") {
    auto lexer = createLexer("@");
    CHECK(lexer.getNextToken() == "ERROR");
    CHECK(lexer.getBuffer() == "@");
}

TEST_CASE("ERROR - carácter #") {
    auto lexer = createLexer("#");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("ERROR - carácter $") {
    auto lexer = createLexer("$");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("ERROR - carácter ~") {
    auto lexer = createLexer("~");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("ERROR - carácter `") {
    auto lexer = createLexer("`");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("ERROR - AND incompleto") {
    auto lexer = createLexer("&");
    CHECK(lexer.getNextToken() == "ERROR");
}

TEST_CASE("ERROR - OR incompleto") {
    auto lexer = createLexer("|");
    CHECK(lexer.getNextToken() == "ERROR");
}

// ============================================================================
// PROGRAMAS COMPLETOS
// ============================================================================
TEST_CASE("Programa - declaración simple") {
    auto lexer = createLexer("int x = 42;");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
}

TEST_CASE("Programa - if statement") {
    auto lexer = createLexer("if (x > 10) { return x; }");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_GT");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "KW_RETURN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Programa - if-else") {
    auto lexer = createLexer("if (x) { y = 1; } else { y = 0; }");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "RBRACE");
    CHECK(lexer.getNextToken() == "KW_ELSE");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Programa - while loop") {
    auto lexer = createLexer("while (x < 100) { x = x + 1; }");
    CHECK(lexer.getNextToken() == "KW_WHILE");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_LT");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Programa - for loop") {
    auto lexer = createLexer("for (i = 0; i < 10; i = i + 1) { print i; }");
    CHECK(lexer.getNextToken() == "KW_FOR");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_LT");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "KW_PRINT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Programa - expresión aritmética compleja") {
    auto lexer = createLexer("a + b * c - d / e % f");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_MUL");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_SUB");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_DIV");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_MOD");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
}

TEST_CASE("Programa - expresión lógica compleja") {
    auto lexer = createLexer("a && b || !c && (d != e)");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_AND");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_OR");
    CHECK(lexer.getNextToken() == "OP_NOT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_AND");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_NE");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "RPAREN");
}

TEST_CASE("Programa - función simple") {
    auto lexer = createLexer("int suma(int a, int b) { return a + b; }");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "COMMA");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "KW_RETURN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Programa - con comentarios mezclados") {
    auto lexer = createLexer("int x = 5; // declaración\n/* bloque */ x = x + 1;");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
}

TEST_CASE("Programa - múltiples declaraciones") {
    auto lexer = createLexer("int x = 1; int y = 2; int z = 3;");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
}

// ============================================================================
// CASOS EDGE ADICIONALES
// ============================================================================
TEST_CASE("Edge - todos los operadores consecutivos") {
    auto lexer = createLexer("+-*/%");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "OP_SUB");
    CHECK(lexer.getNextToken() == "OP_MUL");
    CHECK(lexer.getNextToken() == "OP_DIV");
    CHECK(lexer.getNextToken() == "OP_MOD");
}

TEST_CASE("Edge - todos los delimitadores consecutivos") {
    auto lexer = createLexer(";,(){}");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "COMMA");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Edge - operadores relacionales seguidos") {
    auto lexer = createLexer("<<=>>=");
    CHECK(lexer.getNextToken() == "OP_LT");
    CHECK(lexer.getNextToken() == "OP_LE");
    CHECK(lexer.getNextToken() == "OP_GT");
    CHECK(lexer.getNextToken() == "OP_GE");
}

TEST_CASE("Edge - mezcla de todo sin espacios") {
    auto lexer = createLexer("if(x>=10){y=x+5;}");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getNextToken() == "LPAREN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_GE");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "RPAREN");
    CHECK(lexer.getNextToken() == "LBRACE");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ASSIGN");
    CHECK(lexer.getNextToken() == "IDENTIFIER");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "SEMICOLON");
    CHECK(lexer.getNextToken() == "RBRACE");
}

TEST_CASE("Edge - números negativos en expresión") {
    auto lexer = createLexer("-5 + -10");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "-5");
    CHECK(lexer.getNextToken() == "OP_ADD");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getBuffer() == "-10");
}

TEST_CASE("Edge - operador menos vs número negativo") {
    auto lexer = createLexer("5 - 3");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "OP_SUB");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Edge - todas las keywords juntas") {
    auto lexer = createLexer("if else while for return int void print");
    CHECK(lexer.getNextToken() == "KW_IF");
    CHECK(lexer.getNextToken() == "KW_ELSE");
    CHECK(lexer.getNextToken() == "KW_WHILE");
    CHECK(lexer.getNextToken() == "KW_FOR");
    CHECK(lexer.getNextToken() == "KW_RETURN");
    CHECK(lexer.getNextToken() == "KW_INT");
    CHECK(lexer.getNextToken() == "KW_VOID");
    CHECK(lexer.getNextToken() == "KW_PRINT");
}

TEST_CASE("Edge - comentario dentro de comentario de bloque") {
    auto lexer = createLexer("/* // esto no termina el bloque */ 42");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Edge - división vs comentario") {
    auto lexer = createLexer("5 / 2");
    CHECK(lexer.getNextToken() == "INTEGER");
    CHECK(lexer.getNextToken() == "OP_DIV");
    CHECK(lexer.getNextToken() == "INTEGER");
}

TEST_CASE("Edge - solo EOF repetido") {
    auto lexer = createLexer("");
    for (int i = 0; i < 10; i++) {
        CHECK(lexer.getNextToken() == "EOF");
    }
}