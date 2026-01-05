#ifndef UI_H
#define UI_H

/**
 * @headerfile ui.h
 * @brief Provides the definitions for the UI and its utilities
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_PARAMS SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

/// @brief Structure to store SDL components needed for rendering
typedef struct {
    TTF_Font* font; /** Pointer to text font */
    SDL_Window* window; /** Window used for drawing */
    SDL_Renderer* renderer; /** Renderer for text and other events */
} UI;

/**
 * @brief Function used to create a new UI structure
 * @return A pointer to a UI
 */
UI* CreateUI(void);

/**
 * @brief Function used to initialize an SDL context
 * 
 * This function is later invoked upon UI creation
 */
void InitializeSDL(void);

/**
 * @brief Function used to render the Gap Buffer's text to the window
 * 
 * The text should be null terminated so the length is not strictly required
 * 
 * @param ui A pointer to the UI structure
 * @param text The C string to be rendered to the window
 * @param text_length The length of the C string
 */
void RenderText(UI* ui, const char* text, size_t text_length);

/**
 * @brief Function used to render to cursor
 * @param ui A pointer to the UI structure
 * @param cursor_pos The current cursor position (ie. that gap start)
 * @param line_index The current line index
 */
void RenderCursor(UI* ui, size_t cursor_pos, size_t line_index);

/**
 * @brief Function used to destroy the UI and cleanup allocated memory
 */
void DestroyUI(UI* ui);

#endif // UI_H
