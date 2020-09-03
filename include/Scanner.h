// Scanner.h | Copyright 2020 Peeled Fruit Studios. All Rights Reserved

#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>

typedef enum {

} TokenType;

typedef struct {
  TokenType t;
  char* raw;
} Token;

class Scanner {
  public:
  Scanner(std::string filename);
  void run();
};

#endif