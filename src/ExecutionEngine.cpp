// Copyright 2020 PFS, All Rights Reserved

#include "ExecutionEngine.h"

void ExecutionEngine::run() {
  for(int i = 0; i < p.h.isize; i++) {
    switch(p.i) {
      case OP_PRINT:
      printValue(pop);
      break;
    }
  }
}