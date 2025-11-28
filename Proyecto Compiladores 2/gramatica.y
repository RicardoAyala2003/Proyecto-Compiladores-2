%language "C++"
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

%token DOT FLOAT CLOSE_BRACKET OP_BRACKET KW_INT KW_IF KW_ELSE KW_WHILE KW_PRINT KW_INPUT IDENTIFIER INTEGER ASSIGN SEMICOLON COMMA OP_PAR CLOSE_PAR OP_BRACE CLOSE_BRACE PLUS MINUS MULT DIV MOD LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL EQUAL DISTINCT AND OR NOT 

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
         |multi_array
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
       | FLOAT
;

array: OP_BRACKET expression CLOSE_BRACKET

;

multi_array: kw IDENTIFIER array SEMICOLON
           | array
;


kw: INTEGER | FLOAT
;

%%