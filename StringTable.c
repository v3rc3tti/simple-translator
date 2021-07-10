#include <stdlib.h>
#include <string.h>
#include "StringTable.h"
#include "Token.h"

StringTable* createStringTable(StringTable *next, const char *lexeme, Token *token) {
    StringTable *table = malloc(sizeof(StringTable));
    memset(table, 0, sizeof(StringTable));
    table->lexeme = malloc((strlen(lexeme)+1)*sizeof(char));
    strcpy(table->lexeme, lexeme);
    table->token = token;
    table->next = next;
    return table;
}

void freeStringTable(StringTable *table) {
    while (table != NULL) {
        StringTable *next = table->next;
        free(table->lexeme);
        freeToken(table->token);
        free(table);
        table = next;
    }
}

Token* findTokenByLexeme(StringTable* table, const char *lexeme) {
    while (table != NULL) {
        if (!strcmp(table->lexeme, lexeme)) {
            Token *token = copyToken(table->token);
            return token;
        }
        table = table->next;
    }
    
    return NULL;
}