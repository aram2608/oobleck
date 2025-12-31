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

void resizeBuffer(Editor* editor, size_t newCapacity) {
    // char leftSide[strlen(editor->buffer->data)];
    // char rightSide[strlen(editor->buffer->data)];

    // memcpy(leftSide, editor->buffer->data, editor->buffer->gapStart);
    // memcpy(rightSide, editor->buffer->data);

    // printf("Left side: %s\n", leftSide);

    GapBuffer* tempBuff = (GapBuffer*)realloc((editor)->buffer, sizeof(GapBuffer) + newCapacity * sizeof(char));
    printf("Resized\n");
    if (tempBuff == NULL) {
        printf("failed to reallocate buffer");
        exit(1);
    }

    (editor)->buffer = tempBuff;
    (editor)->buffer->capacity = newCapacity;
}

void insertChar(Editor* editor, const char c) {
    if ((editor)->buffer->capacity > 1) {
        (editor)->buffer->data[(editor)->buffer->gapStart++] = c;
        (editor)->buffer->capacity--;
    } else {
        resizeBuffer(editor, strlen((editor)->buffer->data) * 2);
        // insertChar(buff, c);
    }
}

void insertString(Editor* editor, const char* str) {
    size_t length = strlen(str);
    for (size_t i = 0; i <= length - 1; i++) {
        insertChar((editor)->buffer, str[i]);
    }
}

void backspace(Editor* editor) {
    if ((editor)->buffer->gapStart > 0) {
        (editor)->buffer->gapStart--;
        (editor)->buffer->capacity++;
    }
}
