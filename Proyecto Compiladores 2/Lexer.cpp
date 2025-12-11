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
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
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
             }else if (currentChar == '>')
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
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S8;
            }
            else if (currentChar == '|')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
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
            else if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') {
                    *yyval = new IntegerExpr(std::stoi(buffer));                    
                    return proyecto::Parser::token::INTEGER;}
                currentState = S10; 
            }
            else if (std::isalpha(currentChar) || currentChar == '_')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') {
                    *yyval = new VarExpression(buffer);
                    return proyecto::Parser::token::IDENTIFIER;}
                currentState = S11;
            }
            else
            {
                buffer += currentChar;
                return proyecto::Parser::token::YYEOF;
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
               *yyval = new IntegerExpr(std::stoi(buffer));
                    return proyecto::Parser::token::INTEGER;}
                currentState = S10;
            }
            else
            {
                index--;
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
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
            }
            else
            {
                index--;
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
                return proyecto::Parser::token::YYEOF;
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
                return proyecto::Parser::token::YYEOF;
            }
            break;

        case S10: 
            if (std::isdigit(currentChar))
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') {
                    *yyval = new IntegerExpr(std::stoi(buffer));
                    return proyecto::Parser::token::INTEGER;}
                currentState = S10;
            }
            else
            {
                index--;
                *yyval = new IntegerExpr(std::stoi(buffer));
                return proyecto::Parser::token::INTEGER;
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
        
                     *yyval = new VarExpression(buffer);
                    return proyecto::Parser::token::IDENTIFIER;
                    
                }
                currentState = S11;
            }
            else
            {
                index--;
                if (buffer == "if") return proyecto::Parser::token::KW_IF;
                if (buffer == "else") return proyecto::Parser::token::KW_ELSE;
                if (buffer == "while") return proyecto::Parser::token::KW_WHILE;
                if (buffer == "int") return proyecto::Parser::token::KW_INT;
                if (buffer == "print") return proyecto::Parser::token::KW_PRINT;
                if (buffer == "input") return proyecto::Parser::token::KW_INPUT;

                 *yyval = new VarExpression(buffer);
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
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S14;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
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
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S14;
            }
            else
            {
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S13;
            }
            break;

        case S15: 
            if (currentChar == '"')
            {
                buffer += currentChar;
                 *yyval = new VarExpression(buffer);
                return proyecto::Parser::token::IDENTIFIER;
            }
            else if (currentChar == '\\')
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                buffer += currentChar; 
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S15;
            }
            else if (currentChar == '\n')
            {
                return proyecto::Parser::token::YYEOF; 
            }
            else
            {
                buffer += currentChar;
                currentChar = getNextChar();
                if (currentChar == '\0') return proyecto::Parser::token::YYEOF;
                currentState = S15;
            }
            break;
        }
    }
}