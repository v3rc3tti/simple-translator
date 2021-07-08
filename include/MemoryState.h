#ifndef MEMORY_STATE_H
#define MEMORY_STATE_H

typedef struct MemoryState_ {
    char* buffer;
    int bufferLen;
    int pointer;
    int count;
} MemoryState;

MemoryState *createMemoryState(int bufferLen);
void freeMemoryState(MemoryState *mem);

#endif