#include "../include/editor.h"

Editor* NewEditor(int argc, char** argv) {
  Editor* editor = (Editor*)malloc(sizeof(Editor));
  editor->buffer = NewBuffer(BUFFER_SIZE);
  editor->str_cache = NewStringCache();
  editor->line_index = NewLineIndex();
  editor->ui = CreateUI();
  editor->umka_context = LoadUmka("plugin.um", argc, argv);
  umkaRun(editor->umka_context);
  return editor;
}

void DestroyEditor(Editor* editor) {
  DestroyBuffer(editor->buffer);
  DestroyUI(editor->ui);
  DestroyLineIndex(editor->line_index);
  DestroyStringCache(editor->str_cache);
  umkaFree(editor->umka_context);
  free(editor);
}

size_t GapLength(Editor* editor) {
  return editor->buffer->gap_end - editor->buffer->gap_start;
}

size_t BufferPrefixLength(Editor* editor) {
  return editor->buffer->gap_start;
}

size_t BufferSuffixLength(Editor* editor) {
  return editor->buffer->capacity - editor->buffer->gap_end;
}

size_t BufferCapacity(Editor* editor) {
  return editor->buffer->capacity;
}

size_t BufferGapStart(Editor* editor) {
  return editor->buffer->gap_start;
}

size_t BufferGapEnd(Editor* editor) {
  return editor->buffer->gap_end;
}

void ResizeBuffer(Editor* editor, size_t new_cap) {
  size_t old_cap = BufferCapacity(editor);
  size_t cap_offset = new_cap - old_cap;
  size_t old_prefix_len = BufferPrefixLength(editor);
  size_t old_suffix_len = BufferSuffixLength(editor);

  char old_prefix[old_prefix_len];
  char old_suffix[old_suffix_len];
  memcpy(old_prefix, editor->buffer->data, old_prefix_len);
  memcpy(old_prefix, editor->buffer->data + editor->buffer->gap_end,
         old_suffix_len);

  GapBuffer* temp_buff = (GapBuffer*)realloc(
      editor->buffer, sizeof(GapBuffer) + new_cap * sizeof(char));
  printf("Resized\n");

  if (temp_buff == NULL) {
    fprintf(stderr, "PANIC: failed to reallocate buffer\n");
    exit(1);
  } else {
    editor->buffer = temp_buff;

    size_t new_gap_end = old_prefix_len + cap_offset;
    memcpy(editor->buffer->data, old_prefix, old_prefix_len);
    memcpy(editor->buffer->data + new_gap_end, old_suffix, old_prefix_len);
    editor->buffer->gap_end = new_gap_end;
    editor->buffer->capacity = new_cap;
  }
}

void InsertChar(Editor* editor, const char c) {
  if (GapLength(editor) > 1) {
    editor->buffer->data[editor->buffer->gap_start++] = c;
    editor->str_cache->cache_status = CacheStatusBad;
  } else {
    ResizeBuffer(editor, BufferCapacity(editor) * 2);
    InsertChar(editor, c);
  }
}

void InsertString(Editor* editor, const char* str) {
  if (GapLength(editor) > 1) {
    size_t str_size = strlen(str);
    size_t buff_size = editor->buffer->gap_start;
    memcpy(editor->buffer->data + buff_size, str, str_size);
    editor->buffer->gap_start += str_size;
    editor->str_cache->cache_status = CacheStatusBad;
  } else {
    ResizeBuffer(editor, BufferCapacity(editor) * 2);
    InsertString(editor, str);
  }
}

void Backspace(Editor* editor) {
  if (BufferGapStart(editor) > 0) {
    editor->buffer->gap_start--;
    editor->str_cache->cache_status = CacheStatusBad;
  }
}

void MoveLeft(Editor* editor) {
  if (BufferGapStart(editor) > 0) {
    const char c = editor->buffer->data[BufferGapStart(editor) - 1];
    editor->buffer->data[BufferGapEnd(editor)] = c;
    editor->buffer->gap_start--;
    editor->buffer->gap_end--;
  }
}

void MoveRight(Editor* editor) {
  if (BufferGapEnd(editor) < BufferCapacity(editor)) {
    const char c = editor->buffer->data[BufferGapEnd(editor) + 1];
    editor->buffer->data[BufferGapStart(editor)] = c;
    editor->buffer->gap_start++;
    editor->buffer->gap_end++;
  }
}

void RecalculateStringCache(Editor* editor) {
  size_t newCacheSize = sizeof(StringCache) + BufferCapacity(editor);
  StringCache* temp_cache =
      (StringCache*)realloc(editor->str_cache, newCacheSize);

  if (temp_cache == NULL) {
    printf("PANIC: failed to reallocate the string cache\n");
    exit(1);
  } else {
    size_t gap_end_offset = editor->buffer->gap_end + 1;
    // Left side of the gap
    size_t prefix_length = BufferPrefixLength(editor);
    // Right side of the gap
    size_t suffix_length = BufferSuffixLength(editor);

    editor->str_cache = temp_cache;

    strncpy(editor->str_cache->cache, editor->buffer->data, prefix_length);
    strncpy(editor->str_cache->cache + prefix_length,
            editor->buffer->data + gap_end_offset, suffix_length);

    editor->str_cache->size = prefix_length + suffix_length;
    editor->str_cache->cache_status = CacheStatusGood;
  }
}

char* ToString(Editor* editor) {
  if (editor->str_cache->cache_status == CacheStatusGood) {
    return editor->str_cache->cache;
  } else {
    RecalculateStringCache(editor);
    return editor->str_cache->cache;
  }
}

size_t StringSize(Editor* editor) {
  return editor->str_cache->size;
}

void IncrementLine(Editor* editor, int new_index) {
  if (editor->line_index->capacity > editor->line_index->line_count) {
    editor->line_index->lines[editor->line_index->line_count++] = new_index;
    editor->line_index->current_line++;
    printf("New Index: %d\n", new_index);
  } else {
    printf("Index needs resized\n");
  }
}

void RenderGUI(Editor* editor) {}
