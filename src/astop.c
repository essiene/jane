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
        case OP_MODULO: printf("{OP_MODULO: ");break;
        case OP_POW: printf("{OP_POW: ");break;
        case OP_GREATER: printf("{OP_GREATER: ");break;
        case OP_LESS: printf("{OP_LESS: ");break;
        case OP_EQUAL: printf("{OP_EQUAL: ");break;
        case OP_GREATER_EQUAL: printf("{OP_GREATER_EQUAL: ");break;
        case OP_LESS_EQUAL: printf("{OP_LESS_EQUAL: ");break;
        case OP_NOT_EQUAL: printf("{OP_NOT_EQUAL: ");break;
        case OP_AND: printf("{OP_AND: ");break;
        case OP_OR: printf("{OP_OR: ");break;
        case OP_NOT: printf("{OP_NOT: ");break;
        case OP_DECLARE: printf("{OP_ASSIGN: ");break;
        case OP_ASSIGN: printf("{OP_ASSIGN: ");break;
        case OP_READ: printf("{OP_READ: ");break;
        case OP_PRINT: printf("{OP_PRINT: ");break;
        case OP_IF: printf("{OP_IF: ");break;
        case OP_ELSE: printf("{OP_ELSE: ");break;
        case OP_WHILE: printf("{OP_WHILE: ");break;
        case OP_STOP: printf("{OP_STOP: ");break;
        case OP_NEXT: printf("{OP_NEXT: ");break;
        case OP_RETURN: printf("{OP_RETURN: ");break;
        case OP_FUN: printf("{OP_FUN: ");break;
        case OP_FUNBODY: printf("{OP_FUNBODY: ");break;
        case OP_CALL: printf("{OP_CALL: ");break;
        case OP_COMMA: printf("{OP_COMMA: ");break;
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
