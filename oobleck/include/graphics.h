#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

void initializeSDL(void);
void closeSDL(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
void renderText(SDL_Renderer* renderer, const char* text, size_t textSize, TTF_Font* font);

#endif
