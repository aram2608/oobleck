#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

/**
 * @headerfile gap_buffer.h
 * @brief Provides the definitions for the Gap Buffer and its utilities
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

/// @struct GapBuffer
/// @brief Structure to represent the Gap Buffer.
typedef struct {
    size_t capacity; /** The total capacity/size of the buffer */
    size_t gap_start; /**< The start of the gap */
    size_t gap_end;  /**< The end of the gap */
    char data[]; /**< The data is stored in a flexible array member (FAM) */
} GapBuffer;

/**
 * @brief Function to create a new gap buffer
 * 
 * @param initial_cap The intital starting capacity for the buffer
 * @return A pointer to the newly created buffer
 */
GapBuffer* NewBuffer(size_t initial_cap);

/**
 * @brief Function to destroy the buffer at the end of the program
 * 
 * @param buff A pointer to the gap buffer
 */
void DestroyBuffer(GapBuffer* buff);

#endif // GAP_BUFFER_H
