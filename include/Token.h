#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
    ID = 256,
    TYPE,
};

typedef struct Token_ {
    int type;
    char *lexeme;
} Token;

typedef struct TokenList_ {
    Token token;
    struct TokenList_ *next;
} TokenList;

Token createToken(int type, const char *lexeme);

void freeTokenList(TokenList *list);
TokenList *createTokenList(TokenList *next, Token token);
void printTokenList(TokenList *list);
TokenList* reverseTokenList(TokenList *list);

#endif