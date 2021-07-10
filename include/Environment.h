#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

typedef struct Symbol_ {
    char *lexeme;
    char *type;
    struct Symbol_ *next;
} Symbol;

typedef struct Environment_ {
    Symbol* symbolTable;
    struct Environment_ *next;
} Environment;

Symbol* createSymbol(const char *lexeme, const char *type);
void freeSymbol(Symbol *symbol);

Environment* createEnvironment(Environment *parent);

//Returns parent environment if exists
Environment* freeEnvironment(Environment *env);
void addSymbolToEnvironment(Environment* env, Symbol *sym);
Symbol* findLexemeInEnvironment(Environment *env, const char *lexeme);
Symbol* findLexemeInSymbolTable(Symbol *table, const char *lexeme);

#endif