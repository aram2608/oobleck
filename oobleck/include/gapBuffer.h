#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

/**
 * @file gapBuffer.h
 * @brief Provides the definitions for the Gap Buffer and its utilities
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 50

/// @brief Structure to represent the Gap Buffer.
typedef struct {
    size_t capacity; /** The total capacity/size of the buffer */
    size_t gapStart; /**< The start of the gap */
    size_t gapEnd;  /**< The end of the gap */
    char data[]; /**< The data is stored in a flexible array member (FAM) */
} GapBuffer;

/**
 * @brief Function to create a new gap buffer
 * 
 * @param initialCapacity The intital starting capacity for the buffer
 * @return A pointer to the newly created buffer
 */
GapBuffer* newBuffer(size_t initialCapacity);

/**
 * @brief Function to resize the gap buffer
 * 
 * A general rule of thumb is to double the size of the buffer as follows
 * strlen(buff->data) * 2
 * 
 * @param buff A pointer to the gap buffer
 * @param newCapacity The new size desired for the buffer
 */
GapBuffer* resizeBuffer(GapBuffer* buff, size_t newCapacity);

/**
 * @brief Function to insert a character into the buffer
 * 
 * @param buff A pointer to the gap buffer
 * @param c The character to be inserted
 */
void insertChar(GapBuffer* buff, const char c);

// Function to insert a string into the buffer
// Takes a buffer and a C string as an argument

/**
 * @brief Function to insert an entire C string into the buffer
 * 
 * Is simply a wrapper for the insertChar function
 * 
 * @param buff A pointer to the gap buffer
 * @param str The string to be inserted
 */
void insertString(GapBuffer* buff, const char* str);

// Function used to free up memory allocated for the buffer
// Takes a buffer as the argument
// After buffer creation, the caller is required to call this method on program
// termination

/**
 * @brief A function to remove a character from the buffer following a backspace
 * 
 * @param buff A pointer to the gap buffer
 */
void backspace(GapBuffer* buff);

/**
 * @brief Function to destroy the buffer at the end of the program
 * 
 * @param buff A pointer to the gap buffer
 */
void destroyBuffer(GapBuffer* buff);

#endif // GAP_BUFFER_H
