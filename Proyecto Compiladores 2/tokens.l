%%
/* PATTERN */                    /* ACTION */
"+"                              return OP_ADD;
"-"                              return OP_SUB;
"*"                              return OP_MUL;
"/"                              return OP_DIV;
"%"                              return OP_MOD;
"=="                             return OP_EQ;
"!="                             return OP_NE;
"<="                             return OP_LE;
">="                             return OP_GE;
"<"                              return OP_LT;
">"                              return OP_GT;
"&&"                             return OP_AND;
"||"                             return OP_OR;
"!"                              return OP_NOT;
"="                              return OP_ASSIGN;
";"                              return SEMICOLON;
","                              return COMMA;
"("                              return LPAREN;
")"                              return RPAREN;
"{"                              return LBRACE;
"}"                              return RBRACE;
/* String Literals - DEBE IR ANTES de identificadores */
\"([^\\\"\n]|\\[^\n])*\"         return STRING_LITERAL;
/* Literales Enteros (con signo opcional) */
-?[0-9]+                         return CONST_INTEGER;
/* Identificadores (después de palabras reservadas) */
[a-zA-Z_][a-zA-Z0-9_]*           return IDENTIFIER;
/* Espacios en blanco */
[ \t\r\n]+                       /* no action: ignore all white space */
/* Comentarios de una línea */
"//".*                           /* no action: ignore single-line comments */
/* Caracteres no reconocidos */
.                                return ERROR;
%%