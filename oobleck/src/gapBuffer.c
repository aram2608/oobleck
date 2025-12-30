#include "../include/gapBuffer.h"

GapBuffer* newBuffer(size_t initialCapacity) {
    GapBuffer *buff = (GapBuffer*)malloc(sizeof(GapBuffer) + initialCapacity * sizeof(char));

    if (buff == NULL) {
        printf("failed to allocate buffer");
        exit(1);
    }

    (buff)->gapStart = 0;
    (buff)->capacity = initialCapacity;
    (buff)->gapEnd = initialCapacity - 1;
    return buff;
}

GapBuffer* resizeBuffer(GapBuffer* buff, size_t newCapacity) {
    GapBuffer* newBuff = (GapBuffer*)realloc(buff, sizeof(GapBuffer) + newCapacity * sizeof(char));

    if (newBuff == NULL) {
        printf("failed to reallocate buffer");
        exit(1);
    }

    (newBuff)->capacity = newCapacity;
    return newBuff;
}

void insertChar(GapBuffer* buff, const char c) {
    if ((buff)->capacity > 1) {
        (buff)->data[buff->gapStart++] = c;
        (buff)->capacity--;
    } else {
        // (buff) = resizeBuffer(buff, strlen(buff->data) * 2);
        // insertChar(buff, c);
        printf("Full\n");
    }
}

void insertString(GapBuffer* buff, const char* str) {
    size_t length = strlen(str);
    for (size_t i = 0; i <= length - 1; i++) {
        insertChar(buff, str[i]);
    }
}

char* toString(GapBuffer* buff) {
    return "Hello world";
}

void destroyBuffer(GapBuffer* buff) {
    free(buff);
    buff = NULL;
}

void backspace(GapBuffer* buff) {
    if ((buff)->gapStart > 0) {
        (buff)->gapStart--;
        (buff)->capacity++;
    }
}
