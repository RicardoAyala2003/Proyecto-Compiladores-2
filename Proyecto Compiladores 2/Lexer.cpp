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
        case 0: 
            if ((currentChar >= 9 && currentChar <= 10) || currentChar == 13 || currentChar == 32)
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return "EOF";
                currentState = 1; 
            }
            else if (currentChar == '"')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 15;
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
                currentState = 2; 
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
                currentState = 3; 
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
                currentState = 4; 
            }
            else if (currentChar == '!')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_NOT";
                currentState = 5; 
            }
            else if (currentChar == '<')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_LT";
                currentState = 6; 
             }else if (currentChar == '>')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "OP_GT";
                currentState = 7; 
            }
            else if (currentChar == '&')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 8;
            }
            else if (currentChar == '|')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 9; 
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
            else if (currentChar == '[')
            {
            buffer += currentChar;  
            currentChar = getNextChar();    
            currentState= 100;
               
            }
            else if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "INTEGER";
                currentState = 10; 
            }
            else if (std::isalpha(currentChar) || currentChar == '_')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "IDENTIFIER";
                currentState = 11;
            }
            else
            {
                buffer += currentChar;
                return "ERROR";
            }
            break;

        case 100:
              if (ch!= ']')
            {
                buffer += currentChar;
                currentChar = getNextChar();
               if (currentChar == '\0') return "ERROR";
                currentState = 100;
            } else {
                return "BRACKET_IDENT";
               }

        case 1: 
            currentState = 0;
            break;

        case 2: 
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

        case 3: 
            if (currentChar == '/')
            {
                buffer = "";
                currentState = 12; 
                currentChar = getNextChar();
                if (currentChar == '\0') return "EOF";
            }
            else if (currentChar == '*')
            {
                buffer = "";
                currentState = 13; 
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
            }
            else
            {
                index--;
                return "OP_DIV";
            }
            break;

        case 4: 
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

        case 5: 
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

        case 6: 
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

        case 7: 
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

        case 8: 
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

        case 9: 
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

        case 10: 
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

        case 11: 
            if (std::isalnum(currentChar) || currentChar == '_')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0')
                {
                  
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

        case 12: 
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

        case 13: 
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

        case 14: 
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

        case 15: 
            if (currentChar == '"')
            {
                buffer += currentChar;
                return "STRING_LITERAL";
            }
            else if (currentChar == '\\')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                buffer += currentChar; 
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 15;
            }
            else if (currentChar == '\n')
            {
                return "ERROR"; 
            }
            else
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return "ERROR";
                currentState = 15;
            }
            break;
        }
    }
}

