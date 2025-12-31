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

// TODO: Calculate the position of the string in memory so we can try and 
// reconstruct our gap in the buffer
void resizeBuffer(Editor* editor, size_t newCapacity) {
    GapBuffer* tempBuff = (GapBuffer*)realloc((editor)->buffer, sizeof(GapBuffer) + newCapacity * sizeof(char));
    printf("Resized\n");

    if (tempBuff == NULL) {
        printf("PANIC: failed to reallocate buffer\n");
        exit(1);
    } else {
        (editor)->buffer = tempBuff;
        (editor)->buffer->capacity = newCapacity;
        (editor)->buffer->gapEnd = newCapacity - 1;
    }
}

void insertChar(Editor* editor, const char c) {
    if ((editor)->buffer->gapEnd - (editor)->buffer->gapStart > 1) {
        (editor)->buffer->data[(editor)->buffer->gapStart++] = c;
        toString(editor);
    } else {
        resizeBuffer(editor, (editor)->buffer->capacity * 2);
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
    if ((editor)->buffer->gapStart > 0) {
        (editor)->buffer->gapStart--;
    }
}

void moveLeft(Editor* editor) {
    if ((editor)->buffer->gapStart > 0) {
        const char c = (editor)->buffer->data[(editor)->buffer->gapStart - 1];
        (editor)->buffer->data[editor->buffer->gapEnd] = c;
        (editor)->buffer->gapStart--;
        (editor)->buffer->gapEnd--;
    }
}

void moveRight(Editor* editor) {
    if ((editor)->buffer->gapEnd < (editor)->buffer->capacity - 1) {
        const char c = (editor)->buffer->data[(editor)->buffer->gapEnd + 1];
        (editor)->buffer->data[editor->buffer->gapStart] = c;
        (editor)->buffer->gapStart++;
        (editor)->buffer->gapEnd++;
    }
}

void toString(Editor* editor) {
    char* leftSide = (char*)malloc((editor)->buffer->gapStart);
    char* rightSide = (char*)malloc((editor)->buffer->capacity - (editor)->buffer->gapEnd + 100);
    strncpy(leftSide, (editor)->buffer->data, (editor)->buffer->gapStart);
    strncpy(rightSide, (editor)->buffer->data + (editor)->buffer->gapEnd, (editor)->buffer->capacity - (editor)->buffer->gapEnd);

    printf("Left side: %s, Right side: %s\n", leftSide, rightSide);
    free(leftSide);
    free(rightSide);
}
