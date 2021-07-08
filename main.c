#include <stdio.h>
#include <ctype.h>
#include "MemoryState.h"
#include "Token.h"

#define INPUT_BUFFER_LEN 256

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

TokenList* getTokenList(FILE* inpFile) {
    TokenList *head = NULL;
    MemoryState *memory = createMemoryState(INPUT_BUFFER_LEN);
    
    while(1) {
        int ch = 0;
        do {
            ch = getNextChar(inpFile, memory);
        } while (isspace(ch));
        
        if (ch == '{' || ch == '}' || ch == ';') {
            char tmp[] = {ch, '\0'};
            Token token = createToken(ch, tmp);
            head = createTokenList(head, token);
        }
        
        if (ch == EOF) {
            break;
        }
    }
    
    freeMemoryState(memory);
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

    TokenList *tokens = getTokenList(inpFile);
    fclose(inpFile);
    printTokenList(tokens);

    freeTokenList(tokens);
    return 0;
}