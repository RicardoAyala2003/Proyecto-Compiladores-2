#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../ast.hpp"
#include "../Lexer.hpp"
#include "../Parser.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <iostream>

namespace fs = std::filesystem;

std::string readFile(const fs::path& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("No se pudo abrir el archivo: " + filepath.string());
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

TEST_CASE("Compilar y generar código C++ para todos los ejemplos") {
    fs::path ejemplosDir = "../ejemplos";
    
    for (auto& entry : fs::directory_iterator(ejemplosDir)) {
        if (entry.path().extension() == ".c") {
            std::string filename = entry.path().filename().string();
            
            CAPTURE(filename);
            
            SUBCASE(filename.c_str()) {
                MESSAGE("Procesando archivo: ", filename);
                
                std::string source = readFile(entry.path());
                std::vector<char> input(source.begin(), source.end());
                Lexer lexer(input);
                AstNode* ast = nullptr;
                proyecto::Parser parser(lexer, ast);
                
                // Archivos que deben fallar con errores semánticos
                bool shouldFailSemantic = (filename.find("undeclared") != std::string::npos ||
                                          filename.find("redeclaration") != std::string::npos);
                
                if (shouldFailSemantic) {
                    // Primero parseamos (esto debería funcionar)
                    CHECK_NOTHROW(parser.parse());
                    REQUIRE(ast != nullptr);
                    
                    // Luego intentamos generar código (aquí debe fallar)
                    std::unordered_set<std::string> varSet;
                    CHECK_THROWS_AS(ast->toCpp(varSet), std::runtime_error);
                    MESSAGE("✓ Error semántico esperado detectado en: ", filename);
                    
                } else {
                    // Archivos que deben compilar correctamente
                    CHECK_NOTHROW(parser.parse());
                    REQUIRE(ast != nullptr);
                    
                    std::unordered_set<std::string> varSet;
                    std::string cppCode;
                    CHECK_NOTHROW(cppCode = ast->toCpp(varSet));
                    CHECK_FALSE(cppCode.empty());
                    MESSAGE("✓ Compilado exitosamente: ", filename);
                }
            }
        }
    }
}