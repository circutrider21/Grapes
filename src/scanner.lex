// Scanner.lex | Copyright 2020 Peeled Fruit Studios, All Rights Reserved

%{
  #include <iostream>
  #include "scanner.h"

  extern "C" int yylex();
}%

// Rules For The Parser

%%

[0-9]+ {
  Token t;
  t.type = TOKEN_NUMBER;
  t.raw = yyval;
  return t;
}

";" {
  Token t;
  t.type = TOKEN_SEMICOLON;
  t.raw = yyval;
  return t;
}

[\t\n\r\f] ;

%%

