#include "../include/Compiler.h"
#include <fstream>

using namespace std;

ifstream f;
char* data;

Compiler::Compiler(string filename) {
  f.open(filename, ios::in);
  std::string contents((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
  cout << contents.c_str() << endl;
}

