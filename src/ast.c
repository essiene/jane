#include <stdio.h>
#include <ast.h>


int main()
{
    AstVal ida = astval_identifier_new("sum_of_all");
    AstVal idnum1 = astval_number_new(55);
    AstVal idnum2 = astval_number_new(5);

    AstOp add = astop_new(OP_ADD, idnum1, idnum2);
    AstOp root = astop_new(OP_ASSIGN, ida, astval_op_new(add));
    AstOp print = astop_new(OP_PRINT, ida, NULL);

    root = astop_next_set(root, print);
    compile_op(root);
    printf("\n");

    return 0;
}


/*AstOp {
    type = ASSIGN;
    lval = AstVal {
        type = IDENTIFIER;
        value.string = "a";
    };

    rval =  AstVal {
        type = NUMBER;
        value.number = 5;
    };

    next = AstOp {
        type = ASSIGN;
        lval = "b";
        rval = "10";
        next = AstOp {
            type = ASSIGN;
            lval = AstVal {
                type = IDENTIFIER;
                value.string = "sum";
            };

            rval = AstVal {
                type = AST;
                value.ast = AstOp {
                    type = OP_ADD;
                    lval = AstVal {
                        type = IDENTIFIER;
                        value.string = "a";
                    };
                    rval = AstVal {
                        type=AST;
                        lval = AstVal {
                            type=IDENTIFIER;
                            value.string = "b";
                        };

                        rval = AstVal {
                            type=NUMBER;
                            value.number = 16;
                        };
                        next = null;
                    };
                    next = null;
                };
            next = AstOp {
                type = OP_PRINT;
                lval = AstVal {
                    type=IDENTIFIER;
                    value.string = "sum";
                };
                rval = null;
                next = null;
            }
        }
    }
}
*/
