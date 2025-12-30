#include "../include/editor.h"

Editor *newEditor(int argc, char** argv) {
    Editor* editor = (Editor*)malloc(sizeof(Editor));
    editor->buffer = newBuffer(BUFFER_SIZE);
    editor->ui = createUI();
    editor->umkaContext = loadUmka("plugin.um", argc, argv);
    umkaRun(editor->umkaContext);

    bool ok = SDL_StartTextInput(editor->ui->window);

    if (!ok) {
        printf("PANIC: failed to start capturing text input");
        abort();
    }

    return editor;
}

void destroyEditor(Editor* editor) {
    SDL_StopTextInput(editor->ui->window);
    destroyBuffer(editor->buffer);
    destroyUI(editor->ui);
    umkaFree(editor->umkaContext);
    free(editor);
}