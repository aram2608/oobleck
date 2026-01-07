#include "../include/gap_buffer.h"

GapBuffer* NewBuffer(size_t initial_cap) {
  GapBuffer* buff =
      (GapBuffer*)malloc(sizeof(GapBuffer) + initial_cap * sizeof(char));

  if (buff == NULL) {
    printf("failed to allocate buffer");
    exit(1);
  }

  buff->gap_start = 0;
  buff->capacity = initial_cap;
  buff->gap_end = initial_cap;
  return buff;
}

void DestroyBuffer(GapBuffer* buff) {
  free(buff);
  buff = NULL;
}
