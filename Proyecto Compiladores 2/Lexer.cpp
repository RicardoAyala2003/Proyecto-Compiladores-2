#include "Lexer.hpp"
#include <cctype>
#include <limits>
#include <stdexcept>

Lexer::Lexer(std::vector<char> input) : characters(input), index(0), buffer(""), line(1), column(1) {}

char Lexer::getNextChar()
{
    if (index >= characters.size()) return '\0';
    char c = characters[index++];
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return c;
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

void Lexer::throwLexicalError(const std::string& msg)
{
    throw std::runtime_error("Error Léxico [Línea " + std::to_string(line) + 
                           ", Columna " + std::to_string(column) + "]: " + msg);
}

int Lexer::validateInteger(const std::string& str)
{
    try {
        long long value = std::stoll(str);
        if (value > std::numeric_limits<int>::max()) {
            throwLexicalError("Literal entero fuera de rango: " + str + 
                            " (máximo: " + std::to_string(std::numeric_limits<int>::max()) + ")");
        }
        if (value < std::numeric_limits<int>::min()) {
            throwLexicalError("Literal entero fuera de rango: " + str + 
                            " (mínimo: " + std::to_string(std::numeric_limits<int>::min()) + ")");
        }
        return static_cast<int>(value);
    }
    catch (const std::out_of_range&) {
        throwLexicalError("Literal entero fuera de rango: " + str);
    }
    return 0;
}

int Lexer::getNextToken(proyecto::Parser::value_type *yyval)
{
    State currentState = S0;
    buffer = "";

    char currentChar = getNextChar();
    if (currentChar == '\0') return proyecto::Parser::token::YYEOF;

    while (true)
    {
        switch (currentState)
        {
        case S0: 
            if ((currentChar >= 9 && currentChar <= 10) || currentChar == 13 || currentChar == 32)
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S1; 
            }
            else if (currentChar == '"')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Cadena sin cerrar");
                currentState = S15;
            }
            else if (currentChar == '+')
            {
                buffer += currentChar;
                return proyecto::Parser::token::PLUS;
            }
            else if (currentChar == '-')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::MINUS;
                currentState = S2; 
            }
            else if (currentChar == '*')
            {
                buffer += currentChar;
                return proyecto::Parser::token::MULT;
            }
            else if (currentChar == '/')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::DIV;
                currentState = S3; 
            }
            else if (currentChar == '%')
            {
                buffer += currentChar;
                return proyecto::Parser::token::MOD;
            }
            else if (currentChar == '=')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::ASSIGN;
                currentState = S4; 
            }
            else if (currentChar == '!')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::NOT;
                currentState = S5; 
            }
            else if (currentChar == '<')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::LESS_THAN;
                currentState = S6; 
             }
            else if (currentChar == '>')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::GREATER_THAN;
                currentState = S7; 
            }
            else if (currentChar == '&')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Se esperaba '&' después de '&'");
                currentState = S8;
            }
            else if (currentChar == '|')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Se esperaba '|' después de '|'");
                currentState = S9; 
            }
            else if (currentChar == ';')
            {
                buffer += currentChar;
                return proyecto::Parser::token::SEMICOLON;
            }
            else if (currentChar == ',')
            {
                buffer += currentChar;
                return proyecto::Parser::token::COMMA;
            }
            else if (currentChar == '(')
            {
                buffer += currentChar;
                return proyecto::Parser::token::OP_PAR;
            }
            else if (currentChar == ')')
            {
                buffer += currentChar;
                return proyecto::Parser::token::CLOSE_PAR;
            }
            else if (currentChar == '{')
            {
                buffer += currentChar;
                return proyecto::Parser::token::OP_BRACE;
            }
            else if (currentChar == '}')
            {
                buffer += currentChar;
                return proyecto::Parser::token::CLOSE_BRACE;
            }
            else if (currentChar == '[')
            {
                buffer += currentChar;
                return proyecto::Parser::token::OP_BRACKET;
            }
            else if (currentChar == ']')
            {
                buffer += currentChar;
                return proyecto::Parser::token::CLOSE_BRACKET;
            }
            else if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') {
                    int value = validateInteger(buffer);
                    *yyval = new IntegerExpr(value);                    
                    return proyecto::Parser::token::INTEGER;
                }
                currentState = S10; 
            }
