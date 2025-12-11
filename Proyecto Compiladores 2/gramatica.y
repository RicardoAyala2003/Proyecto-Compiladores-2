/*%language "C++"
%require "3.2"
%code requires{
class Lexer;
}
%{
#include "Lexer.hpp"
#define yylex(p) lexer.getNextToken(p)  

void proyecto::Parser::error(const std::string& msg)
{       
    throw std::runtime_error("Error: " + msg + "\n");
}
%}

%define api.namespace{proyecto}
%define api.parser.class{Parser}
%define api.value.type variant
%parse-param {Lexer& lexer}

%token KW_INT KW_IF KW_ELSE KW_WHILE KW_PRINT KW_INPUT IDENTIFIER INTEGER ASSIGN SEMICOLON COMMA OP_PAR CLOSE_PAR OP_BRACE CLOSE_BRACE PLUS MINUS MULT DIV MOD LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL EQUAL DISTINCT AND OR NOT

%nonassoc THEN
%nonassoc KW_ELSE

%%

program: opt_statement_list
;

opt_statement_list: statement_list
                  | %empty
;

statement_list: statement_list statement
              | statement
;

statement: var_decl
         | assignment
         | if_stmt
         | while_stmt
         | print_stmt
         | block
;

var_decl: KW_INT ident_decl opt_ident_list SEMICOLON
;

assignment: IDENTIFIER ASSIGN expression SEMICOLON
;

opt_ident_list: opt_ident_list COMMA ident_decl
              | %empty
;

ident_decl: IDENTIFIER opt_assign_expr
;

opt_assign_expr: ASSIGN expression
               | %empty
;

if_stmt: KW_IF OP_PAR expression CLOSE_PAR statement %prec THEN
       | KW_IF OP_PAR expression CLOSE_PAR statement KW_ELSE statement
;

while_stmt: KW_WHILE OP_PAR expression CLOSE_PAR statement
;

print_stmt: KW_PRINT OP_PAR expression CLOSE_PAR SEMICOLON
;

input_stmt: KW_INPUT OP_PAR CLOSE_PAR
;

block: OP_BRACE opt_statement_list CLOSE_BRACE
;

expression: logical_or
;

logical_or: logical_or OR logical_and
          | logical_and
;

logical_and: logical_and AND equality
           | equality
;

equality: equality EQUAL comparison
        | equality DISTINCT comparison
        | comparison
;

comparison: comparison LESS_THAN term
          | comparison GREATER_THAN term
          | comparison LESS_EQUAL term
          | comparison GREATER_EQUAL term
          | term
;

term: term PLUS factor
    | term MINUS factor
    | factor
;

factor: factor MULT unary
      | factor DIV unary
      | factor MOD unary
      | unary
;

unary: NOT unary
     | MINUS unary
     | primary
;

primary: INTEGER
       | IDENTIFIER
       | input_stmt
       | OP_PAR expression CLOSE_PAR
;

%%*/

%language "C++"
%require "3.2"

%code requires {
    #include <string>
    #include "ast.hpp"
    class Lexer;
}

