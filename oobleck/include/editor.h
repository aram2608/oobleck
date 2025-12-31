#ifndef EDITOR_H
#define EDITOR_H

/**
 * @file editor.h
 * @brief Provides the definitions for the Editor and its utilities
 */

#include "gapBuffer.h"
#include "ui.h"
#include "umkaPlugin.h"


/// @struct Line
/// @brief Structure to represent editor lines
typedef struct {
    size_t begin;
    size_t end;
} Line;

/// @struct Editor
/// @brief Structure to store editor specific objects
typedef struct {
    UI* ui; /**< Pointer to UI, contains base window/rendering utils */
    GapBuffer* buffer; /**< Pointer to the gap buffer for storing text */
    Umka* umkaContext; /**< Pointer to Umka, used for scripting layer */
} Editor;

/**
 * @brief Function to create a new editor structure, caller must deallocate memory
 * @param argc 
 * @param argv 
 * @return A pointer to a new editor
 */
Editor* newEditor(int argc, char** argv);

/**
 * @brief Function to destroy an instance of an editor
 * @param editor Pointer to an editor
 */
void destroyEditor(Editor* editor);

/**
 * @brief Function to resize the gap buffer
 * 
 * A general rule of thumb is to double the size of the buffer as follows
 * (editor)->buffer->capacity * 2
 * 
 * @param editor A pointer to the editor
 * @param newCapacity The new size desired for the buffer
 */
void resizeBuffer(Editor* editor, size_t newCapacity);

/**
 * @brief Function to insert a character into the buffer
 * 
 * @param editor A pointer to the editor
 * @param c The character to be inserted
 */
void insertChar(Editor* editor, const char c);

/**
 * @brief Function to insert an entire C string into the buffer
 * 
 * Is simply a wrapper for the insertChar function
 * 
 * @param editor A pointer to the editor
 * @param str The string to be inserted
 */
void insertString(Editor* editor, const char* str);

/**
 * @brief A function to remove a character from the buffer following a backspace
 * 
 * @param editor A pointer to the editor
 */
void backspace(Editor* editor);

/**
 * @brief Function to move the cursor left
 * @param editor A pointer to the editor
 */
void moveLeft(Editor* editor);

/**
 * @brief Function to move the cursor right
 * @param editor A pointer to the editor
 */
void moveRight(Editor* editor);

void toString(Editor* editor);

#endif // EDITOR_H
