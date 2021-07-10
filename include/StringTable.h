#ifndef STRING_TABLE_H
#define STRING_TABLE_H

#include "Token.h"

typedef struct StringTable_ {
    char *lexeme;
    Token *token;
    struct StringTable_ *next;
} StringTable;

StringTable* createStringTable(StringTable *next, const char *lexeme, Token *token);
void freeStringTable(StringTable *table);

// Makes copy of token
Token* findTokenByLexeme(StringTable* table, const char *lexeme);

#endif