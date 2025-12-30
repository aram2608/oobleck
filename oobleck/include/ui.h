#ifndef UI_H
#define UI_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_PARAMS SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY

typedef struct {
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
} UI;

UI* createUI();
void initializeSDL(void);
void closeSDL(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
void renderText(SDL_Renderer* renderer, const char* text, size_t textSize, TTF_Font* font);
void destroyUI(UI* ui);

#endif
