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
    TTF_Font* font = TTF_OpenFont("./font/Fira_Code/static/FiraCode-Regular.ttf", 10);
    SDL_Color color = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 255,
    };

    if (font == NULL) {
        printf("PANIC: error loading font\n");
        abort();
    }

    SDL_Window* window = SDL_CreateWindow("oobleck", 600, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_Surface* textSurface = textSurface = TTF_RenderText_Solid(font, buff->data, 0, color);

    if (textSurface == NULL) {
        printf("PANIC: failure creating text surface");
        abort();
    }

    SDL_Texture* textImage = textImage = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FRect textRect = {
        .h = textSurface->h * 3,
        .w = textSurface->w * 3,
        .x = 0,
        .y = 0,
    };

    bool run = true;
    SDL_Event event;

    bool ok = SDL_StartTextInput(window);

    if (!ok) {
        printf("PANIC: failed to start capturing text input");
        abort();
    }

    while(run) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    run = false;
                    break;
                case SDL_EVENT_TEXT_INPUT:
                    const char c = *event.text.text;
                    printf("Pressed: %c\n", c);
                    insertChar(buff, c);
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        ok = SDL_RenderTexture(renderer, textImage, NULL, &textRect);

        if (!ok) {
            printf("Failed to render texture\n");
        }
        SDL_RenderPresent(renderer);
    }
    
    umkaFree(umka);
    destroyBuffer(buff);
    SDL_DestroySurface(textSurface);
    closeSDL(window, textImage, renderer, font);
    return 0;
}