else if (std::isalpha(currentChar) || currentChar == '_')
{
    buffer += currentChar;
    int startColumn = column - 1;  
    currentChar = getNextChar();
    if (currentChar == '\0') {
        VarExpression* var = new VarExpression(buffer, line, startColumn);  
        *yyval = var;
        return proyecto::Parser::token::IDENTIFIER;
    }
    currentState = S11;
}
            else
            {
                throwLexicalError("Carácter inválido: '" + std::string(1, currentChar) + "'");
            }
            break;

        case S1: 
            currentState = S0;
            break;

        case S2: 
            if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') {
                    int value = validateInteger(buffer);
                    *yyval = new IntegerExpr(value);
                    return proyecto::Parser::token::INTEGER;
                }
                currentState = S10;
            }
            else
            {
                index--;
                column--;
                return proyecto::Parser::token::MINUS;
            }
            break;

        case S3: 
            if (currentChar == '/')
            {
                buffer = "";
                currentState = S12; 
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
            }
            else if (currentChar == '*')
            {
                buffer = "";
                currentState = S13; 
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Comentario multilínea sin cerrar");
            }
            else
            {
                index--;
                column--;
                return proyecto::Parser::token::DIV;
            }
            break;

        case S4: 
            if (currentChar == '=')
            {
                buffer += currentChar;
                return proyecto::Parser::token::EQUAL;
            }
            else
            {
                index--;
                column--;
                return proyecto::Parser::token::ASSIGN;
            }
            break;

        case S5: 
            if (currentChar == '=')
            {
                buffer += currentChar;
                return proyecto::Parser::token::DISTINCT;
            }
            else
            {
                index--;
                column--;
                return proyecto::Parser::token::NOT;
            }
            break;

        case S6: 
            if (currentChar == '=')
            {
                buffer += currentChar;
                return proyecto::Parser::token::LESS_EQUAL;
            }
            else
            {
                index--;
                column--;
                return proyecto::Parser::token::LESS_THAN;
            }
            break;

        case S7: 
            if (currentChar == '=')
            {
                buffer += currentChar;
                return proyecto::Parser::token::GREATER_EQUAL;
            }
            else
            {
                index--;
                column--;
                return proyecto::Parser::token::GREATER_THAN;
            }
            break;

        case S8: 
            if (currentChar == '&')
            {
                buffer += currentChar;
                return proyecto::Parser::token::AND;
            }
            else
            {
                throwLexicalError("Se esperaba '&' después de '&', se encontró '" + 
                                std::string(1, currentChar) + "'");
            }
            break;

        case S9: 
            if (currentChar == '|')
            {
                buffer += currentChar;
                return proyecto::Parser::token::OR;
            }
            else
            {
                throwLexicalError("Se esperaba '|' después de '|', se encontró '" + 
                                std::string(1, currentChar) + "'");
            }
            break;

        case S10: 
            if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') {
                    int value = validateInteger(buffer);
                    *yyval = new IntegerExpr(value);
                    return proyecto::Parser::token::INTEGER;
                }
                currentState = S10;
            }
            else if (currentChar == '.')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Número flotante incompleto");
                currentState = S20;
            }
            else
            {
                index--;
                column--;
                int value = validateInteger(buffer);
                *yyval = new IntegerExpr(value);
                return proyecto::Parser::token::INTEGER;
            }
            break;

        case S20:
            if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') {
                    *yyval = new FloatExpr(std::stof(buffer));
                    return proyecto::Parser::token::FLOAT;
                }
                currentState = S20;
            }
            else
            {
                index--;
                column--;
                *yyval = new FloatExpr(std::stof(buffer));
                return proyecto::Parser::token::FLOAT;
            }
            break;

        case S11: 
            if (std::isalnum(currentChar) || currentChar == '_')
            {
                buffer += currentChar;
                currentChar = getNextChar();
if (currentChar == '\0')
{
    if (buffer == "if") return proyecto::Parser::token::KW_IF;
    if (buffer == "else") return proyecto::Parser::token::KW_ELSE;
    if (buffer == "while") return proyecto::Parser::token::KW_WHILE;
    if (buffer == "int") return proyecto::Parser::token::KW_INT;
    if (buffer == "print") return proyecto::Parser::token::KW_PRINT;
    if (buffer == "input") return proyecto::Parser::token::KW_INPUT;

    VarExpression* var = new VarExpression(buffer, line, column - buffer.length());  // ← FIX
    *yyval = var;
    return proyecto::Parser::token::IDENTIFIER;
}
                currentState = S11;
            }
else
{
    index--;
    column--;
    if (buffer == "if") return proyecto::Parser::token::KW_IF;
    if (buffer == "else") return proyecto::Parser::token::KW_ELSE;
    if (buffer == "while") return proyecto::Parser::token::KW_WHILE;
    if (buffer == "int") return proyecto::Parser::token::KW_INT;
    if (buffer == "print") return proyecto::Parser::token::KW_PRINT;
    if (buffer == "input") return proyecto::Parser::token::KW_INPUT;

    VarExpression* var = new VarExpression(buffer, line, column - buffer.length() + 1);  // ← FIX
    *yyval = var;
    return proyecto::Parser::token::IDENTIFIER;
}
            break;

        case S12: 
            if (currentChar == '\n' || currentChar == '\r')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                buffer = "";
                currentState = S0;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S12;
            }
            break;

        case S13: 
            if (currentChar == '*')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Comentario multilínea sin cerrar");
                currentState = S14;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Comentario multilínea sin cerrar");
                currentState = S13;
            }
            break;

        case S14: 
            if (currentChar == '/')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                buffer = "";
                currentState = S0;
            }
            else if (currentChar == '*')
            {
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Comentario multilínea sin cerrar");
                currentState = S14;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Comentario multilínea sin cerrar");
                currentState = S13;
            }
            break;

        case S15: 
if (currentChar == '"')
{
    buffer += currentChar;
    VarExpression* var = new VarExpression(buffer, line, column - buffer.length());  // ← FIX
    *yyval = var;
    return proyecto::Parser::token::IDENTIFIER;
}
            else if (currentChar == '\\')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Cadena sin cerrar");
                buffer += currentChar; 
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Cadena sin cerrar");
                currentState = S15;
            }
            else if (currentChar == '\n')
            {
                throwLexicalError("Cadena sin cerrar antes del salto de línea");
            }
            else
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') 
                    throwLexicalError("Cadena sin cerrar");
                currentState = S15;
            }
            break;
        }
    }
}