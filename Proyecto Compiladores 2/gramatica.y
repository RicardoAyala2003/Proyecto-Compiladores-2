%language "C++"
%require "3.2"
%define parse.error verbose

%code requires {
    #include <string>
    #include "ast.hpp"
    class Lexer;
}

%{
    #include "Lexer.hpp"
    #define yylex(v) lexer.getNextToken(v)

    std::string lastKeyword = "";

    void proyecto::Parser::error(const std::string& msg) {
        std::string buffer = lexer.getBuffer();
        int line = lexer.getLine();
        int col = lexer.getColumn();

        std::string errorMsg = "Error Sintáctico [Línea " + std::to_string(line) +
                              ", Columna " + std::to_string(col) + "]";
        errorMsg += ": " + msg;

        lastKeyword = "";
        throw std::runtime_error(errorMsg);
    }
%}

%parse-param {Lexer &lexer}
%parse-param {AstNode*& astN}

%define api.namespace {proyecto}
%define api.parser.class {Parser}
%define api.value.type {AstNode*}

%token IDENTIFIER INTEGER FLOAT
%token KW_INT KW_IF KW_ELSE KW_WHILE KW_PRINT KW_INPUT
%token ASSIGN SEMICOLON COMMA
%token OP_PAR CLOSE_PAR OP_BRACE CLOSE_BRACE OP_BRACKET CLOSE_BRACKET
%token PLUS MINUS MULT DIV MOD
%token LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL EQUAL DISTINCT
%token AND OR NOT
%token DOT

%nonassoc THEN
%nonassoc KW_ELSE

%%

program
    : opt_statement_list { astN = new Program($1); }
    ;

opt_statement_list
    : statement_list { $$ = $1; }
    | %empty { $$ = new StatementList({}); }
    ;

statement_list
    : statement_list statement {
        $$ = $1;
        reinterpret_cast<StatementList*>($$)->stmts.push_back($2);
      }
    | statement {
        $$ = new StatementList({});
        reinterpret_cast<StatementList*>($$)->stmts.push_back($1);
      }
    ;

statement
    : var_decl
    | assignment
    | if_stmt
    | while_stmt
    | print_stmt
    | input_stmt
    | block
    | array_decl
    ;

var_decl
    : KW_INT ident_decl opt_ident_list SEMICOLON {
        $$ = new VarDeclStmt($2, $3);
      }
    | KW_INT error SEMICOLON %prec THEN
    ;

opt_ident_list
    : opt_ident_list COMMA ident_decl {
        $$ = $1;
        reinterpret_cast<IdentList*>($$)->idents.push_back($3);
      }
    | %empty { $$ = new IdentList({}); }
    ;

ident_decl
    : IDENTIFIER opt_assign_expr {
        $$ = new IdentDecl($1, $2);
      }
    ;

opt_assign_expr
    : ASSIGN expression { $$ = $2; }
    | %empty { $$ = nullptr; }
    ;

assignment
    : IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = new AssignmentStmt($1, $3);
      }
    | IDENTIFIER ASSIGN error %prec THEN
    ;

if_kw
    : KW_IF { lastKeyword = "if"; }
    ;

while_kw
    : KW_WHILE { lastKeyword = "while"; }
    ;

print_kw
    : KW_PRINT { lastKeyword = "print"; }
    ;

input_kw
    : KW_INPUT { lastKeyword = "input"; }
    ;

if_stmt
    : if_kw OP_PAR expression CLOSE_PAR statement %prec THEN {
        lastKeyword = "";
        $$ = new IfStmt($3, $5, nullptr);
      }
    | if_kw OP_PAR expression CLOSE_PAR statement KW_ELSE statement {
        lastKeyword = "";
        $$ = new IfStmt($3, $5, $7);
      }
    | if_kw OP_PAR expression error statement KW_ELSE statement %prec THEN
    | if_kw error expression CLOSE_PAR statement KW_ELSE statement %prec THEN
    | if_kw error expression CLOSE_PAR statement %prec THEN
    | if_kw OP_PAR expression error statement %prec THEN
    ;

