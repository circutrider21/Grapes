// Compiler.h | Copyright 2020 Peeled Fruit Studios. All Rights Reserved

#ifndef COMPILER_H
#define COMPILER_H

#include "Common.h"

class Compiler {
  public:
  Compiler(const char* filename);
  void build();
  Program dump();
};


#endif