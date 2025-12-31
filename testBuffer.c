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
    for (size_t i = 0; i <= stringSize; i++) {
        insertChar(buffer, str[i]);
    }
}

void bufferSizes(GapBuffer* buffer) {
    size_t leftSideLength = (buffer)->gapStart;
    size_t rightSideLength = (buffer)->capacity - (buffer)->gapEnd;
    size_t gapEnd = (buffer)->gapEnd;

    printf("Left Side Length: %zu\nRight Side Length: %zu\nGap end: %zu\n", leftSideLength, rightSideLength, gapEnd);
}

void dumpBufferMemory(GapBuffer* buffer) {
    for (size_t it = 0; it <= (buffer)->capacity; it++) {
        printf("Memory: %p at index: %zu for character %c\n", &(buffer)->data[it], it, (buffer)->data[it]);
    }
}

void toString(GapBuffer* buffer) {
    size_t leftSideLength = (buffer)->gapStart;
    size_t rightSideLength = (buffer)->capacity - (buffer)->gapEnd;

    if (rightSideLength > 0) {
        char* leftSide = (char*)malloc(leftSideLength);
        char* rightSide = (char*)malloc(rightSideLength);

        strncpy(leftSide, (buffer)->data, leftSideLength);
        strncpy(rightSide, (buffer)->data + (buffer)->gapEnd + 1, rightSideLength);

        leftSide[leftSideLength] = '\0';
        rightSide[rightSideLength] = '\0';

        size_t gapEnd = (buffer)->gapEnd;
        printf("Left Side: %s\nRight Side: %s\nChar at gap end: %c\n", leftSide, rightSide, (buffer)->data[gapEnd + 1]);

        free(leftSide);
        free(rightSide);
    } else {
        char* leftSide = (char*)malloc(leftSideLength);

        strncpy(leftSide, (buffer)->data, leftSideLength);

        leftSide[leftSideLength] = '\0';

        printf("Left Side: %s\n", leftSide);
        free(leftSide);
    }
}

void moveLeft(GapBuffer* buffer) {
    if ((buffer)->gapStart > 0) {
        const char c = (buffer)->data[(buffer)->gapStart - 1];
        buffer->data[(buffer)->gapEnd] = c;
        buffer->data[buffer->gapStart - 1] = '*';
        buffer->gapStart--;
        buffer->gapEnd--;
    }
}

int main(void) {
    GapBuffer* buffer = newBuffer(INITIAL_CAPACITY);
    insertString(buffer, "Hello world!");
    printf("Hello World! Length: %zu\n", strlen("Hello world!"));

    bufferSizes(buffer);

    toString(buffer);

    moveLeft(buffer);
    moveLeft(buffer);
    moveLeft(buffer);
    moveLeft(buffer);

    printf("--------------Post move--------------\n");

    bufferSizes(buffer);

    toString(buffer);

    printf("--------------Memory--------------\n");

    dumpBufferMemory(buffer);

    destroyBuffer(buffer);
    return 0;
}
