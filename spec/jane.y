%{
#include <stdio.h>
#include <stdlib.h>
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

int usage()
{
    fprintf(stderr, "Usage: janec <file.j>\n");
}

int main(int argc, char** argv)
{
    if(argc != 2) {
        usage();
        return 0;
    }

    const char* infilename = argv[1];
    const char* outfilename = "jane.out.c";

    fclose(stdin);
    stdin = fopen(infilename, "r"); 

    fclose(stdout);
    stdout = fopen(outfilename, "w"); 

    yyparse();

    return 0;
}

%}

%token TOK_DECLARE TOK_ASSIGN 

%token TOK_ADD TOK_SUB TOK_MUL TOK_DIV TOK_MODULO TOK_POW
%token TOK_GREATER TOK_LESS TOK_EQUAL TOK_GREATER_EQUAL TOK_LESS_EQUAL
%token TOK_NOT_EQUAL TOK_OR TOK_AND TOK_NOT

%token TOK_READ TOK_PRINT TOK_IF TOK_ELSE TOK_WHILE TOK_STOP TOK_NEXT TOK_FUN

%token TOK_EBRACE TOK_OBRACE TOK_OPAREN TOK_EPAREN TOK_SEMI TOK_COMMA

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
%token <string> TOK_STRING

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
         statement_read TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_print TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_while { $<astop>$ = $<astop>1; }
         |
         statement_stop TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_next TOK_SEMI { $<astop>$ = $<astop>1; }
         |
         statement_if { $<astop>$ = $<astop>1; }
         ;

statement_declare:
                     TOK_IDENTIFIER TOK_DECLARE expression_arithmetic  {
                        AstVal iden = astval_identifier_new($<string>1);
                        AstOp op = astop_new(OP_DECLARE, iden, $<astval>3);
                        $<astop>$ = op;
                     }
                     ;

statement_assignment:
                     TOK_IDENTIFIER TOK_ASSIGN expression_arithmetic  {
                        AstVal iden = astval_identifier_new($<string>1);
                        AstOp op = astop_new(OP_ASSIGN, iden, $<astval>3);
                        $<astop>$ = op;
                     }
statement_read:
               TOK_READ TOK_STRING TOK_IDENTIFIER { $<astop>$ = astop_new(OP_READ, astval_string_new($<string>2), astval_identifier_new($<string>3)); }
               |
               TOK_READ TOK_IDENTIFIER { $<astop>$ = astop_new(OP_READ, NULL, astval_identifier_new($<string>2)); }
               ;

statement_print:
               TOK_PRINT TOK_STRING expression_arithmetic { $<astop>$ = astop_new(OP_PRINT, astval_string_new($<string>2), $<astval>3); }
               |
               TOK_PRINT TOK_STRING { $<astop>$ = astop_new(OP_PRINT, astval_string_new($<string>2), NULL); }
               |
               TOK_PRINT expression_arithmetic { $<astop>$ = astop_new(OP_PRINT, NULL, $<astval>2); }
               ;

statement_while:
               TOK_WHILE expression_boolean TOK_OBRACE statements TOK_EBRACE {
                    $<astop>$ = astop_new(OP_WHILE, $<astval>2, astval_op_new($<astop>4));
               }
               ;

statement_stop:
              TOK_STOP { $<astop>$ = astop_new(OP_STOP, NULL, NULL); }
              ;

statement_next:
              TOK_NEXT { $<astop>$ = astop_new(OP_NEXT, NULL, NULL); }
              ;

statement_if:
            TOK_IF expression_boolean TOK_OBRACE statements TOK_EBRACE {
                    $<astop>$ = astop_new(OP_IF, $<astval>2, astval_op_new($<astop>4));
            }
            |
            TOK_IF expression_boolean TOK_OBRACE 
                statements 
            TOK_EBRACE TOK_ELSE TOK_OBRACE
                statements
            TOK_EBRACE {
                AstOp op_if = astop_new(OP_IF, $<astval>2, astval_op_new($<astop>4));
                $<astop>$ = astop_new(OP_ELSE, astval_op_new(op_if), astval_op_new($<astop>8));
            }
            ;

expression_boolean: 
                  expression_boolean TOK_AND factor_boolean {
                    $<astval>$ = astval_op_new(astop_new(OP_AND, $<astval>1, $<astval>3));
                  }
                  |
                  expression_boolean TOK_OR factor_boolean {
                    $<astval>$ = astval_op_new(astop_new(OP_OR, $<astval>1, $<astval>3));
                  }
                  |
                  TOK_NOT factor_boolean {
                    $<astval>$ = astval_op_new(astop_new(OP_NOT, $<astval>1, NULL));
                  }
                  |
                  factor_boolean { $<astval>$ = $<astval>1; }
                  ;

expression_arithmetic:
          expression_arithmetic TOK_ADD factor { $<astval>$ = astval_op_new(astop_new(OP_ADD, $<astval>1, $<astval>3));}
          |
          expression_arithmetic TOK_SUB factor { $<astval>$ = astval_op_new(astop_new(OP_SUB, $<astval>1, $<astval>3));}
          |
          factor { $<astval>$ = $<astval>1; }
          ;

factor_boolean:
                  expression_arithmetic TOK_EQUAL expression_arithmetic { 
                    $<astval>$ = astval_op_new(astop_new(OP_EQUAL, $<astval>1, $<astval>3));
                  }
                  |
                  expression_arithmetic TOK_NOT_EQUAL expression_arithmetic { 
                    $<astval>$ = astval_op_new(astop_new(OP_NOT_EQUAL, $<astval>1, $<astval>3));
                  }
                  |
                  expression_arithmetic TOK_GREATER expression_arithmetic { 
                    $<astval>$ = astval_op_new(astop_new(OP_GREATER, $<astval>1, $<astval>3));
                  }
                  |
                  expression_arithmetic TOK_LESS expression_arithmetic { 
                    $<astval>$ = astval_op_new(astop_new(OP_LESS, $<astval>1, $<astval>3));
                  }
                  |
                  expression_arithmetic TOK_GREATER_EQUAL expression_arithmetic { 
                    $<astval>$ = astval_op_new(astop_new(OP_GREATER_EQUAL, $<astval>1, $<astval>3));
                  }
                  |
                  expression_arithmetic TOK_LESS_EQUAL expression_arithmetic { 
                    $<astval>$ = astval_op_new(astop_new(OP_LESS_EQUAL, $<astval>1, $<astval>3));
                  }
                  |
                  TOK_BOOLEAN { $<astval>$ = astval_boolean_new($<number>1); } 
                  ;

factor:
      factor TOK_MUL atom { $<astval>$ = astval_op_new(astop_new(OP_MUL, $<astval>1, $<astval>3)); }
      |
      factor TOK_DIV atom { $<astval>$ = astval_op_new(astop_new(OP_DIV, $<astval>1, $<astval>3)); }
      |
      factor TOK_MODULO atom { $<astval>$ = astval_op_new(astop_new(OP_MODULO, $<astval>1, $<astval>3)); }
      |
      exponential { $<astval>$ = $<astval>1; }
      |
      atom { $<astval>$ = $<astval>1; }
      ;

exponential:
           atom TOK_POW atom { $<astval>$ = astval_op_new(astop_new(OP_POW, $<astval>1, $<astval>3)); }
           ;

atom: 
    TOK_IDENTIFIER { $<astval>$ = astval_identifier_new($<string>1); }
    |
    TOK_NUMBER { $<astval>$ = astval_number_new($<number>1); }
    ;
%%
