#ifndef LINE_INDEX_H
#define LINE_INDEX_H

/**
 * @headerfile line_index.h
 * @brief Implementation for the line index
 */

#include <stdlib.h>

#define INITIAL_LINE_INDEX_SIZE 25

typedef struct {
  size_t begin;
  size_t end;
} Line;

/// @struct LineIndex
/// @brief Structure to represent editor line index
typedef struct {
  size_t capacity;     /** Array capacity */
  size_t line_count;   /** Keep track of the current buffer position */
  size_t current_line; /** The current line being editted */
  int lines[];
} LineIndex;

LineIndex* NewLineIndex(void);
void DestroyLineIndex(LineIndex* line_index);

#endif
