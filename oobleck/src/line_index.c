#include "../include/line_index.h"

LineIndex* NewLineIndex(void) {
  LineIndex* lineIndex = (LineIndex*)malloc(
      sizeof(LineIndex) + INITIAL_LINE_INDEX_SIZE * sizeof(int));
  (lineIndex)->line_count = 0;
  (lineIndex)->capacity = INITIAL_LINE_INDEX_SIZE;
  (lineIndex)->current_line = 0;
  return lineIndex;
}

void DestroyLineIndex(LineIndex* line_index) {
  free(line_index);
}
