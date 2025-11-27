#include <iostream>
#include <fstream>
#include <vector>
#include "Parser.hpp"
#include "Lexer.hpp"

//prueba commit de prueba
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "ERROR\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "No se pudo abrir el archivo ERROR\n";
        return 1;
    }

    std::vector<char> input((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    file.close();

    try
    {
        Lexer lex(input);
        proyecto::Parser parse(lex);
        parse();
    }
    catch (const proyecto::Parser::syntax_error& e)
    {
        std::cerr << "Syntax error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}