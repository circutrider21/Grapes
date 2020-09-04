#include "../include/Scanner.h"
#include <cstdio>
#include <cstring>

using namespace std;

int line;

typedef struct {
  const char* start;
  const char* current;
  int line;
} Lexer;

Lexer nkg;

extern "C" char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  if (!file)
    printf("Error: Unable To Open File %s\n", path);

  fseek(file, 1, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 2);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

void Scanner::setup(const char* filename) {
  const char* data = readFile(filename);
  nkg.start = data;
  nkg.current = data;
  nkg.line = 1;
}

static char advance() {
  nkg.current++;
  return nkg.current[-1];
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

static char peekNext() {
  if (isAtEnd()) return '\0';
  return nkg.current[1];
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\n':
        nkg.line++;
        advance();
        break;
      case '\t':
        advance();
        break;

      case '/':
        if (peekNext() == '/') {
          // A comment goes until the end of the line.
          while (peek() != '\n' && !isAtEnd()) advance();
        } else {
          return;
        }
        break;

      default:
        return;
    }
  }
}

static Token stri() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') nkg.line++;
    advance();
  }

  if (isAtEnd()) return errorToken("Unterminated string.");

  // The closing quote.
  advance();
  return makeToken(TOKEN_STRING);
}

static bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

static Token number() {
  while (isDigit(peek())) advance();

  // Look for a fractional part.
  if (peek() == '.' && isDigit(peekNext())) {
    // Consume the ".".
    advance();

    while (isDigit(peek())) advance();
  }

  return makeToken(TOKEN_NUMBER);
}

static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
}

static TokenType checkKeyword(int start, int length,
    const char* rest, TokenType type) {
  if (nkg.current - nkg.start == start + length &&
      memcmp(nkg.start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

static TokenType identifierType()
{
  switch (nkg.start[0]) {
    case 'a': return checkKeyword(1, 2, "nd", TOKEN_AND);
    case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
    case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);
    case 'f':
      if (nkg.current - nkg.start > 1) {
        switch (nkg.start[1]) {
          case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
          case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
          case 'u': return checkKeyword(2, 1, "n", TOKEN_FUN);
        }
      }
      break;
    case 'i': return checkKeyword(1, 1, "f", TOKEN_IF);
    case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
    case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
    case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
    case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
    case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);
    case 't':
      if (nkg.current - nkg.start > 1) {
        switch (nkg.start[1]) {
          case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
          case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
        }
      }
      break;
    case 'v': return checkKeyword(1, 2, "ar", TOKEN_VAR);
    case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
  }

  return TOKEN_IDENTIFIER;
}

static Token identifier() {
  while (isAlpha(peek()) || isDigit(peek())) advance();

  return makeToken(identifierType());
}

Token Scanner::scanToken() {
  skipWhitespace();

  nkg.start = nkg.current;

  if (isAtEnd()) return makeToken(TOKEN_EOF);

  char c = advance();

  if (isAlpha(c)) return identifier();
  if (isDigit(c)) return number();
  //named function stri because string is reserved
  if (c == '"') return stri();

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

