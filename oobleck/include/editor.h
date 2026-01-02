#ifndef EDITOR_H
#define EDITOR_H

/**
 * @headerfile editor.h
 * @brief Provides the definitions for the Editor and its utilities
 */

#include "string_cache.h"
#include "line_index.h"
#include "gap_buffer.h"
#include "ui.h"
#include "umka_plugin.h"

/// @struct Editor
/// @brief Structure to store editor specific objects
typedef struct {
    UI* ui; /**< Pointer to UI, contains base window/rendering utils */
    GapBuffer* buffer; /**< Pointer to the gap buffer for storing text */
    LineIndex* lineIndex; /** Pointer to line index */
    StringCache* stringCache; /** Pointer to the String Cache */
    Umka* umkaContext; /**< Pointer to Umka, used for scripting layer */
} Editor;

/**
 * @brief Function to create a new editor structure, caller must deallocate memory
 * @param argc The command line argument count
 * @param argv The command line arguments
 * 
 * The provided parameters do not do anythin as of right now. They are simply
 * passed to the Umka context for its constructor.
 * 
 * @return A pointer to a new editor
 */
Editor* newEditor(int argc, char** argv);

/**
 * @brief Function to destroy an instance of an editor
 * @param editor Pointer to an editor
 */
void destroyEditor(Editor* editor);

/**
 * @brief Function to return the length of the gap
 * @param editor A pointer to the editor
 * 
 * A simple calculation of the gapEnd - gapStart
 * @return The size of the gap
 */
size_t gapLength(Editor* editor);

/**
 * @brief Function to return the length of the buffer prefix
 * @param editor A pointer to the editor
 * 
 * Simply returns the start of the gap. Used primarily for readability during
 * calculations.
 * 
 * @return The size of the buffer prefix (ie. the start of the gap)
 */
size_t bufferPrefixLength(Editor* editor);

/**
 * @brief Function to return the length of the buffer suffix
 * @param editor A pointer to the editor
 * 
 * Calculating the suffix is slightly more involved than the prefix.
 * We need to subtract the total capacity from the end of the gap.
 * 
 * @return The size of the buffer suffix
 */
size_t bufferSuffixLength(Editor* editor);

/**
 * @brief Function to return the buffer capacity
 * @param editor A pointer to the editor
 * 
 * A simple helper function to improve readability for calculations
 * 
 * @return The bufer capacity size
 */
size_t bufferCapacity(Editor* editor);

/**
 * @brief Function to return the buffer gap start
 * @param editor A pointer to the editor
 * 
 * A simple helper function to improve readability, an alias for bufferPrefixLength
 * 
 * @return The start position of the buffer's gap
 */
size_t bufferGapStart(Editor* editor);

/**
 * @brief Function to return the buffer gap end
 * @param editor A pointer to the editor
 * 
 * A simple helper function to improve readability for calculations
 * 
 * @return The end position of the buffer's gap
 */
size_t bufferGapEnd(Editor* editor);

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

/**
 * @brief Function to recalculate the cached string
 * @param editor A pointer to the editor
 */
void recalculateStringCache(Editor* editor);

/**
 * @brief Function to return the string representation of the buffer
 * @param editor A pointer to the editor
 * 
 * This method simply returns the cached string. It first tests to see if the
 * cache status is okay
 * 
 * @return The cached string
 */
char* toString(Editor* editor);

/**
 * @brief Function to return the cached string's size
 * @param editor A pointer to the editor
 * 
 * This method simply returns the cached string's size.
 * 
 * @return The size of the cached string
 */
size_t stringSize(Editor* editor);

void incrementLine(Editor* editor, int lineIndex);

#endif // EDITOR_H
