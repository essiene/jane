#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gc.h>

#include <ast.h>

struct _AstOp {
    AstOpType type;
    AstVal lval;
    AstVal rval;
    AstOp next;
};

void astop_printf(AstOp a)
{
    if(a == NULL) {
        return;
    }
    
    switch(a->type) {
        case OP_ADD: printf("{OP_ADD: ");break;
        case OP_SUB: printf("{OP_SUB: ");break;
        case OP_MUL: printf("{OP_MUL: ");break;
        case OP_DIV: printf("{OP_DIV: ");break;
        case OP_DECLARE: printf("{OP_ASSIGN: ");break;
        case OP_ASSIGN: printf("{OP_ASSIGN: ");break;
        case OP_PRINT: printf("{OP_PRINT: ");break;
        case OP_WHILE: printf("{OP_WHILE: ");break;
    }

    if(a->rval != NULL) {
        astval_printf(a->rval);
    }

    if(a->lval != NULL) {
        astval_printf(a->lval);
    }

    printf("}");

    if(a->next == NULL) {
        return;
    }

    astop_printf(a->next);
}

AstOp astop_new(AstOpType type, AstVal rval, AstVal lval)
{
    ASTTYPE_NEW(AstOp, type, a);
    a->rval = rval;
    a->lval = lval;
    a->next = NULL;

    return a;
}

AstOp astop_next_set(AstOp op, AstOp next)
{
    op->next = next;
    return op;
}

AstOp astop_next_get(AstOp op)
{
    return op->next;
}

int astop_has_next(AstOp op)
{
    return op->next != NULL;
}

AstOpType astop_type_get(AstOp op)
{
    return op->type;
}

AstVal astop_rval_get(AstOp op)
{
    return op->rval;
}

AstVal astop_lval_get(AstOp op)
{
    return op->lval;
}
