#include <stdio.h>
#include "Translator.h"
#include "Token.h"
#include "Environment.h"

/*
 * blocks -> blocks block | e
 * block -> '{' {push Environment} decls stmts '}' {pop Environment}
 * decls -> decls decl | e
 * decl -> type id ; {add Symbol to Environment}
 * stmts -> stmts stmt | e
 * stmt ->  block | id ; {find Symbol in Environment}
 */

static Token *lookahead;
static TokenList *tokenList;
static Environment *environment;

void translateTokenList(TokenList *list) {
    environment = createEnvironment(NULL);
    tokenList = list;
    lookahead = list->token;
    blocks();
    freeEnvironment(environment);
}

void blocks() {
    if (lookahead->type == '{') {
        block(); blocks();
    }
}

void block() {
    match('{'); 
    
    //start semantic action
    printf("{");
    environment = createEnvironment(environment);
    //end semantic action
    
    decls();
    stmts(); 
    match('}');
    
    //start semantic action
    printf("}");
    environment = freeEnvironment(environment);
    //end semantic action
}

void decls() {
    if (lookahead->type == TYPE) {
        decl(); decls();
    }
}

void decl() {
    //start semantic action
    Token *typeToken = lookahead;
    //end semantic action
    
    match(TYPE);
    
    //start semantic action
    Token *idToken = lookahead;
    //end semantic action
    
    match(ID); match(';');
    
    //start semantic action
    Symbol *symbol = createSymbol(idToken->lexeme, typeToken->lexeme);
    addSymbolToEnvironment(environment, symbol);
    //end semantic action
}

void stmts() {
    if (lookahead->type == '{' || lookahead->type == ID) {
        stmt();
        stmts();
    }
}

void stmt() {
    switch (lookahead->type) {
        case '{':
            block();
        break;
        case ID: {
            //start semantic action
            Token *idToken = lookahead;
            //end semantic action
            
            match(ID);
            match(';');
            
            //start semantic action
            Symbol *symbol = findLexemeInEnvironment(environment, idToken->lexeme);
            if (symbol) {
                printf("%s:%s;", symbol->lexeme, symbol->type);
            }
            //end semantic action
        }    
        break;
        default:
            printf("Syntax Error");
            lookahead = NULL;
    }
}

void match(int tokenType) {
    if (lookahead->type == tokenType) {
        tokenList = tokenList->next;
        if (tokenList) {
            lookahead = tokenList->token;
        } else {
            lookahead = NULL;
        }
    } else {
        printf("Syntax Error\n");
        lookahead = NULL;
    }
}
