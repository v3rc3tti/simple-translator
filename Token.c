#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Token.h"

Token createToken(int type, const char *lexeme) {
    Token token;
    token.type = type;
    int lexLen = strlen(lexeme);
    token.lexeme = malloc((lexLen+1)*sizeof(char));
    strcpy(token.lexeme, lexeme);
    return token;
}

TokenList *createTokenList(TokenList *next, Token token) {
    TokenList* newList = malloc(sizeof(TokenList));
    memset(newList, 0, sizeof(TokenList));
    newList->next = next;
    newList->token = token;
    return newList;
}

void freeTokenList(TokenList *list) { 
    while (list != NULL) {
        Token *t = &(list->token);
        free(t->lexeme);
        TokenList *next = list->next;
        free(list);
        list = next;
    }
}

void printTokenList(TokenList *list) {
    while (list != NULL) {
        printf("type:%d|lexeme:%s\n", list->token.type,
            list->token.lexeme);
        list = list->next;
    }
}

TokenList* reverseTokenList(TokenList *list) {
    TokenList *prev = NULL;
    TokenList *next = NULL;
    
    while (list != NULL) {
        next = list->next;
        list->next = prev;
        prev = list;
        list = next;
    }
    
    return prev;
}
