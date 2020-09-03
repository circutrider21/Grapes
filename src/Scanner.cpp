#include "../include/Scanner.h"
#include <fstream>

using namespace std;

ifstream f;

int line;

typedef struct {
  const char* start;
  const char* current;
  int line;
} Lexer;

Lexer nkg;

Scanner::Scanner(string filename) {
  f.open(filename, ios::in);
  std::string contents((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
  const char* data = contents.c_str();
  nkg.start = data;
  nkg.current = data;
  nkg.line = 1;
  f.close();
}

static bool isAtEnd() {
  return *nkg.current == '\0';
}

static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = nkg.start;
  token.length = (int)(nkg.current - nkg.start);
  token.line = nkg.line;

  return token;
}

static Token errorToken(const char* message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = 21;
  token.line = nkg.line;

  return token;
}

bool match(char expected) {
  if (isAtEnd()) return false;
  if (*nkg.current != expected) return false;

  nkg.current++;
  return true;
}

static char peek() {
  return *nkg.current;
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\n':
        scanner.line++;
        advance();
        break;
      case '\t':
        advance();
        break;

      default:
        return;
    }
  }
}

Token scanToken() {
  skipWhitespace();

  nkg.start = nkg.current;

  if (isAtEnd()) return makeToken(TOKEN_EOF);

  char c = advance();

  switch (c) {
    case '(': return makeToken(TOKEN_LEFT_PAREN);
    case ')': return makeToken(TOKEN_RIGHT_PAREN);
    case '{': return makeToken(TOKEN_LEFT_BRACE);
    case '}': return makeToken(TOKEN_RIGHT_BRACE);
    case ';': return makeToken(TOKEN_SEMICOLON);
    case ',': return makeToken(TOKEN_COMMA);
    case '.': return makeToken(TOKEN_DOT);
    case '-': return makeToken(TOKEN_MINUS);
    case '+': return makeToken(TOKEN_PLUS);
    case '/': return makeToken(TOKEN_SLASH);
    case '*': return makeToken(TOKEN_STAR);
    case '!':
      return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
      return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
      return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
      return makeToken(match('=') ?
                       TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  }

  return errorToken("Unexpected character.");
}

