#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t capacity; /** The total capacity/size of the buffer */
    size_t gapStart; /**< The start of the gap */
    size_t gapEnd;  /**< The end of the gap */
    char data[]; /**< The data is stored in a flexible array member (FAM) */
} GapBuffer;

#define INITIAL_CAPACITY 10

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

int main() {
    GapBuffer* buffer = newBuffer(INITIAL_CAPACITY);

    destroyBuffer(buffer);
    return 0;
}