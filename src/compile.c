#include <stdio.h>
#include <ast.h>

#define COMPILE_BINARY_EXPRESSION(Op, COpr) \
    AstVal rval = astop_rval_get(Op); \
    compile_astval(rval);\
    fprintf(stdout, COpr);\
    AstVal lval = astop_lval_get(Op);\
    compile_astval(lval);\
    if (1);

void compile_astval(AstVal val)
{
    switch(astval_type_get(val)) {
        case IDENTIFIER: fprintf(stdout, "%s ", astval_string_get(val));break;
        case STRING: break;
        case NUMBER: fprintf(stdout, "%d ", astval_number_get(val));break;
        case BOOLEAN: if(astval_number_get(val)) { 
            fprintf(stdout, "true "); 
            break; 
        } else {
            fprintf(stdout, "false ");
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
    fprintf(stdout, "(int) pow(");

    AstVal rval = astop_rval_get(op); 
    compile_astval(rval);

    fprintf(stdout, ",");

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);

    fprintf(stdout, ")");
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
    fprintf(stdout, "!");
    AstVal rval = astop_rval_get(op);
    compile_astval(rval);

}

void compile_declare(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    fprintf(stdout, "int %s = ", astval_string_get(rval)); /* an identifier */

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
    fprintf(stdout, ";\n");

}

void compile_assign(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    fprintf(stdout, "%s = ", astval_string_get(rval)); /* an identifier */

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
    fprintf(stdout, ";\n");

}

void compile_read(AstOp op)
{
    AstVal label = astop_rval_get(op);
    if(label != NULL) {
        printf("printf(\"%%s\", %s);\n", astval_string_get(label));
    }

    AstVal value = astop_lval_get(op);
    if(value == NULL) {
        printf("printf(\"\\n\");\n");
        return;
    }

    printf("scanf(\"%%d\", &%s);\n", astval_string_get(value));
}

void compile_print(AstOp op)
{
    AstVal label = astop_rval_get(op);
    if(label != NULL) {
        fprintf(stdout, "printf(\"%%s\", %s);\n", astval_string_get(label));
    }

    AstVal value = astop_lval_get(op);
    if(value == NULL) {
        fprintf(stdout, "printf(\"\\n\");\n");
        return;
    }

    switch(astval_type_get(value)) {
        case IDENTIFIER: fprintf(stdout, "printf(\"%%d\\n\",%s) ", astval_string_get(value));break;
        case STRING: break;
        case NUMBER: fprintf(stdout, "printf(\"%d\\n\") ", astval_number_get(value));break;
        case BOOLEAN: {
            if(astval_number_get(value)) {
                fprintf(stdout, "printf(\"true\\n\") ");
                break;
            } else {
                fprintf(stdout, "printf(\"false\\n\") ");
                break;
            }
        }
        case OP: 
                     fprintf(stdout, "printf(\"%%d\\n\",");
                     compile_op(astval_op_get(value));
                     fprintf(stdout, ")");
                     break;
    }

    fprintf(stdout, ";\n");
}

void compile_if(AstOp op)
{
    fprintf(stdout, "if (");
    AstVal expression = astop_rval_get(op);
    compile_astval(expression);
    fprintf(stdout, ") {\n");

    AstVal statments = astop_lval_get(op);
    compile_astval(statments);

    fprintf(stdout, "}\n");
}

void compile_else(AstOp op)
{
    AstVal if_exp = astop_rval_get(op);
    AstOp if_op = astval_op_get(if_exp);
    compile_if(if_op);

    fprintf(stdout, "else {\n");

    AstVal statments = astop_lval_get(op);
    compile_astval(statments);

    fprintf(stdout, "}\n");
}

void compile_while(AstOp op)
{
    fprintf(stdout, "while (");
    AstVal expression = astop_rval_get(op);
    compile_astval(expression);
    fprintf(stdout, ") {\n");

    AstVal statments = astop_lval_get(op);
    compile_astval(statments);

    fprintf(stdout, "}\n");
}

void compile_stop(AstOp op)
{
    fprintf(stdout, "break;\n");
}

void compile_next(AstOp op)
{
    fprintf(stdout, "continue;\n");
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
            case OP_READ: compile_read(current);break;
            case OP_PRINT: compile_print(current);break;
            case OP_IF: compile_if(current);break;
            case OP_ELSE: compile_else(current);break;
            case OP_WHILE: compile_while(current);break;
            case OP_STOP: compile_stop(current);break;
            case OP_NEXT: compile_next(current);break;
        }

        current = astop_next_get(current);
    }
        
}

void compile_root(AstOp op)
{
    fprintf(stdout, "#include <stdio.h>\n");
    fprintf(stdout, "#include <stdlib.h>\n");
    fprintf(stdout, "#include <math.h>\n");
    fprintf(stdout, "\n");

    compile_op(op);
}
