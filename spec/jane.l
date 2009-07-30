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
\;                          return TOK_SEMI;
\{                          return TOK_OBRACE;
\}                          return TOK_EBRACE;
\=                          return TOK_ASSIGN;
\:\=                        return TOK_DECLARE;
\+                          return TOK_ADD;
\-                          return TOK_SUB;
\*                          return TOK_MUL;
\/                          return TOK_DIV;
[_a-zA-Z][_a-zA-Z0-9]*      yylval.string=strdup(yytext);return TOK_IDENTIFIER;
\n                          ;
[ \t]                       ;
.                           return (int) yytext;
%%
