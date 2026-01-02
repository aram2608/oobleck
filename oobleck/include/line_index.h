#ifndef LINE_INDEX_H
#define LINE_INDEX_H

#include <stdlib.h>

#define INITIAL_LINE_INDEX_SIZE 25

typedef struct {
    size_t begin;
    size_t end;
} Line;

/// @struct LineIndex
/// @brief Structure to represent editor line index
typedef struct {
    size_t capacity;
    size_t lineCount;
    size_t currentLine;
    int lines[];
} LineIndex;

LineIndex* newLineIndex(void);
void destroyLineIndex(LineIndex* lineIndex);

#endif
