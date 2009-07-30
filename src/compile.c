#include <stdio.h>
#include <ast.h>

void compile_astval(AstVal val)
{
    switch(astval_type_get(val)) {
        case IDENTIFIER: printf("%s ", astval_string_get(val));break;
        case NUMBER: printf("%d ", astval_number_get(val));break;
        case OP: compile_op(astval_op_get(val));break;
    }
}

void compile_add(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    compile_astval(rval);

    printf(" + ");

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
}

void compile_sub(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    compile_astval(rval);

    printf(" - ");

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
}

void compile_mul(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    compile_astval(rval);

    printf(" * ");

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
}

void compile_div(AstOp op)
{
    AstVal rval = astop_rval_get(op);
    compile_astval(rval);

    printf(" / ");

    AstVal lval = astop_lval_get(op);
    compile_astval(lval);
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
    printf("\n");
    printf("int main()\n");
    printf("{\n");

    compile_op(op);

    printf("return 0;\n");
    printf("}\n");
}

