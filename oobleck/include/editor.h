#ifndef EDITOR_H
#define EDITOR_H

#include "gapBuffer.h"
#include "ui.h"

typedef struct {
    size_t begin;
    size_t end;
} Line;

typedef struct {
    UI* ui;
    GapBuffer* buffer;
} Editor;

Editor* newEditor(void);
void destroyEditor(Editor* editor);

#endif