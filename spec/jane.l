%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "y.tab.h"
%}

%%
[0-9]+                      yylval.number=atoi(yytext);return TOK_NUMBER;
print                       return TOK_PRINT;
if                          return TOK_IF;
while                       return TOK_WHILE;
stop                        return TOK_STOP;
next                        return TOK_NEXT;
true                        yylval.number=1;return TOK_BOOLEAN;
false                       yylval.number=0;return TOK_BOOLEAN;
\;                          return TOK_SEMI;
\{                          return TOK_OBRACE;
\}                          return TOK_EBRACE;
\=                          return TOK_ASSIGN;
\:\=                        return TOK_DECLARE;
\+                          return TOK_ADD;
\-                          return TOK_SUB;
\*                          return TOK_MUL;
\/                          return TOK_DIV;
\>                          return TOK_GREATER;
\<                          return TOK_LESS;
\=\=                        return TOK_EQUAL;
\>\=                        return TOK_GREATER_EQUAL;
\<\=                        return TOK_LESS_EQUAL;
\!\=                        return TOK_NOT_EQUAL;
\|\|                        return TOK_OR;
\&\&                        return TOK_AND;
\!                          return TOK_NOT;
[_a-zA-Z][_a-zA-Z0-9]*      yylval.string=strdup(yytext);return TOK_IDENTIFIER;
\n                          ;
[ \t]                       ;
.                           return (int) yytext;
%%
