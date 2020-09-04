// Compiler.cpp | Copyright 2020 Peeled Fruit Studios. All Rights Reserved.

#include "../include/Compiler.h"
#include "../include/Defs.h"
#include "../include/Scanner.h"
#include <vector>

Scanner s;
Program curProg;

Compiler::Compiler(const char* filename) {
  s.setup(filename);
}
std::vector<int> instv;
std::vector<Value> conv;

void emitInst(int inst) {
  instv.push_back(inst);
}

void emitConst(Value v) {
  conv.push_back(v);
}

Value stov(const char* string, int length) {
  char data[length];
  for(int i = 0; i < length; i++) {
    data[i] = string[i];
  }
  printf("%s\n", string);
  Value to_ret;
  to_ret.v = V_STRING;
  to_ret.cval = data;
  return to_ret;
}

Value evaluate() {
  Token to_eval;
  Value to_ret;
  while(to_eval.type != TOKEN_SEMICOLON) {
    switch(to_eval.type) {
      case TOKEN_STRING:
      return stov(to_eval.start, to_eval.length);
      break;
    }
    to_eval = s.scanToken();
  }
  return to_ret;
}

void Compiler::build() {
  Token curTok;
  while(curTok.type != TOKEN_EOF) {
    switch(curTok.type) {
      case TOKEN_PRINT:
      emitConst(evaluate());
      emitInst(OP_LOAD);
      emitInst(OP_PRINT);
      break;
    }
    curTok = s.scanToken();
  }
  emitInst(OP_RETURN);
}

Program Compiler::dump() {
  curProg.conSize = conv.size();
  curProg.inSize = instv.size();
  curProg.instr = (int *)malloc(sizeof(int) * curProg.inSize);
  for(int c = 0; c < instv.size(); c++) {
    curProg.instr[c] = instv.at(c);
  }
  curProg.Consts = (Value *)malloc(sizeof(Value) * curProg.conSize);
  for(int f = 0; f < conv.size(); f++) {
    curProg.Consts[f] = conv.at(f);
  }

  return curProg;
}