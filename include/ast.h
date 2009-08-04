#ifndef _AST_JANE_H
#define _AST_JANE_H

#define ASTTYPE_NEW(Type, EnumType, a) Type a = GC_malloc(sizeof(*a)); \
                                 if(a == NULL) { \
                                     return NULL; \
                                 } \
                                 a->type = EnumType; \
                                 if(1) \

typedef struct _AstVal* AstVal;
typedef struct _AstOp* AstOp;

typedef enum {
    OP,
    NUMBER,
    BOOLEAN,
    IDENTIFIER,
    STRING
} AstValType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MODULO,
    OP_POW,
    OP_GREATER,
    OP_LESS,
    OP_EQUAL,
    OP_GREATER_EQUAL,
    OP_LESS_EQUAL,
    OP_NOT_EQUAL,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_DECLARE,
    OP_ASSIGN,
    OP_READ,
    OP_PRINT,
    OP_IF,
    OP_ELSE,
    OP_WHILE,
    OP_STOP,
    OP_NEXT
} AstOpType;

AstVal astval_identifier_new(const char*);
AstVal astval_string_new(const char*);
AstVal astval_number_new(int);
AstVal astval_boolean_new(int);
AstVal astval_op_new(AstOp);
AstValType astval_type_get(AstVal);
int astval_number_get(AstVal);
const char* astval_string_get(AstVal);
AstOp astval_op_get(AstVal);
void astval_printf(AstVal);

AstOp astop_new(AstOpType, AstVal, AstVal);
AstOp astop_next_set(AstOp, AstOp);
AstOp astop_next_get(AstOp);
AstOpType astop_type_get(AstOp);
AstVal astop_rval_get(AstOp);
AstVal astop_lval_get(AstOp);
int astop_has_next(AstOp);
void astop_printf(AstOp);

void compile_op(AstOp);
void compile_add(AstOp);
void compile_sub(AstOp);
void compile_mul(AstOp);
void compile_div(AstOp);
void compile_assign(AstOp);
void compile_print(AstOp);

#endif