while_stmt
    : while_kw OP_PAR expression CLOSE_PAR statement {
        lastKeyword = "";
        $$ = new WhileStmt($3, $5);
      }
    | while_kw OP_PAR expression error statement %prec THEN
    | while_kw error expression CLOSE_PAR statement %prec THEN
    ;

print_stmt
    : print_kw OP_PAR expression CLOSE_PAR SEMICOLON {
        lastKeyword = "";
        $$ = new PrintStmt($3);
      }
    | print_kw error expression CLOSE_PAR SEMICOLON %prec THEN
    ;

input_stmt
    : input_kw OP_PAR CLOSE_PAR {
        lastKeyword = "";
        $$ = new InputStmt();
      }
    | input_kw OP_PAR error CLOSE_PAR %prec THEN
    | input_kw error CLOSE_PAR %prec THEN
    ;

block
    : OP_BRACE opt_statement_list CLOSE_BRACE {
        $$ = new BlockStmt($2);
      }
    | OP_BRACE error CLOSE_BRACE %prec THEN
    ;

expression
    : logical_or | error
    ;

logical_or
    : logical_or OR logical_and {
        $$ = new BinaryExpr($1, BinaryOperator::OR, $3);
      }
    | logical_and
    ;

logical_and
    : logical_and AND equality {
        $$ = new BinaryExpr($1, BinaryOperator::AND, $3);
      }
    | equality
    ;

equality
    : equality EQUAL comparison {
        $$ = new BinaryExpr($1, BinaryOperator::EQUAL, $3);
      }
    | equality DISTINCT comparison {
        $$ = new BinaryExpr($1, BinaryOperator::DISTINCT, $3);
      }
    | comparison
    ;

comparison
    : comparison LESS_THAN term {
        $$ = new BinaryExpr($1, BinaryOperator::LESS_THAN, $3);
      }
    | comparison GREATER_THAN term {
        $$ = new BinaryExpr($1, BinaryOperator::GREATER_THAN, $3);
      }
    | comparison LESS_EQUAL term {
        $$ = new BinaryExpr($1, BinaryOperator::LESS_EQUAL, $3);
      }
    | comparison GREATER_EQUAL term {
        $$ = new BinaryExpr($1, BinaryOperator::GREATER_EQUAL, $3);
      }
    | term
    ;

term
    : term PLUS factor {
        $$ = new BinaryExpr($1, BinaryOperator::PLUS, $3);
      }
    | term MINUS factor {
        $$ = new BinaryExpr($1, BinaryOperator::MINUS, $3);
      }
    | factor
    ;

factor
    : factor MULT unary {
        $$ = new BinaryExpr($1, BinaryOperator::MULT, $3);
      }
    | factor DIV unary {
        $$ = new BinaryExpr($1, BinaryOperator::DIV, $3);
      }
    | factor MOD unary {
        $$ = new BinaryExpr($1, BinaryOperator::MOD, $3);
      }
    | unary
    ;

unary
    : NOT unary {
        $$ = new UnaryExpr(UnaryOperator::NOT, $2);
      }
    | MINUS unary {
        $$ = new UnaryExpr(UnaryOperator::NEGATE, $2);
      }
    | primary
    ;

primary
    : INTEGER
    | FLOAT
    | IDENTIFIER
    | input_stmt
    | OP_PAR expression CLOSE_PAR { $$ = new ParExpr($2); }
    ;

array
    : OP_BRACKET expression CLOSE_BRACKET {
        $$ = new ArrayAccess($2);
      }
    ;

array_decl
    : KW_INT IDENTIFIER array SEMICOLON {
        $$ = new ArrayDeclStmt($2, $3);
      }
    | KW_INT IDENTIFIER error SEMICOLON %prec THEN
    | KW_INT error array SEMICOLON %prec THEN
    | array
    ;

%%
