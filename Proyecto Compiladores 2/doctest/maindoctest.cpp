#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../ast.hpp"
#include "../Lexer.hpp"
#include "../Parser.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

namespace fs = std::filesystem;

std::string readFile(const fs::path& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo: " + filepath.string());
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

TEST_CASE("Parsear todos los ejemplos en ejemplos/") {
    fs::path ejemplosDir = "ejemplos";

    for (auto& entry : fs::directory_iterator(ejemplosDir)) {
        if (entry.path().extension() == ".c") {
            std::string source = readFile(entry.path());
            std::vector<char> chars(source.begin(), source.end());

            Lexer lexer(chars);
            proyecto::Parser parser;
            AstNode* ast = nullptr;

            SUBCASE(entry.path().filename().string().c_str()) {
                // Intentar parsear
                REQUIRE_NOTHROW(parser.parse(lexer, ast));
                REQUIRE(ast != nullptr);

                // Intentar generar código C++
                std::unordered_set<std::string> varSet;
                std::string cppCode;
                REQUIRE_NOTHROW(cppCode = ast->toCpp(varSet));
                CHECK(!cppCode.empty());
            }
        }
    }
}
