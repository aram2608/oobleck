#ifndef EDITOR_H
#define EDITOR_H

/**
 * @file editor.h
 * @brief Provides the definitions for the Editor and its utilities
 */

#include "gapBuffer.h"
#include "ui.h"
#include "umkaPlugin.h"


/// @brief Structure to represent editor lines
typedef struct {
    size_t begin;
    size_t end;
} Line;

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

#endif // EDITOR_H
