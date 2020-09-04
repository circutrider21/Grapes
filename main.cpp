<<<<<<< HEAD
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
=======
#include "include/Scanner.h"
using namespace std;

int main() {
  Scanner s("Test.gs");
  Token t;
  for (;;) {
    t = s.scanToken();
    if(t.type == TOKEN_EOF) {
      exit(0);
    }
    cout << t.start << endl;
  }
>>>>>>> cf9083e6d6959b7c53418be31fd4fefcd4713077
  return 0;
}