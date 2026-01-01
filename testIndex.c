#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t capacity;
    size_t lineCount;
    int lines[];
} LineIndex;

LineIndex* newIndex(void) {
    LineIndex* lineIndex = (LineIndex*)malloc(sizeof(LineIndex) + 25 * sizeof(int));
    (lineIndex)->capacity = 25;
    (lineIndex)->lineCount = 0;
    return lineIndex;
}

void destroyIndex(LineIndex* index) {
    free(index);
    index = NULL;
}

int main() {
    LineIndex* index = newIndex();
    (index)->lines[0] = 1;

    destroyIndex(index);
    return 0;
}