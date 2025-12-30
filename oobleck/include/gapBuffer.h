#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 50

// Structure to represent the Gap Buffer
// The data is stored in a flexible array member (FAM)
typedef struct {
    size_t capacity;
    size_t gapStart;
    size_t gapEnd;
    char data[];
} GapBuffer;

// Function to create a new buffer
// Takes an inital size for the starting capacity as an argument
// Returns a pointer to a buffer, the caller is required to free up allocated
// memory
GapBuffer* newBuffer(size_t initialCapacity);

// Function to resize the gap in the buffer
// Takes a pointer to the buffer and the new capacity as arguments
// A general rule of thumb is to double the size of the buffer as follows
// strlen(buff->data) * 2
GapBuffer* resizeBuffer(GapBuffer* buff, size_t newCapacity);

// Function to insert a single character into the buffer
// Takes a buffer and a char as arguments
void insertChar(GapBuffer* buff, const char c);

// Function to insert a string into the buffer
// Takes a buffer and a C string as an argument
void insertString(GapBuffer* buff, const char* str);

// Function used to free up memory allocated for the buffer
// Takes a buffer as the argument
// After buffer creation, the caller is required to call this method on program
// termination
void destroyBuffer(GapBuffer* buff);

#endif // gapBuffer.h
