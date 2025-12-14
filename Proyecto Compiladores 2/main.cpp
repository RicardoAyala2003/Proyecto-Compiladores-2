#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "Parser.hpp"
#include "Lexer.hpp"
#include "ast.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "No se pudo abrir el archivo: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<char> input((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    file.close();

    try
    {
        Lexer lex(input);
        AstNode* ast = nullptr;
        proyecto::Parser parse(lex, ast);
        parse();
        
        if (ast != nullptr)
        {
            std::ofstream out("codigo.cpp");
            if (!out)
            {
                std::cerr << "No se pudo crear el archivo de salida: " << "codigo.cpp" << std::endl;
                return 1;
            }
            
            std::unordered_set<std::string> varSet;
            out << ast->toCpp(varSet);
            out.close();
            
            std::cout << "Compilacion exitosa! Codigo generado en: " << "codigo.cpp" << std::endl;
        }
        else
        {
            std::cerr << "Error: No se pudo construir el AST" << std::endl;
            return 1;
        }
    }
    catch (const proyecto::Parser::syntax_error& e)
    {
        std::cerr << "Error de sintaxis: " << e.what()<< std::endl;
        return 1;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Error desconocido" << std::endl;
        return 1;
    }

    return 0;
}