%{
    #include "Lexer.hpp"
    #define yylex(v) lexer.getNextToken(v)
    
    void proyecto::Parser::error(const std::string& msg) {
        throw std::runtime_error("Error: " + msg + "\n");
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

program: opt_statement_list { astN = new Program($1); }
;

opt_statement_list: statement_list { $$= $1; }
                  | %empty { $$= new StatementList({}); }
;

statement_list: statement_list statement { 
                    $$= $1; 
                    reinterpret_cast<StatementList*>($$)->stmts.push_back($2);
                }
              | statement { 
                    $$= new StatementList({});
                    reinterpret_cast<StatementList*>($$)->stmts.push_back($1);
                }
;

statement: var_decl { $$= $1; }
         | assignment { $$= $1; }
         | if_stmt { $$= $1; }
         | while_stmt { $$= $1; }
         | print_stmt { $$= $1; }
         | block { $$= $1; }
         | array_decl { $$= $1; }
;

var_decl: KW_INT ident_decl opt_ident_list SEMICOLON {
            $$= new VarDeclStmt($2, $3);
        }
;

opt_ident_list: opt_ident_list COMMA ident_decl {
                    $$= $1;
                    reinterpret_cast<IdentList*>($$)->idents.push_back($3);
                }
              | %empty {
                    $$= new IdentList({});
                }
;

ident_decl: IDENTIFIER opt_assign_expr {
                $$= new IdentDecl($1, $2);
            }
;

opt_assign_expr: ASSIGN expression { $$= $2; }
               | %empty { $$= nullptr; }
;

assignment: IDENTIFIER ASSIGN expression SEMICOLON {
                $$= new AssignmentStmt($1, $3);
            }
;

if_stmt: KW_IF OP_PAR expression CLOSE_PAR statement %prec THEN {
            $$= new IfStmt($3, $5, nullptr);
         }
       | KW_IF OP_PAR expression CLOSE_PAR statement KW_ELSE statement {
            $$= new IfStmt($3, $5, $7);
         }
;

while_stmt: KW_WHILE OP_PAR expression CLOSE_PAR statement {
                $$= new WhileStmt($3, $5);
            }
;

print_stmt: KW_PRINT OP_PAR expression CLOSE_PAR SEMICOLON {
                $$= new PrintStmt($3);
            }
;

input_stmt: KW_INPUT OP_PAR CLOSE_PAR {
                $$= new InputStmt();
            }
;

block: OP_BRACE opt_statement_list CLOSE_BRACE {
            $$= new BlockStmt($2);
       }
;

expression: logical_or { $$= $1; }
;

logical_or: logical_or OR logical_and {
                $$= new BinaryExpr($1, BinaryOperator::OR, $3);
            }
          | logical_and { $$= $1; }
;

logical_and: logical_and AND equality {
                $$= new BinaryExpr($1, BinaryOperator::AND, $3);
             }
           | equality { $$= $1; }
;

equality: equality EQUAL comparison {
            $$= new BinaryExpr($1, BinaryOperator::EQUAL, $3);
          }
        | equality DISTINCT comparison {
            $$= new BinaryExpr($1, BinaryOperator::DISTINCT, $3);
          }
        | comparison { $$= $1; }
;

comparison: comparison LESS_THAN term {
                $$= new BinaryExpr($1, BinaryOperator::LESS_THAN, $3);
            }
          | comparison GREATER_THAN term {
                $$= new BinaryExpr($1, BinaryOperator::GREATER_THAN, $3);
            }
          | comparison LESS_EQUAL term {
                $$= new BinaryExpr($1, BinaryOperator::LESS_EQUAL, $3);
            }
          | comparison GREATER_EQUAL term {
                $$= new BinaryExpr($1, BinaryOperator::GREATER_EQUAL, $3);
            }
          | term { $$= $1; }
;

term: term PLUS factor {
        $$= new BinaryExpr($1, BinaryOperator::PLUS, $3);
      }
    | term MINUS factor {
        $$= new BinaryExpr($1, BinaryOperator::MINUS, $3);
      }
    | factor { $$= $1; }
;

factor: factor MULT unary {
            $$= new BinaryExpr($1, BinaryOperator::MULT, $3);
        }
      | factor DIV unary {
            $$= new BinaryExpr($1, BinaryOperator::DIV, $3);
        }
      | factor MOD unary {
            $$= new BinaryExpr($1, BinaryOperator::MOD, $3);
        }
      | unary { $$= $1; }
;

unary: NOT unary {
            $$= new UnaryExpr(UnaryOperator::NOT, $2);
       }
     | MINUS unary {
            $$= new UnaryExpr(UnaryOperator::NEGATE, $2);
       }
     | primary { $$= $1; }
;

primary: INTEGER { $$= $1; }
       | FLOAT { $$= $1; }
       | IDENTIFIER { $$= $1; }
       | input_stmt { $$= $1; }
       | OP_PAR expression CLOSE_PAR { $$= new ParExpr($2);  }
;

array: OP_BRACKET expression CLOSE_BRACKET {
            $$= new ArrayAccess($2);
       }
;

array_decl: KW_INT IDENTIFIER array SEMICOLON {
                $$= new ArrayDeclStmt($2, $3);
            }
          | array { $$= $1; }
;

%%