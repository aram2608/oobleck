#include "../include/lineIndex.h"

LineIndex* newLineIndex(void) {
    LineIndex* lineIndex = (LineIndex*)malloc(sizeof(LineIndex) + INITIAL_LINE_INDEX_SIZE * sizeof(int));
    (lineIndex)->lineCount = 0;
    (lineIndex)->capacity = INITIAL_LINE_INDEX_SIZE;
    (lineIndex)->currentLine = 0;
    return lineIndex;
}

void destroyLineIndex(LineIndex* lineIndex) {
    free(lineIndex);
}
