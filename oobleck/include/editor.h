#ifndef EDITOR_H
#define EDITOR_H

#include "gapBuffer.h"

typedef struct {
    size_t begin;
    size_t end;
} Line;

typedef struct {
    GapBuffer* buffer;
} Editor;

#endif