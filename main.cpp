#include "include/Scanner.h"
#include <new>
#include <iostream>
using grapes::lexer::Scanner;
using namespace std;

int main() {
  Scanner* s = new Scanner("../Test.gs");
  grapes::lexer::Token t = s->scanToken();
  while(t.type != grapes::lexer::TOKEN_EOF) {
    t = s->scanToken();
  }
  delete s;
}