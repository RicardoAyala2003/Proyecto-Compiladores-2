#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>

class Lexer
{
private:
    std::vector<char> characters;
    int index;
    std::string buffer;

    char getNextChar();
    char checkNextChar();

public:
    Lexer(std::vector<char> input);
    std::string getBuffer();
    std::string getNextToken();
};

#endif // LEXER_HPP