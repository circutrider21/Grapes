#ifndef DEFS_H
#define DEFS_H

typedef enum {
  V_INT,
  V_STRING,
  V_BOOL,
  V_IDENT
} ValType;

typedef struct {
  ValType v;
  union {
    int ival;
    bool bval;
    char* cval;
  };
} Value;

typedef struct {
  int conSize;
  int inSize;
  int* instr;
  Value* Consts;
} Program;

typedef enum {
  OP_LOAD = 15,
  OP_PRINT,
  OP_RETURN
} OpCodes;

#endif