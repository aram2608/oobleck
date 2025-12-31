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

void destroyBuffer(GapBuffer* buff) {
    free(buff);
    buff = NULL;
}
