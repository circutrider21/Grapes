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

// Get The Scanner Ready For Parsing
void initScanner(char* filename);

// Get the next token in the program
Token getToken();
