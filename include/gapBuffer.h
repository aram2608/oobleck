#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 50

typedef struct {
    size_t capacity;
    size_t gapStart;
    size_t gapEnd;
    char data[];
} GapBuffer;

GapBuffer* newBuffer(size_t initialCapacity);

GapBuffer* resizeBuffer(GapBuffer* buff, size_t newCapacity);

void insertChar(GapBuffer* buff, const char c);

void insertString(GapBuffer* buff, const char* str);

void destroyBuffer(GapBuffer* buff);

#endif // gapBuffer.h
