#ifndef EE_H
#define EE_H

#include "Common.h"
#include <stack>
using namespace std;

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

class ExecutionEngine {
  public:
  ExecutionEngine(Program p);
  void run();
};

#endif