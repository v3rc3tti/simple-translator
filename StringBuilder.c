#include <stdlib.h>
#include <string.h>
#include "StringBuilder.h"

StringBuilder* createStringBuilder(int initLen) {
    StringBuilder *strBuilder = malloc(sizeof(StringBuilder));
    memset(strBuilder, 0, sizeof(StringBuilder));
    strBuilder->buffer = malloc(initLen * sizeof(char));
    memset(strBuilder->buffer, 0, initLen * sizeof(char));
    strBuilder->bufferLen = initLen;
    return strBuilder;
}

void addCharToStringBuilder(StringBuilder *strBuilder, char ch) {
    if (strBuilder->length >= strBuilder->bufferLen-1) {
        char *oldBuffer = strBuilder->buffer;
        size_t newLen = sizeof(char) * 2 * strBuilder->bufferLen;
        char *newBuffer = malloc(newLen);
        memset(newBuffer, 0, newLen);
        strcpy(newBuffer, oldBuffer);
        free(oldBuffer);
        strBuilder->buffer = newBuffer;
        strBuilder->bufferLen = newLen;
    }
    strBuilder->buffer[strBuilder->length] = ch;
    strBuilder->length++;
}

void freeStringBuilder(StringBuilder *strBuilder) {
    free(strBuilder->buffer);
    free(strBuilder);
}