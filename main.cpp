#include "include/Compiler.h"
#include "include/ExecutionEngine.h"
using namespace std;

int main() {
  Program pt; 
  Compiler c("../Test.gs");
  c.build();
  pt = c.dump();

  ExecutionEngine e(pt);
  e.run();
  return 0;
}