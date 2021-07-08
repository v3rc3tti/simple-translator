#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

typedef struct StringBuilder_ {
    char *buffer;
    int bufferLen;
    int length;
} StringBuilder;

StringBuilder* createStringBuilder(int initLen);
void addCharToStringBuilder(StringBuilder *strBuilder, char ch);
void freeStringBuilder(StringBuilder *strBuilder);

#endif