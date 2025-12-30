#include "../include/umkaPlugin.h"
#include "../include/gapBuffer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

void initializeSDL(void) {
    bool ok = SDL_Init(SDL_INIT_VIDEO);

    if (!ok) {
        printf("PANIC: failed to initialize SDL\n");
        exit(1);
    }

    ok = TTF_Init();

    if (!ok) {
        printf("PANIC: failed to initialize SDL TTF\n");
        exit(1);
    }
}

void closeSDL(SDL_Window* window, SDL_Texture* text, SDL_Renderer* renderer, TTF_Font* font) {
    TTF_CloseFont(font);
    SDL_DestroyTexture(text);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv) {
    GapBuffer* buff = newBuffer(BUFFER_SIZE);
    Umka* umka = loadUmka("plugin.um", argc, argv);
    umkaRun(umka);

    insertString(buff, "Hello world!");

    printf("Buffer: %s\n", buff->data);

    initializeSDL();
    TTF_Font* font = TTF_OpenFont("./font/Fira_Code/static/FiraCode-Light.ttf", 10);
    SDL_Color color = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 255,
    };

    if (font == NULL) {
        printf("PANIC: error loading font\n");
        exit(1);
    }

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Text", 0, color);

    if (textSurface == NULL) {
        printf("PANIC: failure creating text surface");
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow("oobleck", 600, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Texture* textImage = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);

    bool run = true;
    SDL_Event event;

    while(run) {
        SDL_RenderTexture(renderer, textImage, NULL, NULL);
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                run = false;
            }
        }
    }

    umkaFree(umka);
    destroyBuffer(buff);
    closeSDL(window, textImage, renderer, font);
    return 0;
}
