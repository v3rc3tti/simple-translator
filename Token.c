#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Token.h"

Token* createToken(int type, const char *lexeme) {
    Token* token = malloc(sizeof(Token));
    memset(token, 0, sizeof(Token));
    token->type = type;
    int lexLen = strlen(lexeme);
    token->lexeme = malloc((lexLen+1)*sizeof(char));
    strcpy(token->lexeme, lexeme);
    return token;
}

Token* copyToken(Token *token) {
    Token *newToken = malloc(sizeof(Token));
    memset(newToken, 0, sizeof(Token));
    newToken->type = token->type;
    size_t lexemeLen = strlen(token->lexeme) + 1;
    newToken->lexeme = malloc(lexemeLen * sizeof(char));
    strcpy(newToken->lexeme, token->lexeme);
    return newToken;
}

void freeToken(Token *token) {
    free(token->lexeme);
    free(token);
}

TokenList* createTokenList(TokenList *next, Token *token) {
    TokenList* newList = malloc(sizeof(TokenList));
    memset(newList, 0, sizeof(TokenList));
    newList->next = next;
    newList->token = token;
    return newList;
}

void freeTokenList(TokenList *list) { 
    while (list != NULL) {
        freeToken(list->token);
        TokenList *next = list->next;
        free(list);
        list = next;
    }
}

void printTokenList(TokenList *list) {
    while (list != NULL) {
        printf("type:%d|lexeme:%s\n", list->token->type,
            list->token->lexeme);
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
