#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    size_t capacity; /** The total capacity/size of the buffer */
    size_t gapStart; /**< The start of the gap */
    size_t gapEnd;  /**< The end of the gap */
    char data[]; /**< The data is stored in a flexible array member (FAM) */
} GapBuffer;

#define INITIAL_CAPACITY 20

GapBuffer* newBuffer(size_t initialCapacity) {
    GapBuffer *buff = (GapBuffer*)malloc(sizeof(GapBuffer) + initialCapacity * sizeof(char));

    if (buff == NULL) {
        printf("failed to allocate buffer");
        exit(1);
    }

    (buff)->gapStart = 0;
    (buff)->capacity = initialCapacity;
    (buff)->gapEnd = initialCapacity;
    return buff;
}

void destroyBuffer(GapBuffer* buff) {
    free(buff);
    buff = NULL;
}

void insertChar(GapBuffer* buffer, const char c) {
    if ((buffer)->gapEnd - (buffer)->gapStart > 0) {
        (buffer)->data[(buffer)->gapStart++] = c;
    }
}

void insertString(GapBuffer* buffer, const char* str) {
    size_t stringSize = strlen(str);
    for (size_t i = 0; i <= stringSize - 1; i++) {
        insertChar(buffer, str[i]);
    }
}

void bufferSizes(GapBuffer* buffer) {
    size_t leftSideLength = (buffer)->gapStart;
    size_t rightSideLength = (buffer)->capacity - (buffer)->gapEnd;

    printf("Left Side Length: %zu\nRight Side Length: %zu\n", leftSideLength, rightSideLength);
}

void dumpBuffer(GapBuffer* buffer) {
    printf("%s\n", buffer->data);
}

void toString(GapBuffer* buffer) {
    size_t leftSideLength = (buffer)->gapStart;
    size_t rightSideLength = (buffer)->capacity - (buffer)->gapEnd;

    if (rightSideLength > 0) {
        char* leftSide = (char*)malloc(leftSideLength);
        char* rightSide = (char*)malloc(rightSideLength);

        strncpy(leftSide, (buffer)->data, leftSideLength);
        strncpy(rightSide, (buffer)->data, rightSideLength);

        printf("Left Side: %s\n Right Side: %s\n", leftSide, rightSide);

        free(leftSide);
        free(rightSide);
    } else {
        char* leftSide = (char*)malloc(leftSideLength);

        strncpy(leftSide, (buffer)->data, leftSideLength);

        printf("Left Side: %s\n", leftSide);
        free(leftSide);
    }
}

int main() {
    GapBuffer* buffer = newBuffer(INITIAL_CAPACITY);
    insertString(buffer, "Hello world!");

    dumpBuffer(buffer);
    bufferSizes(buffer);

    toString(buffer);

    destroyBuffer(buffer);
    return 0;
}