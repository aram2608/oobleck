#include "../include/editor.h"

Editor *newEditor(int argc, char** argv) {
    Editor* editor = (Editor*)malloc(sizeof(Editor));
    (editor)->buffer = newBuffer(BUFFER_SIZE);
    (editor)->ui = createUI();
    (editor)->umkaContext = loadUmka("plugin.um", argc, argv);
    umkaRun((editor)->umkaContext);

    bool ok = SDL_StartTextInput((editor)->ui->window);

    if (!ok) {
        printf("PANIC: failed to start capturing text input");
        abort();
    }

    return editor;
}

void destroyEditor(Editor* editor) {
    SDL_StopTextInput((editor)->ui->window);
    destroyBuffer((editor)->buffer);
    destroyUI((editor)->ui);
    umkaFree((editor)->umkaContext);
    free(editor);
}

size_t gapLength(Editor* editor) {
    return (editor)->buffer->gapEnd - (editor)->buffer->gapStart;
}

size_t bufferPrefixLength(Editor* editor) {
    return (editor)->buffer->gapStart;
}

size_t bufferSuffixLength(Editor* editor) {
    return (editor)->buffer->capacity - (editor)->buffer->gapEnd;
}

size_t bufferCapacity(Editor* editor) {
    return (editor)->buffer->capacity;
}

size_t bufferGapStart(Editor* editor) {
    return (editor)->buffer->gapStart;
}

size_t bufferGapEnd(Editor* editor) {
    return (editor)->buffer->gapEnd;
}

// TODO: Calculate the position of the string in memory so we can try and 
// reconstruct our gap in the buffer

void resizeBuffer(Editor* editor, size_t newCapacity) {
    size_t oldCapacity = bufferCapacity(editor);
    size_t rightSideLength = bufferSuffixLength(editor);
    size_t capacityOffset = newCapacity - oldCapacity;

    GapBuffer* tempBuff = (GapBuffer*)realloc((editor)->buffer, sizeof(GapBuffer) + newCapacity * sizeof(char));
    printf("Resized\n");

    if (tempBuff == NULL) {
        printf("PANIC: failed to reallocate buffer\n");
        exit(1);
    } else {
        (editor)->buffer = tempBuff;

        // I don't know if this calculation is right honestly
        // TODO: Map out the math here a bit better so we don't seg fault
        (editor)->buffer->gapEnd = bufferGapStart(editor) + capacityOffset;
        (editor)->buffer->capacity = newCapacity;
    }
}

void insertChar(Editor* editor, const char c) {
    if (gapLength(editor) > 1) {
        (editor)->buffer->data[(editor)->buffer->gapStart++] = c;
        toString(editor);
    } else {
        resizeBuffer(editor, bufferCapacity(editor) * 2);
        insertChar(editor, c);
    }
}

void insertString(Editor* editor, const char* str) {
    size_t length = strlen(str);
    for (size_t i = 0; i <= length - 1; i++) {
        insertChar(editor, str[i]);
    }
}

void backspace(Editor* editor) {
    if (bufferGapStart(editor) > 0) {
        (editor)->buffer->gapStart--;
    }
}

void moveLeft(Editor* editor) {
    if (bufferGapStart(editor) > 0) {
        const char c = (editor)->buffer->data[bufferGapStart(editor) - 1];
        (editor)->buffer->data[bufferGapEnd(editor)] = c;
        (editor)->buffer->gapStart--;
        (editor)->buffer->gapEnd--;
    }
}

void moveRight(Editor* editor) {
    if (bufferGapEnd(editor) < bufferCapacity(editor)) {
        const char c = (editor)->buffer->data[bufferGapEnd(editor) + 1];
        (editor)->buffer->data[bufferGapStart(editor)] = c;
        (editor)->buffer->gapStart++;
        (editor)->buffer->gapEnd++;
    }
}

void toString(Editor* editor) {
    size_t oldCapacity = bufferCapacity(editor);
    size_t rightSideLength = bufferSuffixLength(editor);
    size_t leftSideLength = bufferPrefixLength(editor);
    size_t totalSize = rightSideLength + leftSideLength;

    if (rightSideLength > 0) {
        char* leftSide = (char*)malloc(leftSideLength);
        char* rightSide = (char*)malloc(rightSideLength);

        strncpy(leftSide, (editor)->buffer->data, leftSideLength);
        strncpy(rightSide, (editor)->buffer->data, rightSideLength);

        free(leftSide);
        free(rightSide);
    } else {
        char* leftSide = (char*)malloc(leftSideLength);

        strncpy(leftSide, (editor)->buffer->data, leftSideLength);

        free(leftSide);
    }
}
