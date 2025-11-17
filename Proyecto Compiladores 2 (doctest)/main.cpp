#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Lexer.hpp"

std::vector<char> loadFileContent(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<char> content;

    if (!file)
    {
        std::cerr << "Cannot open file.\n";
        return content;
    }

    char ch;
    while (file.get(ch))
    {
        content.push_back(ch);
    }

    return content;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./program <filename>\n";
        return 1;
    }

    std::vector<char> fileChars = loadFileContent(argv[1]);

    Lexer lexer(fileChars);

    std::string tokenType;

    while ((tokenType = lexer.getNextToken()) != "EOF") 
    {
        std::cout << tokenType << " >> " << lexer.getBuffer() << "\n";
    }

    return 0;
}