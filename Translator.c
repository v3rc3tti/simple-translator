#include <stdio.h>
#include "Translator.h"
#include "Token.h"

/*
 * blocks -> blocks block | e
 *   blocks -> block blocks | e
 * block -> '{' decls stmts '}'
 * decls -> decls decl | e
 * decl -> type id ;
 * stmts -> stmts stmt | e
 * stmt ->  block | id ;
 */

static Token *lookahead;
static TokenList *tokenList;

void translateTokenList(TokenList *list) {
    tokenList = list;
    lookahead = list->token;
    blocks();
}

void blocks() {
    if (lookahead->type == '{') {
        block(); blocks();
    }
}

void block() {
    match('{'); decls(); stmts(); match('}');
}

void decls() {
    if (lookahead->type == TYPE) {
        decl(); decls();
    }
}

void decl() {
    match(TYPE); match(ID); match(';');
}

void stmts() {
    if (lookahead->type == '{' || lookahead->type == ID) {
        stmt(); stmts();
    }
}

void stmt() {
    switch (lookahead->type) {
        case '{':
            block();
        break;
        case ID:
            match(ID); match(';');
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
