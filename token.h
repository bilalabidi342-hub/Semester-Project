#ifndef TOKEN_H
#define TOKEN_H
enum TokenType{
 NUMBER,PLUS,MINUS,STAR,SLASH,ASIGN,IDENT,PRINT,END,GT,LT,EQEQ,AGAR,WARNA,JABTAK,LBRACE,RBRACE
};
struct Token{
  TokenType type;
  char value[50];
};
#endif