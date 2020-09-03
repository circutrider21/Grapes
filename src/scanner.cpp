/* Scanner.c | Copright 2020 Peeled Fruit Studios, All Rights Reserved.*/

#include "../include/scanner.h"
#include <iostream>
#include <fstream>

void Scanner::initScanner(char* filename) {
  f.open(filename);
}

Token Scanner::getToken() {
  Token t;
  t.type = TOKEN_IDENTIFIER;
  t.raw = "print";
  return t;
}
