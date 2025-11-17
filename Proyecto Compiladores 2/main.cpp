#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "Lexer.hpp"

std::vector<char> loadFileContent(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<char> content;

    if (!file)
    {
        std::cerr << "Error: Cannot open file '" << filename << "'\n";
        return content;
    }

    char ch;
    while (file.get(ch))
    {
        content.push_back(ch);
    }

    file.close();
    return content;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        std::cerr << "Example: " << argv[0] << " test.txt\n";
        return 1;
    }

    std::string filename = argv[1];
    std::vector<char> fileChars = loadFileContent(filename);

    if (fileChars.empty())
    {
        std::cerr << "Error: File is empty or could not be read.\n";
        return 1;
    }

    std::cout << "======================================\n";
    std::cout << "Analyzing file: " << filename << "\n";
    std::cout << "======================================\n\n";

    Lexer lexer(fileChars);
    std::string tokenType;
    int tokenCount = 0;

    std::cout << std::left << std::setw(20) << "TOKEN TYPE" 
              << std::setw(30) << "LEXEME" << "\n";
    std::cout << "------------------------------------------------------\n";

    while ((tokenType = lexer.getNextToken()) != "EOF") 
    {
        tokenCount++;
        std::string lexeme = lexer.getBuffer();
        
        // Mostrar el token con formato
        std::cout << std::left << std::setw(20) << tokenType 
                  << std::setw(30) << ("\"" + lexeme + "\"") << "\n";
    }

    std::cout << "------------------------------------------------------\n";
    std::cout << "Total tokens found: " << tokenCount << "\n";
    std::cout << "======================================\n";

    return 0;
}