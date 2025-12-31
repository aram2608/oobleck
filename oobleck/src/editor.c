#include "../include/editor.h"

Editor *newEditor(int argc, char** argv) {
    Editor* editor = (Editor*)malloc(sizeof(Editor));
    (editor)->buffer = newBuffer(BUFFER_SIZE);
    (editor)->stringCache = newStringCache();
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

void resizeBuffer(Editor* editor, size_t newCapacity) {
    size_t oldCapacity = bufferCapacity(editor);
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
        (editor)->stringCache->cacheStatus = CacheStatusBad;
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
        (editor)->stringCache->cacheStatus = CacheStatusBad;
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

void recalculateStringCache(Editor* editor) {
    size_t newCacheSize = sizeof(StringCache) + bufferCapacity(editor);
    StringCache* tempCache = (StringCache*)realloc((editor)->stringCache, newCacheSize);

    if (tempCache == NULL) {
        printf("PANIC: failed to reallocate the string cache\n");
        exit(1);
    } else {
        size_t gapEndOffset = (editor)->buffer->gapEnd + 1;
        size_t leftSideLength = bufferPrefixLength(editor);
        size_t rightSideLength = bufferSuffixLength(editor);

        (editor)->stringCache = tempCache;

        strncpy((editor)->stringCache->cache, (editor)->buffer->data, leftSideLength);
        strncpy(editor->stringCache->cache + leftSideLength, (editor)->buffer->data + gapEndOffset, rightSideLength);

        (editor)->stringCache->size = leftSideLength + rightSideLength;
        (editor)->stringCache->cacheStatus = CacheStatusGood;
    }
}

char* toString(Editor* editor) {
    if ((editor)->stringCache->cacheStatus == CacheStatusGood) {
        return (editor)->stringCache->cache;
    } else {
        recalculateStringCache(editor);
        return (editor)->stringCache->cache;
    }
}

size_t stringSize(Editor* editor) {
    return (editor)->stringCache->size;
}
