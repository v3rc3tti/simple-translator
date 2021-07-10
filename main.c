#include <stdio.h>
#include <ctype.h>
#include "MemoryState.h"
#include "Token.h"
#include "StringBuilder.h"
#include "StringTable.h"

#define INPUT_BUFFER_LEN 256
#define STRING_BUILDER_LEN 256

/*
 * program -> blocks
 * blocks -> blocks block | block
 * block -> '{' decls stmts '}'
 * decls -> decls decl | e
 * decl -> type id ;
 * stmts -> stmts stmt | e
 * stmt ->  block | id ;
 */

int getNextChar(FILE* stream, MemoryState *memory) {
    if (memory->pointer >= memory->count) {
        if (feof(stream)) {
            return EOF;
        }
        size_t count = fread(memory->buffer, sizeof(char),
            memory->bufferLen, stream);
        memory->pointer = 0;
        memory->count = count;
    }

    char ch = memory->buffer[memory->pointer];
    memory->pointer++;
    return ch;
}

TokenList* getTokenList(FILE* inpFile, StringTable *strTable) {
    TokenList *head = NULL;
    MemoryState *memory = createMemoryState(INPUT_BUFFER_LEN);
    
    int ch = ' ';
    while(1) {
        while (isspace(ch)) {
            ch = getNextChar(inpFile, memory);
        }
        
        if (ch == '{' || ch == '}' || ch == ';') {
            char tmp[] = {ch, '\0'};
            Token *token = createToken(ch, tmp);
            head = createTokenList(head, token);
            ch = getNextChar(inpFile, memory);
        } else if (isalpha(ch)) {
            StringBuilder *strBuilder = createStringBuilder(STRING_BUILDER_LEN);
            do {
                addCharToStringBuilder(strBuilder, ch);
                ch = getNextChar(inpFile, memory);
            } while (isalnum(ch));
            
            Token *token = findTokenByLexeme(strTable, strBuilder->buffer);
            if (!token) {
                token = createToken(ID, strBuilder->buffer);
            }
            freeStringBuilder(strBuilder);
            head = createTokenList(head, token);
        } else if (ch == EOF) {
            break;
        } else {
            printf("Syntax error");
            freeTokenList(head);
            head = NULL;
            break;
        }
    }
    
    freeMemoryState(memory);
    head = reverseTokenList(head);
    return head;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: translator.exe filename\n");
        return 1;
    }

    FILE *inpFile = fopen(argv[1], "r");
    if (!inpFile) {
        printf("Failed to open the file!\n");
        return 1;
    }
    printf("<<===--Turbo--===>>\n");
    
    Token *token = createToken(TYPE, "int");
    StringTable *table = createStringTable(NULL, "int", token);
    token = createToken(TYPE, "bool");
    table = createStringTable(table, "bool", token);
    
    TokenList *tokens = getTokenList(inpFile, table);
    fclose(inpFile);
    printTokenList(tokens);

    freeTokenList(tokens);
    freeStringTable(table);
    
    return 0;
}