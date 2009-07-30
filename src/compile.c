#include <stdio.h>
#include <ast.h>

#define COMPILE_BINARY_EXPRESSION(Op, COpr) \
    AstVal rval = astop_rval_get(Op); \
    compile_astval(rval);\
    printf(COpr);\
    AstVal lval = astop_lval_get(Op);\
    compile_astval(lval);\
    if (1);

void compile_astval(AstVal val)
{
    switch(astval_type_get(val)) {
        case IDENTIFIER: printf("%s ", astval_string_get(val));break;
        case NUMBER: printf("%d ", astval_number_get(val));break;
        case BOOLEAN: if(astval_number_get(val)) { 
            printf("true "); 
            break; 
        } else {
            printf("false ");
            break;
        }
        case OP: compile_op(astval_op_get(val));break;
    }
}

void compile_add(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "+");
}

void compile_sub(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "-");
}

void compile_mul(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "*");
}

void compile_div(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "/");
}

void compile_modulo(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "%%");
}

void compile_pow(AstOp op)
{
    printf("(int) pow(");

    AstVal rval = astop_rval_get(op); 
    compile_astval(rval);

    printf(",");

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);

    printf(")");
}


void compile_greater(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, ">");
}

void compile_less(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "<");
}

void compile_equal(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "==");
}

void compile_greater_equal(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, ">=");
}

void compile_less_equal(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "<=");
}

void compile_not_equal(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "!=");
}

void compile_and(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "&&");
}

void compile_or(AstOp op)
{
    COMPILE_BINARY_EXPRESSION(op, "||");
}

void compile_not(AstOp op)
{
    printf("!");
    AstVal rval = astop_rval_get(op);
    compile_astval(rval);

}

void compile_declare(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    printf("int %s = ", astval_string_get(rval)); /* an identifier */

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
    printf(";\n");

}

void compile_assign(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    printf("%s = ", astval_string_get(rval)); /* an identifier */

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
    printf(";\n");

}

void compile_print(AstOp op)
{
    AstVal rval = astop_rval_get(op);

    switch(astval_type_get(rval)) {
        case IDENTIFIER: printf("printf(\"%%d\\n\",%s) ", astval_string_get(rval));break;
        case NUMBER: printf("printf(\"%d\\n\") ", astval_number_get(rval));break;
        case BOOLEAN: {
            if(astval_number_get(rval)) {
                printf("printf(\"true\\n\") ");
                break;
            } else {
                printf("printf(\"false\\n\") ");
                break;
            }
        }
        case OP: 
                     printf("printf(\"%%d\\n\",");
                     compile_op(astval_op_get(rval));
                     printf(")");
                     break;
    }

    printf(";\n");
}

void compile_while(AstOp op)
{
    printf("while (");
    AstVal expression = astop_rval_get(op);
    compile_astval(expression);
    printf(") {\n");

    AstVal statments = astop_lval_get(op);
    compile_astval(statments);

    printf("}\n");
}

void compile_stop(AstOp op)
{
    printf("break;\n");
}

void compile_next(AstOp op)
{
    printf("continue;\n");
}

void compile_op(AstOp op)
{
    AstOp current = op;

    while(current != NULL) {
        switch(astop_type_get(current)) {
            case OP_ADD: compile_add(current);break;
            case OP_SUB: compile_sub(current);break;
            case OP_MUL: compile_mul(current);break;
            case OP_DIV: compile_div(current);break;
            case OP_MODULO: compile_modulo(current);break;
            case OP_POW: compile_pow(current);break;
            case OP_GREATER: compile_greater(current);break;
            case OP_LESS: compile_less(current);break;
            case OP_EQUAL: compile_equal(current);break;
            case OP_GREATER_EQUAL: compile_greater_equal(current);break;
            case OP_LESS_EQUAL: compile_less_equal(current);break;
            case OP_NOT_EQUAL: compile_not_equal(current);break;
            case OP_AND: compile_and(current);break;
            case OP_OR: compile_or(current);break;
            case OP_NOT: compile_not(current);break;
            case OP_DECLARE: compile_declare(current);break;
            case OP_ASSIGN: compile_assign(current);break;
            case OP_PRINT: compile_print(current);break;
            case OP_WHILE: compile_while(current);break;
            case OP_STOP: compile_stop(current);break;
            case OP_NEXT: compile_next(current);break;
        }

        current = astop_next_get(current);
    }
        
}

void compile_root(AstOp op)
{
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <math.h>\n");
    printf("\n");
    printf("int main()\n");
    printf("{\n");

    compile_op(op);

    printf("return 0;\n");
    printf("}\n");
}

