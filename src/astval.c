#include <stdio.h>
#include <stdlib.h>
#include <gc.h>
#include <ast.h>

struct _AstVal{ 
    AstValType type;

    union {
        AstOp op;
        int number; 
        const char* string; 
    } value;
}; 


AstVal astval_identifier_new(const char* str)
{
    ASTTYPE_NEW(AstVal, IDENTIFIER, a);
    a->value.string = str;
    return a;
}

AstVal astval_number_new(int n)
{
    ASTTYPE_NEW(AstVal, NUMBER, a);
    a->value.number = n;
    return a;
}

AstVal astval_boolean_new(int n)
{
    ASTTYPE_NEW(AstVal, BOOLEAN, a);
    a->value.number = n;
    return a;
}

AstVal astval_op_new(AstOp op)
{
    ASTTYPE_NEW(AstVal, OP, a);
    a->value.op= op;
    return a;
}

AstValType astval_type_get(AstVal a)
{
    return a->type;
}

int astval_number_get(AstVal a)
{
    return a->value.number;
}

const char * astval_string_get(AstVal a)
{
    return a->value.string;
}

AstOp astval_op_get(AstVal a)
{
    return a->value.op;
}

void astval_printf(AstVal a)
{
    switch(a->type) {
        case IDENTIFIER: printf("<IDENTIFIER: %s>", a->value.string);break;
        case NUMBER: printf("<NUMBER: %d>", a->value.number);break;
        case BOOLEAN: {
            if(a->value.number) {
                printf("<BOOLEAN: true>");
                break;
            } else {
                printf("<BOOLEAN: false>");
                break;
            }
        }
        case OP: printf("<");astop_printf(a->value.op);printf(">");break;
    }
}
