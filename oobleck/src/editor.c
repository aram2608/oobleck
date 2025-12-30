#include "../include/editor.h"

Editor *newEditor(void) {
    Editor* editor = (Editor*)malloc(sizeof(editor));
    editor->buffer = newBuffer(BUFFER_SIZE);
    editor->ui = createUI();

    return editor;
}

void destroyEditor(Editor* editor) {
    destroyBuffer(editor->buffer);
    destroyUI(editor->ui);
    free(editor);
}