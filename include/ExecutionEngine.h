#include "Common.h"

class ExecutionEngine {
  private:
  Program r;
  public:
  ExecutionEngine(Program p){
    r = p;
  }
  void run();
};