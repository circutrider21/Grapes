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
  return 0;
}