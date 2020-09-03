// Common.h | Copyright 2020 Peeled Fruit Studios. All Rights Reserved

#ifndef COMMON_H
#define COMMON_H

#include <iostream>

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

void printVal(Value v);

#endif