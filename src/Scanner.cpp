#include "../include/Scanner.h"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>

using namespace grapes::lexer;

int size;
int linum;
char* data;
static int counter;

Scanner::Scanner(const char* filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    printf("Error opening file %s\n", filename);
    exit(3);
  }
  int fd = fileno(f);
  if (fd == 0) {
    printf("Error: FIle Descriptor not found\n");
    exit(2);
  }
  struct stat s;
  fstat(fd, &s);
  size = s.st_size;
  data = (char *)mmap(0, s.st_size + 1, PROT_READ, MAP_SHARED, fd, 0);
  data[st.size] = 
  if (data == NULL) {
    printf("Error: mmap Failed\n");
  }
  std::cout << data <<std::endl;
  counter = 0;
}

Token mToken(int typ, const char* data, int lengt, int lin){
  Token t;
  t.type = typ;
  t.start = data;
  t.length = lengt;
  t.line = lin;
}

Token errortok(char* info, int linum) {
  return mToken(TOKEN_ERROR, info, 0, linum);
}


void skipWhitespace() {
  for (;;) {
    char c = data[counter + 1];
    switch (c) {
      case ' ':
      case '\r':
      case '\n':
        linum++;
        counter++;
        break;
      case '\t':
        counter++;
        break;

      case '/':
        if (data[counter + 2] == '/') {
          // A comment goes until the end of the line.
          while (data[counter + 1] != '\n' && data[counter] != '\0'){
            counter++;
          }
        } else {
          return;
        }
        break;

      default:
        return;
    }
  }
}

Token stri() {
  std::vector<char> holder;
  counter++;
  while(data[counter] != '"') {
    holder.push_back(data[counter]);
    counter++;
  }
  char* data = (char*)calloc(holder.size(), sizeof(char));
  for(int i = 0; i < holder.size(); i++) {
    data[i] = holder.at(i);
  }
  return mToken(TOKEN_STRING, data, holder.size(), linum);
}

Token number() {
  std::vector<char> holde;
  while(isdigit(data[counter])) {
    holde.push_back(data[counter]);
    counter++;
  }
  char* data = (char*)calloc(holde.size(), sizeof(char));
  for(int i = 0; i < holde.size(); i++) {
    data[i] = holde.at(i);
  }
  return mToken(TOKEN_NUMBER, data, holde.size(), linum);
}

Token identifier() {
  switch(data[counter]) {
    case 'c': return mToken(TOKEN_CLASS, "class", 5, linum);
    case 'e': return mToken(TOKEN_ELSE, "else", 4, linum);
    case 'f':
    if (data[counter + 1] == 'o') {
      return mToken(TOKEN_FOR, "for", 3, linum);
    } else if (data[counter + 1] == 'a') {
      return mToken(TOKEN_FALSE, "false", 5, linum);
    } else if (data[counter + 1] == 'u') {
      return mToken(TOKEN_FUN, "fun", 3, linum);
    }
    case 'i': return mToken(TOKEN_IF, "if", 2, linum);
    case 'n': return mToken(TOKEN_NIL, "nil", 3, linum);
    case 'p': return mToken(TOKEN_PRINT, "print", 5, linum);
    case 'r': return mToken(TOKEN_RETURN, "return", 6, linum);
    case 's': return mToken(TOKEN_SUPER, "super", 5, linum);
    case 't':
    if(data[counter + 1] == 'h') {
      return mToken(TOKEN_THIS, "this", 4, linum);
    } else if (data[counter + 1] == 'r') {
      return mToken(TOKEN_TRUE, "true", 4, linum);
    }
    case 'v': return mToken(TOKEN_VAR, "var", 3, linum);
    case 'w': return mToken(TOKEN_WHILE, "while", 5, linum);
    default:
      return errortok("Unidentified Keyword", linum);
  }
}

Token Scanner::scanToken() {
  skipWhitespace();


  char c = data[counter];
  if (c == '\0')
    return mToken(TOKEN_EOF, nullptr, 0, linum);
  if (c == '"')
    return stri();
  if (isalpha(c))
    return identifier();
  if (isdigit(c))
    return number();
  

  switch (c) {
    case '(': return mToken(TOKEN_LEFT_PAREN, nullptr, 0, linum);
    case ')': return mToken(TOKEN_RIGHT_PAREN, nullptr, 0, linum);
    case '{': return mToken(TOKEN_LEFT_BRACE, nullptr, 0, linum);
    case '}': return mToken(TOKEN_RIGHT_BRACE, nullptr, 0, linum);
    case ';': return mToken(TOKEN_SEMICOLON, nullptr, 0, linum);
    case ',': return mToken(TOKEN_COMMA, nullptr, 0, linum);
    case '.': return mToken(TOKEN_DOT, nullptr, 0, linum);
    case '-': return mToken(TOKEN_MINUS, nullptr, 0, linum);
    case '+': return mToken(TOKEN_PLUS, nullptr, 0, linum);
    case '/': return mToken(TOKEN_SLASH, nullptr, 0, linum);
    case '*': return mToken(TOKEN_STAR, nullptr, 0, linum);
    case '!':
      if (data[counter + 1] == '=') {
        return mToken(TOKEN_BANG_EQUAL, nullptr, 0, linum);
      } else {
        return mToken(TOKEN_BANG, nullptr, 0, linum);
      }
    case '=':
      if(data[counter + 1] == '=') {
        return mToken(TOKEN_EQUAL_EQUAL, nullptr, 0, linum);
      } else {
        return mToken(TOKEN_EQUAL, nullptr, 0, linum);
      }
    case '<':
      if(data[counter + 1] == '=') {
        return mToken(TOKEN_GREATER_EQUAL, nullptr, 0, linum);
      } else {
        return mToken(TOKEN_GREATER, nullptr, 0, linum);
      }
    case '>':
      if(data[counter + 1] == '=') {
        return mToken(TOKEN_LESS_EQUAL, nullptr, 0, linum);
      } else {
        return mToken(TOKEN_LESS, nullptr, 0, linum);
      }
      
  }

  return errortok("Unexpected character.", linum);

}

Scanner::~Scanner() {
  munmap((void *)data, size);
  data = nullptr;
}


/*

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
  if (type == TOKEN_STRING) {
    token.start = nkg.start + 1;
    token.length = (int)(nkg.current - nkg.start - 2);
    token.line = nkg.line;
    return token;
  }
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

static bool isalpha(char c) {
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
  while (isalpha(peek()) || isDigit(peek())) advance();

  return makeToken(identifierType());
}

Token Scanner::scanToken() {
  skipWhitespace();

  nkg.start = nkg.current;

  if (isAtEnd()) return makeToken(TOKEN_EOF);

  char c = advance();

  if (isalpha(c)) return identifier();
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
} */

