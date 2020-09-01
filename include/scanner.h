// Scanner.h | Copyright 2020 Peeled Fruit Studios, All Rights Reserved.

#include "Common.h"

//Types Of Tokens in grapes
typedef enum {
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_IDENTIFIER,
  TOKEN_PRINT,
  TOKEN_VAR,
  TOKEN_FUNC
} TokenType;

// Definition of a Token
typedef struct {
  TokenType type;
  char* raw;
} Token;

// The Scanner Class

class Scanner {
private:
  ifstream f;
  int pos;
public:
  void initScanner(char* filename);
  Token getToken();
};
