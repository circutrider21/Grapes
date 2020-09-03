#include "include/ExecutionEngine.h"
using namespace std;

int main() {
  Value v;
  v.v = V_INT;
  v.ival = 18;
  printVal(v); 

  Program p;
  p.conSize = 1;
  p.inSize = 3;
  p.instr = (int *)malloc(sizeof(int) * 3);
  p.Consts = (Value *)malloc(sizeof(Value) * 1);
  p.instr[0] = OP_LOAD;
  p.instr[1] = OP_PRINT;
  p.instr[2] = OP_RETURN;
  v.ival = 20;
  p.Consts[0] = v;

  ExecutionEngine e(p);
  e.run();
}