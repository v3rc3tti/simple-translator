#include <stdlib.h>
#include <string.h>
#include "Environment.h"

Symbol* createSymbol(const char *lexeme, const char *type) {
    Symbol *symbol = malloc(sizeof(Symbol));
    memset(symbol, 0, sizeof(Symbol));
    int lexemeLen = strlen(lexeme) + 1;
    int typeLen = strlen(type) + 1;
    symbol->lexeme = malloc(lexemeLen * sizeof(char));
    symbol->type = malloc(typeLen * sizeof(char));
    strcpy(symbol->lexeme, lexeme);
    strcpy(symbol->type, type);
    return symbol;
}

void freeSymbol(Symbol *symbol) {
    free(symbol->lexeme);
    free(symbol->type);
    free(symbol);
}

Environment* createEnvironment(Environment *parent) {
    Environment *env = malloc(sizeof(Environment));
    memset(env, 0, sizeof(Environment));
    env->next = parent;
    return env;
}

Environment* freeEnvironment(Environment *env) {
    Symbol *sym = env->symbolTable;
    
    while (sym != NULL) {
        Symbol *next = sym->next;
        freeSymbol(sym);
        sym = next;
    }
    Environment *parent = env->next;
    free(env);
    return parent;
}

void addSymbolToEnvironment(Environment* env, Symbol *sym) {
    if (env == NULL || sym == NULL) {
        return;
    }
    
    sym->next = env->symbolTable;
    env->symbolTable = sym;
}

Symbol* findLexemeInEnvironment(Environment *env, const char *lexeme) {
    while (env != NULL) {
        Symbol *sym = findLexemeInSymbolTable(env->symbolTable, lexeme);
        if (sym) {
            return sym;
        }
        env = env->next;
    }
    return NULL;
}

Symbol* findLexemeInSymbolTable(Symbol *table, const char *lexeme) {
    while (table != NULL) {
        if (!strcmp(table->lexeme, lexeme)) {
            return table;
        }
        table = table->next;
    }
    return NULL;
}