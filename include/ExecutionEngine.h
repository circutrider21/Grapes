#ifndef EE_H
#define EE_H

#include "Common.h"
#include "Defs.h"
#include <stack>
using namespace std;

class ExecutionEngine {
  public:
  ExecutionEngine(Program p);
  void run();
};

#endif