%{
#include<stdio.h>
#include "../include/ast.h"
#include "../src/y.tab.h"

void yyerror(const char *str)
{
    fprintf(stderr, "error: %s\n", str);
}

int yywrap()
{
    return 1;
}

int main()
{
    yyparse();
    return 0;
}

%}

%token TOK_DECLARE TOK_ASSIGN TOK_ADD TOK_SUB TOK_MUL TOK_DIV
%token TOK_GREATER TOK_LESS TOK_EQUAL TOK_GREATER_EQUAL TOK_LESS_EQUAL
%token TOK_NOT_EQUAL TOK_OR TOK_AND TOK_NOT

%token TOK_PRINT TOK_IF TOK_WHILE TOK_STOP TOK_NEXT

%token TOK_EBRACE TOK_OBRACE TOK_SEMI

%union
{
    int number;
    char* string;
    void* astval;
    void* astop;
}

%token <number> TOK_NUMBER 
%token <string> TOK_IDENTIFIER 
%token <number> TOK_BOOLEAN

%%

program: statements { compile_root($<astop>$); };

statements:
          statement {
            $<astop>$ = $<astop>1;
          }
          |
          statement statements {
            $<astop>$ = astop_next_set($<astop>1, $<astop>2);
          }
          ;

statement:
         statement_declare TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_assignment TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_print TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_while { $<astop>$ = $<astop>1; }
         |
         statement_stop TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_next TOK_SEMI { $<astop>$ = $<astop>1; }
         ;

statement_declare:
                     TOK_IDENTIFIER TOK_DECLARE expression  {
                        AstVal iden = astval_identifier_new($<string>1);
                        AstOp op = astop_new(OP_DECLARE, iden, $<astval>3);
                        $<astop>$ = op;
                     }
                     ;

statement_assignment:
                     TOK_IDENTIFIER TOK_ASSIGN expression  {
                        AstVal iden = astval_identifier_new($<string>1);
                        AstOp op = astop_new(OP_ASSIGN, iden, $<astval>3);
                        $<astop>$ = op;
                     }
                     ;

statement_print:
               TOK_PRINT expression { $<astop>$ = astop_new(OP_PRINT, $<astval>2, NULL); }
               ;

statement_while:
               TOK_WHILE expression TOK_OBRACE statements TOK_EBRACE {
                    $<astop>$ = astop_new(OP_WHILE, $<astval>2, astval_op_new($<astop>4));
               }
               ;

statement_stop:
              TOK_STOP { $<astop>$ = astop_new(OP_STOP, NULL, NULL); }
              ;

statement_next:
              TOK_NEXT { $<astop>$ = astop_new(OP_NEXT, NULL, NULL); }
              ;

expression:
          expression TOK_ADD factor { $<astval>$ = astval_op_new(astop_new(OP_ADD, $<astval>1, $<astval>3));}
          |
          expression TOK_SUB factor { $<astval>$ = astval_op_new(astop_new(OP_SUB, $<astval>1, $<astval>3));}
          |
          factor { $<astval>$ = $<astval>1; }
          ;

factor:
      factor TOK_MUL atom { $<astval>$ = astval_op_new(astop_new(OP_MUL, $<astval>1, $<astval>3)); }
      |
      factor TOK_DIV atom { $<astval>$ = astval_op_new(astop_new(OP_DIV, $<astval>1, $<astval>3)); }
      |
      atom { $<astval>$ = $<astval>1; }
      ;

atom: 
    TOK_IDENTIFIER { $<astval>$ = astval_identifier_new($<string>1); }
    |
    TOK_NUMBER { $<astval>$ = astval_number_new($<number>1); }
    ;
%%
