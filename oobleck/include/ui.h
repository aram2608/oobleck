#ifndef UI_H
#define UI_H

/**
 * @headerfile ui.h
 * @brief Provides the definitions for the UI and its utilities
 */

#include "la.h"
#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define WINDOW_PARAMS SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct {
  unsigned int texture_id;
  Vector2 size;
  Vector2 bearing;
  unsigned int advance;
} Character;

/// @brief Structure to store SDL components needed for rendering
typedef struct {
  unsigned int VAO;
  unsigned int VBO;
  Shader shader;
  GLFWwindow* window; /**< Window used for drawing */
  Character glyphs[128];
} UI;

/**
 * @brief Function used to create a new UI structure
 * @return A pointer to a UI
 */
UI* CreateUI(void);

void InitializeOpenGL(void);

void LoadFont(UI* ui);

void CloseOpenGL(void);

/**
 * @brief Function used to render the Gap Buffer's text to the window
 *
 * The text should be null terminated so the length is not strictly required
 *
 * @param ui A pointer to the UI structure
 * @param text The C string to be rendered to the window
 */
void RenderText(UI* ui, const char* text, float x, float y, float scale);

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

bool CheckCompileError(GLuint shader, char* type);

#endif  // UI_H
