#ifndef LEXER_HPP
#define LEXER_HPP
#include "Parser.hpp"
#include <vector>
#include <string>

class Lexer
{
private:
    enum State
    {
        S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15,S20
    };
    std::vector<char> characters;
    int index;
    std::string buffer;
    char getNextChar();
    char checkNextChar();
public:
    Lexer(std::vector<char> input);
    std::string getBuffer();
    int getNextToken(proyecto::Parser::value_type *yyval);
};

#endif