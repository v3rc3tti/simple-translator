#include <stdlib.h>
#include <string.h>
#include "MemoryState.h"

MemoryState *createMemoryState(int bufferLen) {
    MemoryState *newState = malloc(sizeof(MemoryState));
    memset(newState, 0, sizeof(MemoryState));
    newState->bufferLen = bufferLen;
    newState->buffer = malloc(sizeof(char)*bufferLen);
    memset(newState->buffer, 0, bufferLen*sizeof(char));
    return newState;
}

void freeMemoryState(MemoryState *mem) {
    if (mem == NULL) return;
    free(mem->buffer);
    free(mem);
}