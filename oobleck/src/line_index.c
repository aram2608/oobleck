#include "../include/line_index.h"

LineIndex* NewLineIndex(void) {
  LineIndex* line_index = (LineIndex*)malloc(
      sizeof(LineIndex) + INITIAL_LINE_INDEX_SIZE * sizeof(int));
  line_index->line_count = 0;
  line_index->capacity = INITIAL_LINE_INDEX_SIZE;
  line_index->current_line = 0;
  return line_index;
}

void DestroyLineIndex(LineIndex* line_index) {
  free(line_index);
}
