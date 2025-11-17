#include "Lexer.hpp"
#include <cctype>

Lexer::Lexer(std::vector<char> input) : characters(input), index(0), buffer("") {}

char Lexer::getNextChar()
{
    if (index >= characters.size()) return '\0';
    return characters[index++];
}

char Lexer::checkNextChar()
{
    if (index >= characters.size()) return '\0';
    return characters[index];
}

std::string Lexer::getBuffer()
{
    return buffer;
}

std::string Lexer::getNextToken()
{
    int currentState = 0;
    buffer = "";

    char currentChar = getNextChar();
    if (currentChar == '\0') return "EOF";

    while (true)
    {
        switch (currentState)
        {
        case 0: // Estado inicial
            if ((currentChar >= 9 && currentChar <= 10) || currentChar == 13 || currentChar == 32)
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "EOF";
                currentState = 1; // Espacios en blanco
            }
            else if (currentChar == '+')
            {
                buffer += currentChar;
                return "OP_ADD";
            }
            else if (currentChar == '-')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_SUB";
                currentState = 2; // Puede ser OP_SUB o inicio de número negativo
            }
            else if (currentChar == '*')
            {
                buffer += currentChar;
                return "OP_MUL";
            }
            else if (currentChar == '/')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_DIV";
                currentState = 3; // Puede ser OP_DIV o comentario
            }
            else if (currentChar == '%')
            {
                buffer += currentChar;
                return "OP_MOD";
            }
            else if (currentChar == '=')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_ASSIGN";
                currentState = 4; // Puede ser OP_ASSIGN o OP_EQ
            }
            else if (currentChar == '!')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_NOT";
                currentState = 5; // Puede ser OP_NOT o OP_NE
            }
            else if (currentChar == '<')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_LT";
                currentState = 6; // Puede ser OP_LT o OP_LE
            }
            else if (currentChar == '>')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_GT";
                currentState = 7; // Puede ser OP_GT o OP_GE
            }
            else if (currentChar == '&')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 8; // Debe ser &&
            }
            else if (currentChar == '|')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 9; // Debe ser ||
            }
            else if (currentChar == ';')
            {
                buffer += currentChar;
                return "SEMICOLON";
            }
            else if (currentChar == ',')
            {
                buffer += currentChar;
                return "COMMA";
            }
            else if (currentChar == '(')
            {
                buffer += currentChar;
                return "LPAREN";
            }
            else if (currentChar == ')')
            {
                buffer += currentChar;
                return "RPAREN";
            }
            else if (currentChar == '{')
            {
                buffer += currentChar;
                return "LBRACE";
            }
            else if (currentChar == '}')
            {
                buffer += currentChar;
                return "RBRACE";
            }
            else if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "INTEGER";
                currentState = 10; // Número entero
            }
            else if (std::isalpha(currentChar) || currentChar == '_')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "IDENTIFIER";
                currentState = 11; // Identificador o keyword
            }
            else
            {
                buffer += currentChar;
                return "ERROR";
            }
            break;

        case 1: // Espacios en blanco
            currentState = 0;
            break;

        case 2: // OP_SUB o número negativo
            if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "INTEGER";
                currentState = 10;
            }
            else
            {
                index--;
                return "OP_SUB";
            }
            break;

        case 3: // OP_DIV o comentario
            if (currentChar == '/')
            {
                buffer = "";
                currentState = 12; // Comentario de línea
                currentChar = getNextChar();
                if (currentChar == '\0') return "EOF";
            }
            else if (currentChar == '*')
            {
                buffer = "";
                currentState = 13; // Comentario de bloque
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
            }
            else
            {
                index--;
                return "OP_DIV";
            }
            break;

        case 4: // OP_ASSIGN o OP_EQ
            if (currentChar == '=')
            {
                buffer += currentChar;
                return "OP_EQ";
            }
            else
            {
                index--;
                return "OP_ASSIGN";
            }
            break;

        case 5: // OP_NOT o OP_NE
            if (currentChar == '=')
            {
                buffer += currentChar;
                return "OP_NE";
            }
            else
            {
                index--;
                return "OP_NOT";
            }
            break;

        case 6: // OP_LT o OP_LE
            if (currentChar == '=')
            {
                buffer += currentChar;
                return "OP_LE";
            }
            else
            {
                index--;
                return "OP_LT";
            }
            break;

        case 7: // OP_GT o OP_GE
            if (currentChar == '=')
            {
                buffer += currentChar;
                return "OP_GE";
            }
            else
            {
                index--;
                return "OP_GT";
            }
            break;

        case 8: // OP_AND
            if (currentChar == '&')
            {
                buffer += currentChar;
                return "OP_AND";
            }
            else
            {
                return "ERROR";
            }
            break;

        case 9: // OP_OR
            if (currentChar == '|')
            {
                buffer += currentChar;
                return "OP_OR";
            }
            else
            {
                return "ERROR";
            }
            break;

        case 10: // Número entero
            if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "INTEGER";
                currentState = 10;
            }
            else
            {
                index--;
                return "INTEGER";
            }
            break;

        case 11: // Identificador o keyword
            if (std::isalnum(currentChar) || currentChar == '_')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0')
                {
                    // Verificar keywords al final
                    if (buffer == "if") return "KW_IF";
                    if (buffer == "else") return "KW_ELSE";
                    if (buffer == "while") return "KW_WHILE";
                    if (buffer == "for") return "KW_FOR";
                    if (buffer == "return") return "KW_RETURN";
                    if (buffer == "int") return "KW_INT";
                    if (buffer == "void") return "KW_VOID";
                    if (buffer == "print") return "KW_PRINT";
                    return "IDENTIFIER";
                }
                currentState = 11;
            }
            else
            {
                index--;
                // Verificar keywords
                if (buffer == "if") return "KW_IF";
                if (buffer == "else") return "KW_ELSE";
                if (buffer == "while") return "KW_WHILE";
                if (buffer == "for") return "KW_FOR";
                if (buffer == "return") return "KW_RETURN";
                if (buffer == "int") return "KW_INT";
                if (buffer == "void") return "KW_VOID";
                if (buffer == "print") return "KW_PRINT";
                return "IDENTIFIER";
            }
            break;

        case 12: // Comentario de línea
            if (currentChar == '\n' || currentChar == '\r')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "EOF";
                buffer = "";
                currentState = 0;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "EOF";
                currentState = 12;
            }
            break;

        case 13: // Comentario de bloque - buscando *
            if (currentChar == '*')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 14;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 13;
            }
            break;

        case 14: // Comentario de bloque - después de *
            if (currentChar == '/')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "EOF";
                buffer = "";
                currentState = 0;
            }
            else if (currentChar == '*')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 14;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 13;
            }
            break;
        }
    }
}