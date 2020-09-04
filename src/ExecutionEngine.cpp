// Copyright 2020 PFS, All Rights Reserved

#include "../include/ExecutionEngine.h"
#include <stack>

Program r;
std::stack<Value> vst;
int counter;

ExecutionEngine::ExecutionEngine(Program p) {
  r = p;
  counter = 0;
}

static Value getCon() {
  return r.Consts[counter++];
}

void ExecutionEngine::run() {
  for(int i = 0; i < r.inSize; i++) {
    switch(r.instr[i]) {
      case OP_PRINT:
      printVal(vst.top());
      vst.pop();
      break;
      case OP_LOAD:
      vst.emplace(getCon());
      break;
      case OP_RETURN:
      exit(0);
      break;
    }
  }
}