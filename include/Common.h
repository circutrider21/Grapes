// Common.h | Copyright 2020 Peeled Fruit Studios. All Rights Reserved

#include <iostream>

typedef enum {
  VT_INT,
  VT_STRING,
  VT_BOOL,
  VT_IDENT
} ValType;

typedef struct {
  ValType v;
  union {
    int ival;
    bool bval;
    char* cval;
  }
} Value;

void printVal(Value v);